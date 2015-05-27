<?php

function progress_example_uploadtemp() {
  
    $upload_dir = get_upload_temp_path();

    //    $allowed_ext = array('jpg','jpeg','png','gif','doc','docx','flv','mp3','mp4'.'xls','xlsx','mov','ppt','pptx','wma'.'swf');
    $allowed_ext = array('jpg', 'jpeg', 'png', 'gif', 'doc', 'docx', 'xls', 'xlsx', 'zip', '7z');


    if (strtolower($_SERVER['REQUEST_METHOD']) != 'post') {
        exit_status('Error! Wrong HTTP method!', 1);
    }

    if (array_key_exists('pic', $_FILES) && $_FILES['pic']['error'] == 0) {
        $pic = $_FILES['pic'];
        if (!in_array(get_extension($pic['name']), $allowed_ext)) {
            exit_status('Only ' . implode(',', $allowed_ext) . ' files are allowed!', 1);
        }

        // Move the uploaded file from the temporary
        // directory to the uploads folder:

        if (!file_exists($upload_dir))
            mkdir($upload_dir, 0777);
        if (move_uploaded_file($pic['tmp_name'], $upload_dir . $pic['name'])) {
            exit_status('File was uploaded successfuly!', 0);
        }
    }

    exit_status('Something went wrong with your upload!', 1);
}

function get_upload_temp_path() {
    global $user;
    $uid = $user->uid;
    return file_stream_wrapper_get_instance_by_uri('public://')->realpath() . '\\uploads' . "\\" . $user->uid . "\\";
}

function exit_status($str, $error) {
    echo json_encode(array('status' => $str, 'error' => $error));
    exit;
}
function get_extension($file_name){
    $ext = explode('.', $file_name);
    $ext = array_pop($ext);
    return strtolower($ext);
}