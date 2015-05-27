<?php
require_once dirname(__FILE__) . '/../../lib/PHPExcel/PHPExcel/IOFactory.php';

function review360_survey_management_view(){
    $action_name = theme('review360_survey_view');
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review360_survey_edit($survey_id){
    $action_name = theme('review360_survey_edit',array('survey_id'=>$survey_id));
    $pageContent = theme('right_content', 
            array('page_content' => $action_name,
                  'is_html' => true));
    return $pageContent;
}

function  review360_survey_export($survey_id){
    $survey = get_survey_by_id($survey_id);
    $fileName = $survey->survey_name.'_user_key';
    $date = date("Y_m_d", time());
    $fileName .= "_{$date}.xls";
    
   export_user_key($survey,$fileName);
}

function export_user_key($survey,$fileName){

   $user_keys =get_user_keys($survey->survey_id);
   $headArr = array( "key", "url");
    $objPHPExcel = new PHPExcel();
    $key = ord("A");
    foreach ($headArr as $v) {
        $colum = chr($key);
        $objPHPExcel->setActiveSheetIndex(0)->setCellValue($colum . '1', $v);
        $key += 1;
    }
       
    $column = 2;
    $objActSheet = $objPHPExcel->getActiveSheet();
    foreach ($user_keys as $key => $rows) {
        $span = ord("A");
        foreach ($rows as $keyName => $value) {
            $j = chr($span);
            $objActSheet->setCellValue($j . $column, $value);
            $span++;
        }
        $column++;
    }

    review360_base_export_file($fileName, $objPHPExcel);
}


//function prepareSurveyClass($args) {
//    $group = new stdClass();
//    if ($args && $args['build_info'] && $args['build_info']['args'])
//        $group = $args['build_info']['args'][0];
//    return $group;
//}


function review360_survey_edit_form($form_state, $args) {
    $form = array();
    $survey = prepare_form_stdClass($args);
    $form['survey_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">调查名称</span>',
        '#suffix' => '</div>',
        '#default_value' => $survey->survey_name,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
        ),
    );
    
    
    $form['survey_id'] = array('#type' => 'hidden', '#default_value' => $survey->survey_id);
    
    $form['survey_key'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">识别代码</span>',
        '#suffix' => '</div></div>',
        '#default_value' => $survey->survey_key,
         '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'识别代码',
            'title'=>'调查代码，建议使用拼音缩写，不能重复。'
        ),
        
    );
    
    $form['survey_user_num'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">参与人数</span>',
        '#suffix' => '</div>',
        '#default_value' => $survey->survey_user_num,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'参与人数',
            'title'=>'参与调查的人数。'
        ),
        
    );
    
    $form['survey_status'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">调查状态</span>',
        '#suffix' => '</div></div>',
        '#default_value' =>prepare_survey_status_str( $survey->survey_status),
         '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'调查状态',
            'title'=>'调查当前状态，只有未开始的调查可以修改。'
        ),
        
    );
    
    $form['survey_start_date'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
             <div class="input-group date form_date " data-date="2015-01-01" 
             data-date-format="yyyy-mm-dd" data-link-field="dtp_start_date">
             <span class="input-group-addon" id="sizing-addon1">开始时间</span>',
        '#suffix' => '
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-th"></span></span>
                </div>
                <input type="hidden" id="dtp_start_date" value="" /></div>',
        '#default_value' => prepare_timestamp_to_str($survey->start_date),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'开始时间',
            'title'=>'调查开始时间。'
        ),
        
    );
    
     $form['survey_end_date'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6">
             <div class="input-group date form_date " data-date="2015-01-01" 
             data-date-format="yyyy-mm-dd" data-link-field="dtp_start_date">
             <span class="input-group-addon" id="sizing-addon1">结束时间</span>',
        '#suffix' => '
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-th"></span></span>
                </div>
                <input type="hidden" id="dtp_start_date" value="" /></div></div>',
          '#default_value' => prepare_timestamp_to_str($survey->end_date),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'结束时间',
            'title'=>'调查结束时间。'
        ),
        
    );
     
    
    $form['survey_exams_str'] = array(
       '#type' => 'textfield',
       '#multiple' => TRUE,
       '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">问卷名称</span>',
       '#suffix' => '
                <span class="input-group-addon"><span class="exam_remove_btn btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class=" btn-icon glyphicon glyphicon-th-list"></span></span>
                </div>',
       '#default_value' => $survey->survey_nid_name,
       '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'',
            'title'=>'该调查所包含的问卷名。'
        ),
