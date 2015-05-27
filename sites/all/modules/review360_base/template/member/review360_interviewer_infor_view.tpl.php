<?php
global $base_url;
$user = get_user_infor_by_key($user_key);
?>
<div class="page-header">
    <div class="row">
        <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 30%;background-color:#4494D8;">
                       受访者信息完善
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 40%;background-color:#ffffff;" >
                       问卷填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 10%;background-color:#ffffff;" >
                       問卷提交
                    </div>
                    
                </div>
        </div>
    </div>
</div>
<div class="row">
    <div class="col-md-10 col-md-offset-1" >
        <?php print drupal_render(drupal_get_form('review_interviewer_infor_form', $user)); ?> 
    </div>
</div>