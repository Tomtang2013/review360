<?php
require_once dirname(__FILE__) . '/../../lib/PHPExcel/PHPExcel/IOFactory.php';

function review360_surveymanagement_init_call_back(){
    $pageContent = '<h2>初始化评分标准页！</h2>';
    read_excel_insert();
    return $pageContent;
}

function read_excel_insert(){
    $next_line = "\n ";
    $file_path = drupal_get_path('module','review360_base').'/result_init/result_init.xlsx';
    $objPHPExcel = PHPExcel_IOFactory::load($file_path);
    $currentSheet = $objPHPExcel->getActiveSheet();
    $allRow = $currentSheet->getHighestRow();
    $allColumn = $currentSheet->getHighestColumn();

    
    for ($currentRow = 2; $currentRow <= $allRow; $currentRow++) {
        $row = [];
        for ($currentColumn = 'A'; $currentColumn <= $allColumn; $currentColumn++) {
            $address = $currentColumn . $currentRow;
            $value = $currentSheet->getCell($address)->getValue();
            if ($currentColumn == 'A') {
                $row['rst_type'] = $value . '';
            } else if ($currentColumn == 'B') {
                $row['rst_name'] = $value . '';
            } else if ($currentColumn == 'C') {
                $row['rst_standard'] = $value . '';
            } else if ($currentColumn == 'D') {
                $row['rst_characteristic'] = $value . '';
            } else if ($currentColumn == 'E') {
                $row['rst_advantage'] = $value . '';
            } else if ($currentColumn == 'F') {
                $row['rst_insufficient'] = $value . '';
            } else if ($currentColumn == 'G' ) {
                $row['rst_communicate'] = $value . '';
            }else if ($currentColumn == 'H' ) {
                $row['rst_work_performance']= $value . '';
            }
        }
        insert_review360_user_result($row);
    }
    drupal_set_message(t("评分标准初始化成功!"));
}

function insert_review360_user_result($row){
    $row['rst_create_date'] = time();
    $row['rst_update_date'] = time();
    $rst = db_insert('review360_report_str_result')->fields($row)->execute();
    if ($rst) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}