//        '#default_values' => 14,
    );
    
     $form['survey_exams_nid'] = array(
       '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">问卷编号</span>',
        '#suffix' => '<span class="input-group-addon">'
                    . '<span class="exam_remove_btn btn-icon glyphicon glyphicon-remove"></span></span>'
                    . '</div></div>',
         '#default_value' => $survey->survey_nids,
         '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'',
            'title'=>'该调查所包含的问卷代码。'
        ),
    );
   
    if ($survey->survey_status == 0) {
        $form['submit'] = array(
            '#type' => 'submit',
            '#default_value' => '保存草稿',
            '#prefix' => '<div class="col-md-12 form-line">'
            . '<div class="btn-group col-md-6  " role="group" aria-label="" >'
            . '<span class="input-group-btn">',
            '#attributes' => array(
                'class' => array(
                    'btn btn-primary',
                ),
            ),
        );

        $form['submit_active'] = array(
            '#type' => 'submit',
            '#default_value' => '保存修改并激活调查',
            '#attributes' => array(
                'class' => array(
                    'btn btn-success',
                ),
                'data-loading-text' => '调查激活中...',
                'data-toggle' => 'tooltip',
                'data-placement' => 'bottom',
                'title' => '激活调查将生成调查模板并生成用户代码，激活后的调查到达开始时间后会自动开始。激活后的调查不可修改。'
            ),
        );
        $form['submit_reset'] = array(
            '#type' => 'button',
            '#default_value' => '重新载入',
            '#suffix' => '</span></div></div>',
            '#attributes' => array(
                'class' => array(
                    'btn btn-warning',
                ),
            ),
        );
    } else  if ($survey->survey_status == 1) {
        $form['submit_export'] = array(
            '#type' => 'button',
            '#default_value' => '导出用户代码',
            '#attributes' => array(
                'class' => array(
                    'btn btn-success',
                ),
                'data-loading-text'=>'准备导出...',
                'data-toggle' =>'tooltip',
                'data-placement'=>'bottom',
                'title'=>'导出用户代码，只有已激活的调查可以导出用户代码。'
            ),
            '#prefix' => '<div class="col-md-12 form-line">'
            . '<div class="btn-group col-md-6  " role="group" aria-label="" >'
            . '<span class="input-group-btn">',
            '#suffix' => '',
        ); 
        
        $form['submit_generate_user_exam'] = array(
            '#type' => 'submit',
            '#default_value' => '生成用户问卷',
            '#attributes' => array(
                'class' => array(
                    'btn btn-primary',
                ),
                'data-loading-text'=>'准备导出...',
                'data-toggle' =>'tooltip',
                'data-placement'=>'bottom',
                'title'=>'生成用户问卷，这个过程可能会花费较长时间。'
            ),
            '#suffix' => '</span></div></div>',
        ); 
    } else if($survey->survey_status == 2){
        $form['submit_export'] = array(
            '#type' => 'button',
            '#default_value' => '导出用户代码',
            '#attributes' => array(
                'class' => array(
                    'btn btn-success',
                ),
                'data-loading-text'=>'准备导出...',
                'data-toggle' =>'tooltip',
                'data-placement'=>'bottom',
                'title'=>'导出用户代码，只有已激活的调查可以导出用户代码。'
            ),
            '#prefix' => '<div class="col-md-12 form-line">'
            . '<div class="btn-group col-md-6  " role="group" aria-label="" >'
            . '<span class="input-group-btn">',
            '#suffix' => '</span></div></div>',
        ); 
    }
    
    return $form;
}

function get_selectable_exam(){
    $query = "select re.*,count(wc.cid) number from
            review360_exam re inner join 
            webform_component wc on re.nid = wc.nid
            group by re.nid";
    $result = db_query($query)->fetchAll();
    
    return $result;
}

function review360_survey_edit_form_validate($form, &$form_state) {
    if (empty($form_state['values']['survey_name'])) {
        form_set_error('survey_name',t("调查名称不能为空。"));
    }
    
    if(!validate_survey_name($form_state['values']['survey_name'],$form_state['values']['survey_id'])){
        form_set_error('survey_name', t('调查名称重复。'));
    }
    
    if (empty($form_state['values']['survey_key'])) {
         form_set_error('survey_key',t("调查名称不能为空。"));
    } else   if(!validate_survey_key($form_state['values']['survey_key'],$form_state['values']['survey_id'])){
        form_set_error('survey_key', t('调查识别码重复。'));
    }
    
    $pattern = "/^[0-9]\d*$/";
    if( !preg_match( $pattern, $form_state['values']['survey_user_num'] )){
        form_set_error('survey_user_num', t('参与人员必须为正整数。'));
    } 
    if (empty($form_state['values']['survey_start_date'])) {
        form_set_error('survey_start_date',t('调查开始时间不能为空。'));
    }
   
    if (empty($form_state['values']['survey_end_date'])) {
        form_set_error('survey_end_date', t('调查结束时间不能为空。'));
    }
    if(!validate_survey_start_end_date($form_state['values']['survey_start_date'],
                                        $form_state['values']['survey_end_date'])){
        form_set_error('survey_start_date', t(''));
        form_set_error('survey_end_date', t('调查的结束时间应该晚于开始时间。'));
    }
    
    if (empty($form_state['values']['survey_exams_nid'])
            || empty($form_state['values']['survey_exams_str'])) {
        form_set_error('survey_exams_nid',t(''));
        form_set_error('survey_exams_str',t('请为该调查选择问卷。'));
    }
}

