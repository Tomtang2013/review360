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

$back_url = $base_url.'/interviewer/exam/'.$user_key;
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
                    <div class="progress-bar" style="width: 20%;background-color:#69B4F4;">
                       填写个人信息
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#69B4F4;">
                       需完成测评列表
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#69B4F4;" >
                       评测填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#4494D8;" >
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
                <strong>您成功提交本调查!</strong>，请点击返回按钮，返回测评选择页面继续测评，谢谢。
                <a class="btn btn-primary " style="color:#ffffff;"
                        id="edit-exam-name-btn" 
                        href="<?php print $back_url;?>"
                             type="submit">返回</a>
            </div>
        </div>
    </div>
</div>