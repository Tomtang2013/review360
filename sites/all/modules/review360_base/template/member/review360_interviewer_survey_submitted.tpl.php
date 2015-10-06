<?php
global $base_url;

if(!isset($user_key) || empty($user_key)){
    drupal_goto($base_url.'/?q=interviewer/onboard');
    return;
} 
$user = get_user_infor_by_key($user_key);
if(!isset($user) || empty($user)){
    drupal_goto($base_url.'/?q=interviewer/onboard');
    return;
} 

if (!isset($nid) || empty($nid)) {
    drupal_set_message(
            t('请选择评测后开始答题。')
    );
    drupal_goto($base_url . '/?q=interviewer/exam/' . $user_key);

    return;
}

$back_url = $base_url.'/interviewer/exam/'.$user_key;
$generate_url = $base_url."/interviewer/survey/generate";

$has_result = is_generate_result($nid);
$has_result->has_result = 0;
?>

<input id="generate_url" type="hidden" value="<?php print $generate_url; ?>"/>
<input id="user_key" type="hidden" value="<?php print $user_key; ?>"/>
<input id="nid" type="hidden" value="<?php print $nid; ?>"/>
<input id="has_result" type="hidden" value="<?php print $has_result->has_result; ?>"/>
<script type="text/javascript">
    jQuery(function () {
       if(jQuery('#has_result').val()==0){
           send_generate_post();
       }
    });
    
    function send_generate_post(){
        var link = jQuery('#generate_url').val();
        var data = {user_key:jQuery('#user_key').val()
            ,nid:jQuery('#nid').val()};
         jQuery.post(link,data,function(req){
           console.log(req);
        });
    }
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
                <h1> <small>感谢 <?php print $user->u_name; ?> 参加本次调查!</small></h1>
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