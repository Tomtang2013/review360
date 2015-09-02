<?php

defined('DEFAULT_WORDTEMPLATE') or define('DEFAULT_WORDTEMPLATE', 'sites/default/files/generateFiles/DiscTemp.docx');
defined('DEFAULT_WORDPATH') or define('DEFAULT_WORDPATH', 'sites/default/files/generateFiles/');



function generate_survey_user_report_do_batch($exam,&$context){
    if($exam->is_generate_result == 0){
        generate_survey_result_by_sv($exam);
    }
    
    $review_folder = DEFAULT_WORDPATH . $exam->s_id;
    create_folder_if_not_exist($review_folder);
    
    $report =new ReportCreator(DEFAULT_WORDTEMPLATE,$review_folder);
    if($exam->is_generate_report == 0){
        $report->generate_report($exam);
    }
//    mark_as_generated_report($exam->se_id);
    $context['results'][] = 1;
    $context['results']['survey_id'] = $exam->s_id;
}



function generate_survey_user_report_finish($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('总共生成报告 "%final" 份', array('%final' => (count($results)-1))));
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
  $sid = $results['survey_id'];
  mark_as_avaible_to_download($sid);
}

function mark_as_avaible_to_download($sid){
    db_update('review360_survey')
    ->fields(array(
          'is_generate_report' => 1,
          'update_date' => time(),
      ))
    ->condition('survey_id', $sid)
    ->execute();
}

function mark_as_generated_report($se_id){
    db_update('review360_survey_user_exam')
    ->fields(array(
          'is_generate_report' => 1,
          'update_date' => time(),
      ))
    ->condition('se_id', $se_id)
    ->execute();
}
