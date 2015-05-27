<?php

require_once dirname(__FILE__) . '/../../lib/PHPExcel/PHPExcel/IOFactory.php';

function review360_usermanage_call_back() {
    $action_name = theme('review360_base_config');
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review360_group_edit($group_id){
    $action_name = theme('review360_group_edit',array('group_id'=>$group_id));
    $pageContent = theme('right_content', 
            array('page_content' => $action_name,
                  'is_html' => true));
    return $pageContent;
}

function review360_group_del_ajax(){
    $group_id = $_POST['group_id'];
    $del_user = db_delete('review360_user')
        ->condition('group_id', $group_id)
        ->execute();
    $del_group = db_delete('review360_user_group')
        ->condition('group_id', $group_id)
        ->execute();
    
    if ($del_group>0) {
        echo drupal_json_output(array('status' => 'success'));
         drupal_set_message(t("用户组删除成功，并成功删除 $del_user 位用户。"));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
        drupal_set_message(t("用户组删除失败，请联系管理员。","error"));
    }
   
}

function review360_group_change_name_ajax(){
    $group_name = $_POST['group_name'];
    $group_id = $_POST['group_id'];
    $rst = db_update('review360_user_group')
      ->fields(array(
        'group_name' => $group_name,
        'updatedate' => time(),
      ))
      ->condition('group_id', $group_id)
      ->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}

//function prepareGroupClass($args) {
//    $group = new stdClass();
//    if ($args && $args['build_info'] && $args['build_info']['args'])
//        $group = $args['build_info']['args'][0];
//    return $group;
//}


function review360_user_upload_form($form_state, $args) {
    $form = array();
    $group = prepare_form_stdClass($args);
    
    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['file_upload'] = array(
        '#type' => 'file',
        '#prefix' => '<div class="input-group">',
    );

    $form['group_id'] = array('#type' => 'hidden', '#value' => $group->group_id);
    
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
            'title'=>'新用户将会覆盖原有用户，请先导出修改后再上传。'
        ),
    );

    $form['submit_reset'] = array(
        '#type' => 'button',
        '#value' => '清空',
    );
    
    $form['submit_export'] = array(
        '#type' => 'button',
        '#value' => '导出',
        '#attributes' => array(
            'class' => array(
                'btn btn-success',
            ),
        ),
        '#suffix' => '</span></div>',
    );
    return $form;
}

function review360_user_upload_form_validate($form, &$form_state) {
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

function review360_user_upload_form_submit($form, &$form_state) {
    $file = $form_state['storage']['file'];
    unset($form_state['storage']['file']);
    $file->status = FILE_STATUS_PERMANENT;
    $file_path = drupal_realpath($file->uri);
    $group_id = $form['group_id']['#value'];
//    $form['group_id']
    upload_user_file($file_path,$group_id);
    file_delete($file);
}

function upload_user_file($file_path,$group_id) {
    $objPHPExcel = PHPExcel_IOFactory::load($file_path);
    $currentSheet = $objPHPExcel->getActiveSheet();
    $allRow = $currentSheet->getHighestRow();
    $allColumn = $currentSheet->getHighestColumn();

    $count = 0;
    for ($currentRow = 2; $currentRow <= $allRow; $currentRow++) {
        $row = new stdClass();
        for ($currentColumn = 'A'; $currentColumn <= $allColumn; $currentColumn++) {
            $address = $currentColumn . $currentRow;
            $value = $currentSheet->getCell($address)->getValue();
            if($currentColumn == 'A')
                $row->user_name = $value . '';
            else if($currentColumn == 'B')
                $row->user_email = $value . '';
        }
        if(insert_user_by_group($row,$group_id)>0);
            $count++;
    }
    drupal_set_message(t("成功插入 $count 位用户。"));
}

function insert_user_by_group($row,$group_id) {
    $field_array = array();
    $field_array['group_id'] = $group_id;
    $field_array['user_name'] = $row->user_name;
    $field_array['user_email'] = $row->user_email;
    $field_array['createdate'] = time();
    $field_array['updatedate'] = time();
    $rst = db_insert('review360_user')->fields($field_array)->execute();
    return $rst;
}



function prepare_data() {
    $file_path = drupal_get_path('module', 'accountinfo_base') . '/lib/PHPExcel/example.xlsx';
    $objPHPExcel = PHPExcel_IOFactory::load($file_path);
    $currentSheet = $objPHPExcel->getActiveSheet();
    $allRow = $currentSheet->getHighestRow();
    $allColumn = $currentSheet->getHighestColumn();

    $rows = array();
    for ($currentRow = 2; $currentRow <= $allRow; $currentRow++) {
        $row = new stdClass();
        for ($currentColumn = 'A'; $currentColumn <= $allColumn; $currentColumn++) {
            $address = $currentColumn . $currentRow;
            $value = $currentSheet->getCell($address)->getValue();
            $row->$currentColumn = $value . '';
        }
        $rows[] = $row;
    }
    return $rows;
}

function export_user_file($group_id) {
    $group = get_group_by_id($group_id);
    $fileName = $group->group_name;
    $date = date("Y_m_d", time());
    $fileName .= "_{$date}.xls";

    $data = select_all_user_data_by_group_id($group_id);

    $headArr = array( "user name", "user email");
    $objPHPExcel = new PHPExcel();
//    $objProps = $objPHPExcel->getProperties();
    $key = ord("A");
    foreach ($headArr as $v) {
        $colum = chr($key);
        $objPHPExcel->setActiveSheetIndex(0)->setCellValue($colum . '1', $v);
        $key += 1;
    }

    $column = 2;
    $objActSheet = $objPHPExcel->getActiveSheet();
    foreach ($data as $key => $rows) {
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

function select_all_user_data_by_group_id($group_id){
    $query = "select ru.user_name,ru.user_email from
            review360_user ru where group_id = $group_id
             ";
    $result = db_query($query)->fetchAll();
    return $result;
}

function save_new_user_group_ajax() {
    $group_name = $_POST['group_name'];
    $field_array = array();
    $field_array['group_name'] = $group_name;
    $field_array['createdate'] = time();
    $field_array['updatedate'] = time();
    $rst = db_insert('review360_user_group')->fields($field_array)->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}

function get_user_group_list_ajax(){
    $result = get_user_group_list();
    $rst = new stdClass();
    if ($result) {
        $rst->status = 'success';
        $rst->list = $result;
        drupal_json_output($rst);
    } else {
        $rst->status = 'failed';
        drupal_json_output($rst);
    }
}

function get_user_group_list() {
    $query = "select rsg.*,count(rs.user_id) number from
            review360_user_group rsg left join 
            review360_user rs on rsg.group_id = rs.group_id
            group by rsg.group_id";
    $result = db_query($query)->fetchAll();
    return $result;
}

function get_group_by_id($id){
    $query = "select rsg.* from
            review360_user_group rsg 
            where rsg.group_id = $id  ";
    $group = db_query($query)->fetchObject();
    return $group;
}