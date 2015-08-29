<?php
global $base_url;
if(!isset($user_key) || empty($user_key)){
    drupal_goto($base_url.'/interviewer/onboard');
    return;
} 
$user = get_user_infor_by_key($user_key);
if(!isset($user) || empty($user)){
    drupal_goto($base_url.'/interviewer/onboard');
    return;
} 
if (!isset($nid) || empty($nid)) {
    drupal_set_message(
      t('请选择评测后开始答题。' )
    );
    drupal_goto($base_url . '/interviewer/exam/'.$user_key);
    return;
}

$survey = get_survey_by_id($user->survey_id);

?>


</script> 
<div class="survey-user-exam-main">
    <div class="page-header">
        <div class="row">
            <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#4494D8;">
                       受访者信息完善
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#2C7CC0;">
                       评测选择
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#125FA1;" >
                       评测填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#002521;" >
                       评测提交
                    </div>
                </div>
            </div>
        </div>
        <div class="row">
            <div class="col-md-10 col-md-offset-1" >
                <h1><?php print $survey->survey_name; ?> <small>感谢 <?php print $user->u_name; ?> 参加本次调查!</small></h1>
            </div>
        </div>
    </div>
    <div class="row">
        <div class="col-md-10 col-md-offset-1" >
            <div class="alert alert-success" role="alert">
                <strong>您成功提交本调查!</strong>，请关闭本页面，谢谢。
            </div>
        </div>
    </div>
</div>