function validate_survey_key($key,$id){
    $query = "select count(survey_id) num from  review360_survey "
            . "where survey_key = '$key' and survey_id !=$id";
    $result = db_query($query)->fetchObject();
    if($result->num >0) return false;
    return true;
}

function validate_survey_name($name,$id){
    $query = "select count(survey_id) num from  review360_survey "
            . "where survey_name = '$name' and survey_id !=$id";
    $result = db_query($query)->fetchObject();
    
    if($result->num >0) return false;
    return true;
}

function validate_survey_start_end_date($start,$end){
    $start_val = prepare_date_to_timestamp($start);
    $end_val = prepare_date_to_timestamp($end);
    if($start_val>=$end_val) return false;
    return true;
}

function review360_survey_edit_form_submit($form, &$form_state) {
    $survey = $form_state['values'];
    if('保存草稿' === $form_state['values']['op']){
       store_draft_update($survey);
    } else if('保存修改并激活调查' === $form_state['values']['op']){
        store_draft_update($survey);
        if(active_survey_by_id($survey['survey_id'],$survey['survey_exams_nid'],$survey['survey_key']))   {
            $count = create_survey_user_key($survey['survey_user_num'],$survey['survey_id'],$survey['survey_key']);
            drupal_set_message(t("调查激活成功,生成用户代码 $count 条。"));
        }
        else{
            drupal_set_message(t("调查激活失败，请重试。"),'error');
        }
    } else if('生成用户问卷' === $form_state['values']['op'] ){
        $counter = genrate_user_exam($survey['survey_id']);
        db_update('review360_survey')
            ->fields(array(
                  'survey_status' => 2,
                  'update_date' => time(),
              ))
            ->condition('survey_id', $survey['survey_id'])
            ->execute();
        drupal_set_message(t("生成用户问卷 $counter 份。"));
    }
}

function store_draft_update($survey){
     $one_day_delay = 24*60*60;
        db_update('review360_survey')
            ->fields(array(
                  'survey_name' => $survey['survey_name'],
                  'survey_key' => $survey['survey_key'],
                  'survey_user_num' => $survey['survey_user_num'],
                  'survey_nids' => $survey['survey_exams_nid'],
                  'survey_nid_name' => $survey['survey_exams_str'],
                  'start_date' => prepare_date_to_timestamp($survey['survey_start_date']),
                  'end_date' => prepare_date_to_timestamp($survey['survey_end_date'])+$one_day_delay,
                  'update_date' => time(),
              ))
            ->condition('survey_id', $survey['survey_id'])
            ->execute();
    
    drupal_set_message(t("调查更新成功。"));
}

function genrate_user_exam($s_id){
    global $base_url;
    $survey = get_survey_by_id($s_id);
    $old_node = node_load($survey->nid);
    $users = get_survey_user_exam_list($s_id);
    $counter = 0;
    foreach($users as $user){
        $node = null;
        $exam_name = $survey->survey_name.'_'.$user->su_id;
        $node = prepare_node_main($exam_name);
        $node->webform = array();
        
        $node->webform['components'] = $old_node->webform['components'];
        
        $node->webform['allow_draft'] = 1;
        $node->webform['redirect_url'] = 'interviewer/survey/submitted/'.$user->survey_user_key;
//        $node->path = array('alias' => $user->survey_user_key);
        node_object_prepare($node);
        $node = node_submit($node);
        node_save($node);
        if($node->nid > 0){
            update_survey_user_nid($user->su_id,$node->nid);
            $counter++;
        }
    }
    return $counter;
}

function update_survey_user_nid($su_id,$nid){
    db_update('review360_survey_user')
            ->fields(array(
                  'nid' => $nid,
                  'update_date' => time(),
              ))
            ->condition('su_id', $su_id)
            ->execute();
}

function active_survey_by_id($id,$exam_nids,$survey_key){
     $nid = create_survey_exam_template($exam_nids,$survey_key);
     $rst = db_update('review360_survey')
        ->fields(array(
              'nid' =>$nid,
              'survey_status' => 1,
              'update_date' => time(),
          ))
        ->condition('survey_id', $id)
        ->execute();
     if($rst > 0) return true;
     return false;
}


