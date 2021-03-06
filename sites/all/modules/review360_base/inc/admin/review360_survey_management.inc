<?php
require_once dirname(__FILE__) . '/../../lib/PHPExcel/PHPExcel/IOFactory.php';
defined('DEFAULT_WORDPATH') or define('DEFAULT_WORDPATH', 'sites/default/files/generateFiles/');

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

function review360_surveymanagement_generate_report_by_sid($survey_id){
    $rst = array();
    $query = "select rsue.*,rsu.u_name,rsu.u_company_name,rsu.u_department from review360_survey_user_exam rsue  
        inner join review360_survey_user rsu on 
        rsue.s_id = rsu.survey_id and rsue.user_key = rsu.survey_user_key
        where rsue.s_id = $survey_id and rsue.is_submited = 1";
    $exams = db_query($query)->fetchAll();
  
    foreach ($exams as $exam) {  
       
        $exam->rst = generate_survey_result_by_sv($exam);
        $exam->str = generate_survey_rsult_str($exam);
        watchdog("php", $exam->u_name);
        $is_generated = generate_report($exam);
        if ($is_generated) {
            $rst[] = $exam->u_name;
        }
    }
    
    echo drupal_json_output(array('status' => 'success','doc_list'=>$rst));
    
}

function review_survey_report_generate($survey_id){
    $query = "select *  from review360_survey_user_exam where s_id = $survey_id and is_submited = 1";
    $exams = db_query($query)->fetchAll();
    $function = 'generate_survey_user_report_batch';
    $batch = $function($exams);
    batch_set($batch);
}

function review360_survey_report_export($survey_id) {
    $survey = get_survey_by_id($survey_id);
    $file_name = $survey->survey_name . ".zip";
    $src_file_name = $survey_id . ".zip";
    
    $review_folder = DEFAULT_WORDPATH . $survey_id;
    $zip_name = $survey_id.'.zip';
    zip_folder($zip_name,$review_folder,$survey_id);
    
    $get_url = DEFAULT_WORDPATH . $src_file_name;
    $get_url = drupal_realpath($get_url);
    review360_base_export_zip_file($file_name, $get_url);
}

function review360_survey_report_excel_export($survey_id) {
    $survey = get_survey_by_id($survey_id);
    $fileName = $survey->survey_name.'_excel_report';
    $date = date("Y_m_d", time());
    $fileName .= "_{$date}.xls";
    export_survey_excel_report($survey,$fileName);
}

function get_survey_user_information($survey_id){
     $query = "select rs.survey_id,rs.survey_name,rsu.survey_user_key, 
        rsu.u_email,rsu.u_name,rsu.u_sex,rsu.u_company_name,
        rsu.u_p_number,rsu.u_birthday, rsue.exam_nid,
        rsue.is_submited, rsue.nick_name,rsue.is_generate_result 
        from  review360_survey  rs
        inner join review360_survey_user rsu on rs.survey_id = rsu.survey_id
        inner join review360_survey_user_exam rsue on rsue.s_id = rs.survey_id 
        and rsu.survey_user_key = rsue.user_key
        where rs.survey_id = $survey_id
        ";
    $result = db_query($query)->fetchAll();
    return $result;
}

function get_survey_excel_result($survey){
    $sid = $survey->survey_id;
    $exams = get_survey_user_information($sid);
    $results = get_survey_result_by_sid($exams,$sid);
   
    $export_rsts = array();
   
    foreach($results as $key=>$value){
        $export_rst = new stdClass();
        foreach($exams as $exam){
            if($exam->exam_nid == $key){
                $export_rst = $exam;
            }
        }
        
        $export_rst = init_exam_rst($export_rst);
        
        foreach($value->rst as $result){
           switch_stdclass($result,$export_rst);
        }    
        $export_rst->nick_name = $value->nick_name;
        $export_rst->exam_id = $key;
        
        $export_rsts[] = $export_rst;
    }

    return $export_rsts;
}

function init_exam_rst(&$exam){
    $exam->working_d = 0;
    $exam->working_i = 0;
    $exam->working_s = 0;
    $exam->working_c = 0;
    $exam->innate_d = 0;
    $exam->innate_i = 0;
    $exam->innate_s =  0;
    $exam->innate_c =  0;
    $exam->other_d =  0;
    $exam->other_i = 0;
    $exam->other_s =  0;
    $exam->other_c =  0;
    $exam->stress_d =  0;
    $exam->stress_i = 0;
    $exam->stress_s =  0;
    $exam->stress_c = 0;
    return $exam;
}

