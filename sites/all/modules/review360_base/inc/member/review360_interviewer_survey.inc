<?php

defined('DEFAULT_WORDTEMPLATE') or define('DEFAULT_WORDTEMPLATE', 'sites/default/files/generateFiles/DiscTemp.docx');
defined('DEFAULT_WORDPATH') or define('DEFAULT_WORDPATH', 'sites/default/files/generateFiles/');

function review360_interviewer_survey_report_download($key,$nid){
    $user = get_user_by_key($key,$nid);
    $file_name = 'report_'. $user->nick_name .'_'.$user->u_name.'.docx';
    $src_file_name = $user->survey_id . '/report_' .iconv('utf-8','gbk',$user->nick_name) . '_'.iconv('utf-8','gbk',$user->u_name).'.docx';
    $get_url = DEFAULT_WORDPATH . $src_file_name;
    $get_url = drupal_realpath($get_url);
 
    review360_base_export_doc_file($file_name, $get_url);
}

function get_user_by_key($key,$nid){
    $query = "select rsu.survey_id, rsu.u_name, rs.survey_name,rsue.nick_name from review360_survey_user rsu "
            . " inner join review360_survey rs on rsu.survey_id = rs.survey_id "
            . " inner join review360_survey_user_exam as rsue on rsu.survey_user_key = rsue.user_key"
            . " where rsu.survey_user_key = '$key' and  rsue.exam_nid = $nid";
    return $exam = db_query($query)->fetchObject();
}

function review360_interviewer_survey($key,$nid){
    $action_name = theme('review360_interviewer_survey_view',array('user_key'=>$key,'nid'=>$nid));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
//    $node = node_load(650);
//    $node->path = array('alias' => 'wycjdc_ViByJoIgHbHmVlYp');
//    node_object_prepare($node);
//    $node = node_submit($node);
//    node_save($node);
    
    return $pageContent;
}

function review360_interviewer_survey_submit($key,$nid){
    $action_name = theme('review360_interviewer_survey_submitted',array('user_key'=>$key,'nid'=>$nid));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}


function review360_interviewer_survey_generate_report($user_key,$nid){
    update_user_exam_status($nid);
    $query = "select rsue.*,rsu.u_name,rsu.u_company_name,rsu.u_department from review360_survey_user_exam rsue  
        inner join review360_survey_user rsu on 
        rsue.s_id = rsu.survey_id and rsue.user_key = rsu.survey_user_key
        where exam_nid = $nid";
    $exam = db_query($query)->fetchObject();
    $exam->rst = generate_survey_result_by_sv($exam);
    $exam->str = generate_survey_rsult_str($exam);
    $is_generated = generate_report($exam);
   
    if ($is_generated) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}

function review360_interviewer_survey_generate_ajax(){
    $user_key = $_POST['user_key'];
    $nid= $_POST['nid'];

    $has_result = is_generate_result($nid);
    if($has_result->has_result>0){
        echo drupal_json_output(array('status' => 'already generate report.'));
        return;
    }
  
    update_user_exam_status($nid);
    $query = "select rsue.*,rsu.u_name,rsu.u_company_name,rsu.u_department from review360_survey_user_exam rsue  
        inner join review360_survey_user rsu on 
        rsue.s_id = rsu.survey_id and rsue.user_key = rsu.survey_user_key
        where exam_nid = $nid";
    $exam = db_query($query)->fetchObject();
    $exam->rst = generate_survey_result_by_sv($exam);
    $exam->str = generate_survey_rsult_str($exam);
    $is_generated = generate_report($exam);
   
    if ($is_generated) {
        echo drupal_json_output(array('status' => 'success'));
    } else {
        echo drupal_json_output(array('status' => 'failed'));
    }
}