function create_survey_exam_template($exam_nids,$survey_key){
    $ids = explode(',',$exam_nids);
    $exam_name = $survey_key.'_exam_template';
//    $items = split('\n',$items_str);
    $node = prepare_node_main($exam_name);
    $tmp_node = null;
    $components = null;
    $node_component = array();
    $cid = 1;
    foreach($ids as $id){
        $tmp_node = node_load($id);
        $components = $tmp_node->webform['components'];
        foreach($components as $component){
            $node_component[] = prepare_survey_exam_template_component($component,$survey_key,$cid);
            $cid++;
        }
    }
    $node->webform['components'] = $node_component;
    node_object_prepare($node);
    $node = node_submit($node);
    node_save($node);
    return $node->nid;
}

function prepare_survey_exam_template_component($old_component,$survey_key,$cid){
    $component = array();
    $component['name'] = $old_component['name'];
    $component['type'] = $old_component['type'];
    $component['value'] = $old_component['value'];
    $component['pid'] = $old_component['pid'];
    $component['form_key'] = $survey_key.'_template'.'_'.$cid;
    $component['extra'] = $old_component['extra'];
    $component['weight'] = $old_component['weight'];
    $component['required'] = $old_component['required'];
    return $component;
}

function prepare_node_main($exam_name){
    $node = new stdClass();
    $node->type = "webform";
    $node->title = $exam_name;
    $node->language = LANGUAGE_NONE;
    $node->uid = 1; // Or any id you 
    $node->comment = 1;
    return $node;
}

function insertWebFormCompents($component,$exam){
    $node = node_load($exam->node_id);
    $cid = $component->cid;
   
    $pid = 0;
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
    node_save($node);
    return 1;
}


function prepare_survey_class($args){
    $survey = new stdClass();
    if ($args && $args['build_info'] && $args['build_info']['args'])
        $survey = $args['build_info']['args'][0];
    return $survey;
}

function review360_survey_change_name_ajax(){
    $survey_name = $_POST['survey_name'];
    $survey_id = $_POST['survey_id'];
    $rst = db_update('review360_survey')
      ->fields(array(
        'survey_name' => $survey_name,
        'update_date' => time(),
      ))
      ->condition('survey_id', $survey_id)
      ->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}
function save_new_survey_ajax(){
    $survey_name = $_POST['survey_name'];
   
//    $nid = create_new_webform_node($survey_name);
    $field_array = array();
    $field_array['survey_name'] = $survey_name;
    $field_array['survey_key'] = random_string(4);
    $field_array['create_date'] = time();
    $field_array['update_date'] = time();
    $rst = db_insert('review360_survey')->fields($field_array)->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}

function review360_survey_del_ajax(){
    $survey_id = $_POST['survey_id'];
    $del_survey = db_delete('review360_survey')
        ->condition('survey_id', $survey_id)
        ->execute();
     if ($del_survey>0) {
        echo drupal_json_output(array('status' => 'success'));
        drupal_set_message(t("调查删除成功。"));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
        drupal_set_message(t("调查删除失败，请联系管理员。","error"));
    }
}

function get_survey_list_ajax(){
    $list = get_survey_list();
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

function get_survey_list(){
    $query = "select * from
            review360_survey  ";
    $result = db_query($query)->fetchAll();
    foreach($result as $survey){
        $survey->survey_status_str = prepare_survey_status_str($survey->survey_status);
    }
    return $result;
}

function prepare_survey_status_str($status){
    if($status == 0) return "待编辑";
    else  if($status == 1) return "已激活";
    else  if($status == 2) return "已生成问卷";
    else  if($status == 50) return "已开始";
    else if($status == 100) return "已结束";
}


function get_generated_survey_user($survey_id){
    $query = "select count(su_id) num from review360_survey_user
                where survey_id =  $survey_id";
    $result = db_query($query)->fetchObject();
    return $result->num ;
}

function create_survey_user_key($num,$s_id,$s_key){
    $count = 0;
    for($i=0;$i<$num;$i++){
        $field_array = array();
        $field_array['survey_id'] = $s_id;
        $field_array['survey_user_key'] = $s_key.'_'.random_string(8);
        $field_array['create_date'] = time();
        $field_array['update_date'] = time();
        if(db_insert('review360_survey_user')->fields($field_array)->execute()>0)
            $count++;
    }
    return $count;
}

function get_user_keys($s_id){
    $query = "select survey_user_key, 'http://' url  from review360_survey_user
                where survey_id =  $s_id";
    $result = db_query($query)->fetchAll();
    return $result ;
}

function get_survey_user_exam_list($s_id){
    $query = "select *  from review360_survey_user"
            . " where survey_id =  $s_id";
    $result = db_query($query)->fetchAll();
    return $result ;
}