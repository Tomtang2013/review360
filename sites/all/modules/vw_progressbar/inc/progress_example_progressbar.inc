<?php

function progress_example_progressbar_form($form, &$form_state) {
  $form_state['time'] = REQUEST_TIME;

  // We make a DIV which the progress bar can occupy. You can see this in use
  // in ajax_example_progressbar_callback().
  $form['#attributes']['enctype'] = 'multipart/form-data';
  
  $form['status'] = array(
    '#markup' => '<div id="progress-status"></div>',
  );

  $form['file_upload'] = array(
      '#type' => 'managed_file',
      '#progress_indicator' => 'bar',
//      '#value' => t('ADD NEW PROJECT INFO'),
//      '#theme' => 'resup_upload',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#ajax' => array(
      // Here we set up our AJAX callback handler.
      'callback' => 'vw_example_progressbar_callback',
      // Tell FormAPI about our progress bar.
      'progress' => array(
        'type' => 'bar',
        'message' => t('Execute..'),
        // Have the progress bar access this URL path.
        'url' => url('vw/progress_example/progressbar/progress/' . $form_state['time']),
        // The time interval for the progress bar to check for updates.
        'interval' => 1000,
      ),
    ),
  );

  return $form;
}

//function vw_progressbar_field_widget_form_alter(&$element, &$form_state, $context) {
//    $instance = $context['instance'];
//  if (!empty($instance['settings']['resup']) && file_resup_field_widget_support($instance['widget']['type']) && user_access('upload via file_resup') && file_upload_max_size() >= file_resup_chunksize()) {
//    $keys = element_children($element);
//    $delta = end($keys);
//
//    $cardinality = $context['field']['cardinality'];
//    $element[$delta]['#file_resup_max_files'] = $cardinality != FIELD_CARDINALITY_UNLIMITED ? $cardinality - $delta : -1;
//
//    $upload_validators = $element[$delta]['#upload_validators'];
//    $upload_validators['file_validate_size'] = array(file_resup_max_filesize($instance));
//    $element[$delta]['#file_resup_upload_validators'] = $upload_validators;
//
//    $element[$delta]['#process'][] = 'file_resup_field_widget_process';
//    $element[$delta]['#file_value_callbacks'][] = 'file_resup_field_widget_value';
//  }
//}

function vw_example_progressbar_callback($form, &$form_state) {
  $variable_name = 'example_progressbar_' . $form_state['time'];
  $commands = array();
  variable_set($variable_name, 10);
  sleep(2);
  variable_set($variable_name, 20);
  sleep(2);
  variable_set($variable_name, 30);
  sleep(2);
  variable_set($variable_name, 40);
  sleep(2);
  variable_set($variable_name, 50);
  sleep(2);
  variable_set($variable_name, 60);
  sleep(2);
  variable_set($variable_name, 70);
  sleep(2);
  variable_del($variable_name);

  $commands[] = ajax_command_html('#progress-status', t('Executed.'));

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}


function progress_example_progressbar_progress($time){
    
  $progress = array(
    'message' => t('Starting execute...'),
    'percentage' => -1,
  );

  $completed_percentage = variable_get('example_progressbar_' . $time, 0);

  if ($completed_percentage) {
    $progress['message'] = t('Executing...');
    $progress['percentage'] = $completed_percentage;
  }

  drupal_json_output($progress);
}


function example_admin_form(){  

  $form = array();  
//dd(drupal_realpath('public://'));
  $form['image'] = array(
      '#type' => 'managed_file',
      '#name' => 'image',
      '#title' => t('upload your image here!'),
      '#default_value' => variable_get('image', ''),
      '#description' => t("Here you can upload an image"),
      '#progress_indicator' => 'bar',
      '#upload_location' => 'public://my_img/'
  );

  // Add your submit function to the #submit array
  $form['#submit'][] = 'example_admin_form_submit';

  return $form;
}

function example_admin_form_submit($form, &$form_state){
  // Load the file
  $file = file_load($form_state['values']['image']);
  // Change status to permanent.
  $file->status = FILE_STATUS_PERMANENT;
  // Save.
  file_save($file);
}