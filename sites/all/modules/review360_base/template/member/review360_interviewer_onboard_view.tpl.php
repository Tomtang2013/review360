<?php 
    global $base_url;
?>
<div class="row">
     <div class="page-header">
        <div class="row">
            <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#ffffff;">
                       受访者信息完善
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#ffffff;">
                       评测选择
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#ffffff;" >
                       评测填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#ffffff;" >
                       评测提交
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-6 col-md-offset-3" >
        <?php 
        $form = drupal_get_form('review_interviewer_onboard_form');
        print drupal_render($form) ;?> 
    </div>
</div>