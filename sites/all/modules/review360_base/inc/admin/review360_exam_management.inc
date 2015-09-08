<?php
require_once dirname(__FILE__) . '/../../lib/PHPExcel/PHPExcel/IOFactory.php';

function review360_exam_management_view(){
    $action_name = theme('review360_exam_mg_view');
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review360_exam_edit($exam_id){
//    $nd = node_load(688);
//    dd($nd->webform['components']);
    $action_name = theme('review360_exam_mg_edit',array('exam_id'=>$exam_id));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review360_group_change_name_ajax(){
    $exam_name = $_POST['exam_name'];
    $exam_id = $_POST['exam_id'];
    $spend_time = $_POST['spend_time'];
    if(validate_exam_post_infor($exam_name,$spend_time,$exam_id)){
         echo drupal_json_output(array('status' => 'failed'));
    } else {
        $rst = db_update('review360_exam')
            ->fields(array(
              'exam_name' => $exam_name,
              'spend_time'=>$spend_time,
              'update_date' => time(),
            ))
            ->condition('exam_id', $exam_id)
            ->execute();
        if ($rst) {
            drupal_set_message(t("问卷信息修改成功。")); 
            echo drupal_json_output(array('status' => 'success'));
        } else {
            echo drupal_json_output(array('status' => 'failed'));
        }
    }
}

function validate_exam_post_infor($exam_name,$spend_time,$e_id){
    if( is_exam_duplicate_naming($exam_name,$e_id)){
        form_set_error('', t("该试题名称已经存在，请使用其他名称。"));
        return true;
    }
    
    if(is_available_spend_time($spend_time)){
        form_set_error('', t("花费时间需为正整数，请校验后重新输入。"));
        return true;
    }
    return false;
}

function is_available_spend_time($time){
    $pattern = "/^[1-9]\d*$/";
    if( !preg_match( $pattern, $time )){
        return true;
    } 
    return false;
}

function is_exam_duplicate_naming($name,$e_id){
    $query = "select count(exam_id)>0 is_duplicate from review360_exam
            where exam_id != $e_id and exam_name = '$name'";
    $result = db_query($query)->fetchObject();
    return $result->is_duplicate;
}

function get_exam_list_ajax(){
    $list = get_exam_list();
    $rst = new stdClass();
    if ($list) {
        $rst->status = 'success';
        $rst->list = $list;
        drupal_json_output($rst);
    } else {
        $rst->status = 'failed';
        drupal_json_output($rst);
    }
}

function get_exam_list(){
    $query = "select re.*,ceil(count(wc.cid)/2) number from
            review360_exam re left join 
            webform_component wc on re.nid = wc.nid
            and wc.type = 'select'
            group by re.nid";
    $result = db_query($query)->fetchAll();
    return $result;
}

function get_exam_by_id($exam_id){
    $query = "select * from  review360_exam where exam_id = $exam_id";
    $result = db_query($query)->fetchObject();
    return $result;
}

function save_new_exam_group_ajax(){
    $exam_name = $_POST['exam_name'];
    $nid = create_new_webform_node($exam_name);
    $field_array = array();
    $field_array['exam_name'] = $exam_name;
    $field_array['nid'] = $nid;
    $field_array['exam_key'] = random_string(10);
    $field_array['create_date'] = time();
    $field_array['update_date'] = time();
    $rst = db_insert('review360_exam')->fields($field_array)->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}

function create_new_webform_node($exam_name){
    $node = new stdClass();
    $node->type = "webform";
    $node->title = $exam_name;
    $node->language = LANGUAGE_NONE;
    $node->uid = 1; // Or any id you 
// $random_string = random_string(10);
// $node->path = array('alias' => $random_string);
    $node->comment = 1;
    
    node_object_prepare($node);
    $node = node_submit($node);
    node_save($node);
    return $node->nid;
}

function prepareExamClass($args) {
    $exam = new stdClass();
    if ($args && $args['build_info'] && $args['build_info']['args'])
        $exam = $args['build_info']['args'][0];
    return $exam;
}

function insertWebFormCompents($component,$exam,$pid){
    $node = node_load($exam->node_id);
    $cid = $component->cid;
   
    $node->webform['components'][$cid] = array();
    $node->webform['components'][$cid]['nid'] = $exam->node_id;
    $node->webform['components'][$cid]['cid']= $cid;
    $node->webform['components'][$cid]['pid']= $pid;
    $node->webform['components'][$cid]['form_key']= $exam->exam_key.'_'.$cid.'_'.$pid;
    $node->webform['components'][$cid]['name']= $component->name;
    $node->webform['components'][$cid]['type']= $component->type;
    $node->webform['components'][$cid]['value']= $component->value;
    $node->webform['components'][$cid]['extra'] = $component->extra;
    $node->webform['components'][$cid]['weight'] = $component->weight;
    $node->webform['components'][$cid]['required'] = $component->required;
    $node->webform['components'][$cid]['page_num'] = $component->page_num;
    
    node_save($node);
    return 1;
}

function prepareComponent($name,$items,$type,$weight,$page_num){
    $component = new stdClass();
    $component->name = $name;
    $component->type = $type;
    $component->value = "";
    
    if($weight == 0){
         $component->extra = array(
            "items"=>$items,
            "multiple"=>0,
            "title_display"=> "before",
            "private" => 0,
        );
    } else {
        $component->extra =$items;
    }
   
    $component->weight = $weight;
    $component->required = 1;
    $component->page_num = $page_num;
    return $component;
}

function review360_exam_upload_form($form_state, $args) {
    $form = array();
    $exam = prepareExamClass($args);
    
    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['file_upload'] = array(
        '#type' => 'file',
        '#prefix' => '<div class="col-md-12 form-line"><div class="input-group">',
    );

    $form['exam_id'] = array('#type' => 'hidden', '#value' => $exam->exam_id);
    $form['node_id'] = array('#type' => 'hidden', '#value' => $exam->nid);
    $form['exam_key'] = array('#type' => 'hidden', '#value' => $exam->exam_key);
    $form['submit_upload'] = array(
        '#type' => 'submit',
        '#value' => '上传',
        '#prefix' => '<span class="input-group-btn">',
        '#attributes' => array(
            'class' => array(
                'btn btn-primary',
            ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'title'=>'新问卷将会覆盖原有问卷，请先导出修改后再上传。'
        ),
    );

    $form['submit_reset'] = array(
        '#type' => 'button',
        '#value' => '清空',
    );

    $count = exam_has_questions($exam->nid);
    
    if ($count == 0) {
        $form['submit_export'] = array(
            '#type' => 'button',
            '#value' => '导出',
            '#attributes' => array(
                'class' => array(
                    'btn btn-warning',
                ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'title'=>'该问卷尚未有问题，请先上传。'
            ),
            '#suffix' => '</span></div></div>',
        );
    } else {
        $form['submit_export'] = array(
            '#type' => 'button',
            '#value' => '导出',
            '#attributes' => array(
                'class' => array(
                    'btn btn-success',
                ),
            ),
            '#suffix' => '</span></div></div>',
        );
    }


    return $form;
}

function exam_has_questions($nid){
    $query = "select count(cid) from "
            ."webform_component where nid = $nid";
    $result = db_query($query)->fetchColumn();
    return $result;
}


function review360_exam_upload_form_validate($form, &$form_state) {
    $file = file_save_upload('file_upload', array(
        'file_validate_is_excel' => array(),
        'file_validate_extensions' => array('CSV XLSX XLS'),
    ));

    if ($file) {
        if ($file = file_move($file, 'public://')) {
            $form_state['storage']['file'] = $file;
        } else {
            form_set_error('file', t("写入文件失败，请检查权限。"));
        }
    } else {
        form_set_error('file', t('文件上传失败，请检查文件类型。'));
    }
}

function review360_exam_upload_form_submit($form, &$form_state) {
    $file = $form_state['storage']['file'];
    unset($form_state['storage']['file']);
    $file->status = FILE_STATUS_PERMANENT;
    $file_path = drupal_realpath($file->uri);
    
    $exam = new stdClass();
    $exam->exam_key = $form['exam_key']['#value'];
    $exam->exam_id = $form['exam_id']['#value'];
    $exam->node_id = $form['node_id']['#value'];
//    $form['group_id']
    upload_exam_file($file_path,$exam);
    file_delete($file);
}

function upload_exam_file($file_path,$exam) {
    $next_line = "\n ";
    
    $objPHPExcel = PHPExcel_IOFactory::load($file_path);
    $currentSheet = $objPHPExcel->getActiveSheet();
    $allRow = $currentSheet->getHighestRow();
    $allColumn = $currentSheet->getHighestColumn();

    $count = 0;
    $cid = 1;
    $pid = 1;
    $page_num = 1;
    $idx = 1;
    for ($currentRow = 2; $currentRow <= $allRow; $currentRow++) {
        $row = new stdClass();
        for ($currentColumn = 'A'; $currentColumn <= $allColumn; $currentColumn++) {
            $address = $currentColumn . $currentRow;
            $value = $currentSheet->getCell($address)->getValue();
            if ($currentColumn == 'A') {
                $row->exam_name = $value . '';
            } else if ($currentColumn == 'B') {
                $row->type = $value . '';
            } else if ($currentColumn == 'C') {
                $row->answer_a = $value . '';
            } else if ($currentColumn == 'D') {
                $row->answer_b = $value . '';
            } else if ($currentColumn == 'E') {
                $row->answer_c = $value . '';
            } else if ($currentColumn == 'F') {
                $row->answer_d = $value . '';
            } else if ($currentColumn == 'G' && !empty($value)) {
                $row->answer_e = $value . '';
            }
        }
        $is_special = false;
        if(isset($row->answer_e) && !empty($row->answer_e)){
            $items = $row->answer_a. $next_line
                        .$row->answer_b. $next_line
                        .$row->answer_c. $next_line
                        .$row->answer_d. $next_line
                        .$row->answer_e;
        } else {
            $items = $row->answer_a. $next_line
                        .$row->answer_b. $next_line
                        .$row->answer_c. $next_line
                        .$row->answer_d;
            $is_special = true;
        }
        
        if(!$is_special){
           $count = insert_exam_component($row,$items,$cid++,$exam,$count,0);
           $idx ++;
        } else{
           $page_num = $currentRow -1;
           $row->type = 'fieldset' ;
           $row->weight = $page_num;
           $row->page_num = $page_num;
           $empty_items = array();
           $count = insert_exam_component($row,$empty_items,$cid++,$exam,$count,0);
           $pid = $cid - 1;
           $row->type = 'select' ;
           $row->weight = 0;
           $row->exam_name ='最符合';
           $count = insert_exam_component($row,$items,$cid++,$exam,$count,$pid);
           $row->exam_name = '最不符合'; 
           $count = insert_exam_component($row,$items,$cid++,$exam,$count,$pid);
           
           if($currentRow  != $allRow){
            $row->type = 'pagebreak' ;
            $row->exam_name ='pageblack';
            $empty_items['prev_page_label']='上一页';
            $empty_items['next_page_label']='下一页';
            $empty_items['page_description']='';
            $empty_items['private']='';
            
            $row->weight = $page_num;
            
            $count = insert_exam_component($row,$empty_items,$cid++,$exam,$count,0);
            $idx ++;
           }
        }
    }
    drupal_set_message(t("成功插入 $idx 道题。"));
}

function insert_exam_component($row,$items,$cid,$exam,$count,$pid){
    $component = prepareComponent($row->exam_name,
                        $items,$row->type,$row->weight,$row->page_num);
    $component->cid = $cid++;

    if(insertWebFormCompents($component,$exam,$pid)>0){
        return ++$count;
    }
    return $count;
}


function insert_exam($row,$exam_id) {
    $field_array = array();
    $field_array['exam_id'] = $exam_id;
    $field_array['exam_name'] = $row->exam_name;
//    $field_array['exam_email'] = $row->exam_email;
    $field_array['create_date'] = time();
    $field_array['update_date'] = time();
    $rst = db_insert('review360_exam')->fields($field_array)->execute();
    return $rst;
}

function review360_exam_del_ajax(){
    $exam_id = $_POST['exam_id'];
    $exam = get_exam_by_id($exam_id);
    node_delete($exam->nid);
    $del_exam = db_delete('review360_exam')
        ->condition('exam_id', $exam_id)
        ->execute();
    cache_clear_all();
     if ($del_exam>0) {
        echo drupal_json_output(array('status' => 'success'));
        drupal_set_message(t("问卷删除成功。"));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
        drupal_set_message(t("问卷删除失败，请联系管理员。"),"error");
    }
}

function export_exam_file($exam_id){
        $exam = get_exam_by_id($exam_id);
        $fileName = $exam->exam_name;
        $date = date("Y_m_d", time());
        $fileName .= "_{$date}.xls";

        $nid = $exam->nid;
        $node = node_load($nid);
        $components = select_all_exam_questions_data_by_components($node->webform['components']);

        $headArr = array( "question", "type","a","b","c","d");
        $objPHPExcel = new PHPExcel();
//        $objProps = $objPHPExcel->getProperties();
        $key = ord("A");
        foreach ($headArr as $v) {
            $colum = chr($key);
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue($colum . '1', $v);
            $key += 1;
        }
       
        $column = 2;
        $objActSheet = $objPHPExcel->getActiveSheet();
        foreach ($components as $key => $rows) {
            $span = ord("A");
            foreach ($rows as $keyName => $value) {
                $j = chr($span);
                $objActSheet->setCellValue($j . $column, trim($value));
                $span++;
            }
            $column++;
        }
        
        review360_base_export_file($fileName, $objPHPExcel);
   
   
}

function select_all_exam_questions_data_by_components($comonpents){
    $result = array();
    $item = null;
    $items = null;
    $is_value = false;
    $idx = 1;
    foreach($comonpents as $comonpent){
        if($comonpent['type'] !='fieldset'){
            if(!$is_value){
                continue;
            } else {
                if($comonpent['type']!='select'){
                    continue;
                }
                $item = new stdClass();
//                $item->name = $comonpent['name'];
                $item->name = $idx++;
                $item->type = $comonpent['type'];
                $items = breakItems($comonpent['extra']['items']);
                if (count($items) == 4) {
                    $item->a = $items[0];
                    $item->b = $items[1] ;
                    $item->c = $items[2];
                    $item->d = $items[3] ;
                } else {
                    $item->a = $items[0] . $items[1];
                    $item->b = $items[2] . $items[3];
                    $item->c = $items[4] . $items[5];
                    $item->d = $items[6] . $items[7];
                }

                $result[] = $item;
            }
        } else {
            $is_value = true;
        }
    }
    $idx = 1;
    $rst = array();
    $item = null;
    for($i=0;$i<count($result);$i=$i+2){
        $item = $result[$i];
        $item->name = $idx;
        $rst[] = $item;
        $idx++;
    }
    return $rst;
}

function breakItems($items_str){
    $items = preg_split('/([.\n]+)/i',$items_str);
//    $items = split('\n',$items_str);
    return $items;
}