function switch_stdclass($value,&$rst){
     switch($value->quadrant){
                case "in_working_me" :  return prepare_export_rst_working($value,$rst); 
                case "innate"   :    return prepare_export_rst_innate($value,$rst); 
                case "other"    :    return prepare_export_rst_other($value,$rst); 
                case "stress"   :    return prepare_export_rst_stress($value,$rst); 
            }
}

function prepare_export_rst_working($value, &$rst) {
    $rst->working_d = $value->d;
    $rst->working_i = $value->i;
    $rst->working_s = $value->s;
    $rst->working_c = $value->c;
    return $rst;
}

function prepare_export_rst_innate($value, &$rst){
    $rst->innate_d = $value->d;
    $rst->innate_i = $value->i;
    $rst->innate_s = $value->s;
    $rst->innate_c = $value->c;
    return $rst;
}

function prepare_export_rst_other($value, &$rst){
    $rst->other_d = $value->d;
    $rst->other_i = $value->i;
    $rst->other_s = $value->s;
    $rst->other_c = $value->c;
    return $rst;
}

function prepare_export_rst_stress($value, &$rst){
    $rst->stress_d = $value->d;
    $rst->stress_i = $value->i;
    $rst->stress_s = $value->s;
    $rst->stress_c = $value->c;
    return $rst;
}

function export_excel_result_filter($full_result){
    $rst = array();
    foreach($full_result as $r){
        $new = new stdClass();
        $new->name = $r->u_name;
        $new->survey_user_key = $r->survey_user_key;
        $new->u_sex = $r->u_sex;
        $new->age = calculate_age($r->u_birthday);
        $new->u_p_number = $r->u_p_number;
        $new->u_email = $r->u_email;
        $new->u_company_name = $r->u_company_name;
        
        $new->working_d = $r->working_d;
        $new->working_i = $r->working_i;
        $new->working_s = $r->working_s;
        $new->working_c = $r->working_c;
        $new->innate_d = $r->innate_d;
        $new->innate_i = $r->innate_i;
        $new->innate_s = $r->innate_s;
        $new->innate_c = $r->innate_c;
        $new->other_d = $r->other_d;
        $new->other_i = $r->other_i;
        $new->other_s = $r->other_s;
        $new->other_c = $r->other_c;
        $new->stress_d = $r->stress_d;
        $new->stress_i = $r->stress_i;
        $new->stress_s = $r->stress_s;
        $new->stress_c = $r->stress_c;
        
        $new = prepare_rst_std_value($new);
        $rst[] = $new;
    }
    
    return $rst;
}

function prepare_rst_std_value(&$result){
    $in_working_me = prepare_rst_value("in_working_me",$result->working_d,$result->working_i,$result->working_s,$result->working_c);
    $innate = prepare_rst_value("innate",$result->innate_d,$result->innate_i,$result->innate_s,$result->innate_c);
    $other = prepare_rst_value("other",$result->other_d,$result->other_i,$result->other_s,$result->other_c);
    $stress = prepare_stress_rst_value($in_working_me,$innate);
    if($result->working_d!=0 || $result->working_i!=0 || $result->working_s!=0 || $result->working_c!=0 ){
        $result->working_d = $in_working_me->d_value;
        $result->working_i = $in_working_me->i_value;
        $result->working_s = $in_working_me->s_value;
        $result->working_c = $in_working_me->c_value;
        $result->innate_d = $innate->d_value;
        $result->innate_i = $innate->i_value;
        $result->innate_s = $innate->s_value;
        $result->innate_c = $innate->c_value;
        $result->other_d = $other->d_value;
        $result->other_i = $other->i_value;
        $result->other_s = $other->s_value;
        $result->other_c = $other->c_value;
        $result->stress_d = $stress->d_value;
        $result->stress_i = $stress->i_value;
        $result->stress_s = $stress->s_value;
        $result->stress_c = $stress->c_value;
    }
    return $result;
}

