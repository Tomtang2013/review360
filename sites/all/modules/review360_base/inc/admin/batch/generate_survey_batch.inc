<?php

defined('DEFAULT_WORDTEMPLATE') or define('DEFAULT_WORDTEMPLATE', 'sites/default/files/generateFiles/DiscTemp.docx');
defined('DEFAULT_WORDPATH') or define('DEFAULT_WORDPATH', 'sites/default/files/generateFiles/');



function generate_survey_user_report_do_batch($exam,&$context){
    require_once drupal_get_path('module', 'review360_base') . '/lib/ReportGenerator/ReportCreator.php';

    if($exam->is_generate_result == 0){
        generate_survey_result_by_sv($exam);
    }
    
    $review_folder = DEFAULT_WORDPATH . $exam->s_id;
    $zip_is_exist = file_exists($review_folder);
    if(!$zip_is_exist){
        create_review_results_folder($review_folder);
    }
    $report =new ReportCreator(DEFAULT_WORDTEMPLATE,$review_folder);
    if($exam->is_generate_report == 0){
        $report->generate_report($exam);
    }
       

    $zip_name = $exam->s_id.'.zip';
    zip_folder($zip_name,$review_folder,$exam->s_id);
    mark_as_generated_report($exam->se_id);
    $context['results'][] = 1;
    $context['results']['survey_id'] = $exam->s_id;
}

function create_review_results_folder($dirname) {
    dirname($dirname);
    mkdir($dirname, 0777, true);
    return $dirname;
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

function zip_folder($zip_name, $fold_path,$review_name) {
    $z = new ZipArchive();
    $z->open(DEFAULT_WORDPATH . $zip_name, ZIPARCHIVE::CREATE);
    folderToZip($fold_path, $z,$review_name);
    $z->close();
}

function folderToZip($folder, &$zipFile, $subfolder = null) {
    if ($zipFile == null) {
        // no resource given, exit
        return false;
    }

    $end_split = str_split($folder);
    $sub_end_split = str_split($subfolder);
    // we check if $folder has a slash at its end, if not, we append one
    $folder .= end($end_split) == "/" ? "" : "/";
    $subfolder .= end($sub_end_split) == "/" ? "" : "/";
    // we start by going through all files in $folder
    $handle = opendir($folder);
    while ($f = readdir($handle)) {
        if ($f != "." && $f != "..") {
            if (is_file($folder . $f)) {
                // if we find a file, store it
                // if we have a subfolder, store it there
                if ($subfolder != null)
                    $zipFile->addFile($folder . $f, $subfolder . $f);
                else
                    $zipFile->addFile($folder . $f);
            } elseif (is_dir($folder . $f)) {
                // if we find a folder, create a folder in the zip
                $zipFile->addEmptyDir($f);
                // and call the function again
                folderToZip($folder . $f, $zipFile, $f);
            }
        }
    }
}