<?php

function review360_interviewer_exam($key) {
    $action_name = theme('review360_interviewer_exam_view',array('user_key'=>$key));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    
    return $pageContent;
}