function export_survey_excel_report($survey,$fileName){
    $temp = get_survey_excel_result($survey);
    $results = export_excel_result_filter($temp);

    $headArr = array( "姓名", "通行证","性别","年龄","电话","电子邮箱","公司","D","I","S","C","D","I","S","C","D","I","S","C","D","I","S","C");
    $objPHPExcel = new PHPExcel();
    $key = ord("A");
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue(chr(ord("H")) . '1', "工作角色中的我");
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue(chr(ord("L")) . '1', "天生的我");
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue(chr(ord("P")) . '1', "别人眼中的我");
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue(chr(ord("T")) . '1', "压力下的我");
    foreach ($headArr as $v) {
        $colum = chr($key);
        $objPHPExcel->setActiveSheetIndex(0)->setCellValue($colum . '2', $v);
        $key += 1;
    }
    $column = 3;
    $objActSheet = $objPHPExcel->getActiveSheet();
    foreach ($results as $key => $rows) {
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


function generate_survey_user_report_batch($exams){
  $operations = array();
  foreach($exams as $exam){
      $operations[] = array(
        'generate_survey_user_report_do_batch',
        array(
          $exam,
        ),
      );
  }

    $batch = array(
        'operations' => $operations,
        'finished' => 'generate_survey_user_report_finish',
        'title' => t('报告生成'),
        'init_message' => t('生成中....'),
        'progress_message' => t('已经生成 @current 总共 @total.'),
        'error_message' => t('生成错误请联系管理员.'),
        'file' => drupal_get_path('module', 'review360_base') . '/inc/admin/batch/generate_survey_batch.inc',
    );
    return $batch;
}




function export_user_key($survey,$fileName){
    global $base_url;
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
            if($value == "http://") {
                $value = $base_url.'/?q=interviewer/onboard';
            }
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
        '#suffix' => '</div></div>',
        '#default_value' => $survey->survey_name,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
        ),
    );
    
    
    $form['survey_id'] = array('#type' => 'hidden', '#default_value' => $survey->survey_id);
    $form['survey_key'] = array('#type' => 'hidden', '#default_value' => $survey->survey_key);
//    $form['survey_key'] = array(
//        '#type' => 'textfield',
//        '#prefix' => '
//            <div class="input-group col-md-6">
//            <span class="input-group-addon" id="sizing-addon1">识别代码</span>',
//        '#suffix' => '</div></div>',
//        '#default_value' => $survey->survey_key,
//         '#attributes' => array(
//            'class' => array(
//                'form-control',
//            ),
//            'data-toggle' =>'tooltip',
//            'data-placement'=>'bottom',
//            'placeholder'=>'识别代码',
//            'title'=>'调查代码，建议使用拼音缩写，不能重复。'
//        ),
//        
//    );
    
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
            <div class="input-group col-md-12">
            <span class="input-group-addon" id="sizing-addon1">选择测验</span>',
       '#suffix' => '
                <span class="input-group-addon"><span class="exam_remove_btn btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class=" btn-icon glyphicon glyphicon-th-list"></span></span>
                </div></div>',
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
    
//    $form['survey_exams_nid'] = array('#type' => 'hidden', '#default_value' => $survey->survey_nids);
     $form['survey_exams_nid'] = array(
       '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6" style="display:none;">
            <span class="input-group-addon" id="sizing-addon1">问卷编号</span>',
        '#suffix' => '<span class="input-group-addon">'
                    . '<span class="exam_remove_btn btn-icon glyphicon glyphicon-remove"></span></span>'
                    . '</div>',
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
          
        ); 
       
            $form['submit_export_report'] = array(
                '#type' => 'button',
                '#default_value' => '下载报告',
                '#attributes' => array(
                    'class' => array(
                        'btn ',
                    ),
                    'data-loading-text'=>'准备导出...',
                    'data-toggle' =>'tooltip',
                    'data-placement'=>'bottom',
                    'title'=>'只有已经完成的调查会被导出。'
                ),

                '#suffix' => '',
            ); 
            $form['submit_export_excel_report'] = array(
                '#type' => 'button',
                '#default_value' => '下载调查结果',
                '#attributes' => array(
                    'class' => array(
                        'btn ',
                        'btn-primary'
                    ),
                    'data-loading-text'=>'准备导出...',
                    'data-toggle' =>'tooltip',
                    'data-placement'=>'bottom',
                    'title'=>'下载调查结果，Excel格式。'
                ),

                '#suffix' => '</span></div></div>',
            ); 
    }
    
      if($survey->survey_status == 2 ||
              $survey->survey_status == 3){
        
     }
    
    return $form;
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
    
    $pattern = "/^[1-9]\d*$/";
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
            $review_folder = DEFAULT_WORDPATH . $survey['survey_id'];
            $empty = DEFAULT_WORDPATH . $survey['survey_id']."/empty";
            create_folder_if_not_exist($review_folder);
            create_folder_if_not_exist($empty);
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
//        drupal_set_message(t("生成用户问卷 $counter 份。"));
    } else if('生成报告' === $form_state['values']['op'] ){
        review_survey_report_generate($survey['survey_id']);
    } 
}

