<?php
function review360_interviewer_survey($key){
    $action_name = theme('review360_interviewer_survey_view',array('user_key'=>$key));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
//    $node = node_load(650);
//    $node->path = array('alias' => 'wycjdc_ViByJoIgHbHmVlYp');
//    node_object_prepare($node);
//    $node = node_submit($node);
//    node_save($node);
    
    return $pageContent;
}

function review360_interviewer_survey_submit($key){
    $action_name = theme('review360_interviewer_survey_submitted',array('user_key'=>$key));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}