function prepare_survey_group_excel_result($survey){
//    dd($survey);
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

function loadTempNode($s_id){
    $query = "select e_id as exam_id from review360_survey_exam where s_id = $s_id group by e_id;";
    $nids = db_query($query)->fetchAll();
    $nodes = array();
    foreach($nids as $nid){
        $nodes[] = node_load($nid->exam_id);
    }
   
    return $nodes;
}

function genrate_user_exam($s_id){
    $survey = get_survey_by_id($s_id);
//    $old_node = node_load($survey->nid);
    $nodes = loadTempNode($s_id);
    $users = get_survey_user_exam_list($s_id);
   
    $function = 'genrate_user_exam_batch';
    $batch = $function($users,$survey,$nodes);
    batch_set($batch);
}

function genrate_user_exam_do_batch($user,$survey,$nodes, &$context){
    foreach($nodes as $tmp_node){
        $exam_name = $survey->survey_name . '_' . $user->su_id;
        
        $node = prepare_node_main($exam_name);
        $node->webform = array();

        $node->webform['components'] = $tmp_node->webform['components'];

        $node->webform['allow_draft'] = 1;
    //    $node->webform['redirect_url'] = 'interviewer/survey/submitted/' . $user->survey_user_key;
    //        $node->path = array('alias' => $user->survey_user_key);
        node_object_prepare($node);
        $node = node_submit($node);
        node_save($node);
        if ($node->nid > 0) {
            insert_survey_user_exam($user->survey_id,$user->survey_user_key, $node->nid,$tmp_node->title);
        }
        $context['results'][] = $node->nid;
    }
}

function insert_survey_user_exam($sid,$user_key,$exam_nid,$exam_name){
    $field_array = array();
    $field_array['s_id'] = $sid;
    $field_array['exam_nid'] = $exam_nid;
    $field_array['user_key'] = $user_key;
    $field_array['nick_name'] = $exam_name;
    $field_array['create_date'] = time();
    db_insert('review360_survey_user_exam')->fields($field_array)->execute();
}

function genrate_user_exam_batch($users,$survey,$nodes){
    
  $operations = array();

  foreach($users as $user){
      $operations[] = array(
        'genrate_user_exam_do_batch',
        array(
          $user,
          $survey,
          $nodes
        ),
      );
  }
    
    $batch = array(
        'operations' => $operations,
        'finished' => 'genrate_user_exam_finish',
        'title' => t('问卷生成'),
        'init_message' => t('生成中....'),
        'progress_message' => t('已经生成 @current 人, 总共 @total 人.'),
        'error_message' => t('生成错误请联系管理员.'),
        'file' => drupal_get_path('module', 'review360_base') . '/inc/admin/review360_survey_management.inc',
    );
    return $batch;
}

function genrate_user_exam_finish($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('总共生成问卷 "%final" 份', array('%final' => count($results))));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(
      t('生成问卷出错 @operation  : @args',
        array(
          '@operation' => $error_operation[0],
          '@args' => print_r($error_operation[0], TRUE),
        )
      )
    );
  }
}

//function update_survey_user_nid($su_id,$nid){
//    db_update('review360_survey_user')
//            ->fields(array(
//                  'nid' => $nid,
//                  'update_date' => time(),
//              ))
//            ->condition('su_id', $su_id)
//            ->execute();
//}

function active_survey_by_id($id,$exam_nids,$survey_key){
     //$nid = create_survey_exam_template($exam_nids,$survey_key);
    relate_survey_exam($id,$exam_nids);
    $rst = db_update('review360_survey')
        ->fields(array(
            //  'nid' =>$nid,
              'survey_status' => 1,
              'update_date' => time(),
          ))
        ->condition('survey_id', $id)
        ->execute();
     if($rst > 0) {
         return true;
     }
     return false;
}

function relate_survey_exam($sid,$exam_nids){
    $ids = explode(',',$exam_nids);
    foreach($ids as $id){
        $field_array = array();
        $field_array['s_id'] = $sid;
        $field_array['e_id'] = $id;
        $field_array['create_date'] = time();
        db_insert('review360_survey_exam')->fields($field_array)->execute();
    }
}

//
//function create_survey_exam_template($exam_nids,$survey_key){
//    $ids = explode(',',$exam_nids);
//    $exam_name = $survey_key.'_exam_template';
////    $items = split('\n',$items_str);
//    $node = prepare_node_main($exam_name);
//    $tmp_node = null;
//    $components = null;
//    $node_component = array();
//    $cid = 1;
//    foreach($ids as $id){
//        $tmp_node = node_load($id);
//        $components = $tmp_node->webform['components'];
//        foreach($components as $component){
//            $node_component[] = prepare_survey_exam_template_component($component,$survey_key,$cid);
//            $cid++;
//        }
//    }
//    $node->webform['components'] = $node_component;
//    node_object_prepare($node);
//    $node = node_submit($node);
//    node_save($node);
//    return $node->nid;
//}

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
        $survey->start_date_str = empty($survey->start_date)?'': prepare_timestamp_to_str($survey->start_date);
        $survey->end_date_str = empty($survey->end_date)?'':prepare_timestamp_to_str($survey->end_date);
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
