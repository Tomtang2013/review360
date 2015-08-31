<?php
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/lib/bootstrap-datetimepicker.js');
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/lib/locales/bootstrap-datetimepicker.zh-CN.js');

global $base_url;
$user = get_user_infor_by_key($user_key);
?>

<script type="text/javascript">
    jQuery(function () {
        jQuery('.form_date').datetimepicker({
            language: 'zh-CN',
            weekStart: 1,
            todayBtn: 1,
            autoclose: 1,
            todayHighlight: 1,
            startView: 2,
            minView: 2,
            forceParse: 0,
            format: 'yyyy-mm-dd'
        });
    
        jQuery('.school-list-btn').click(function(){
            jQuery('#schoolBox').modal({
                    keyboard: true
            });
            return false;
        });
        
        jQuery('.school-remove-btn').click(function(){
            jQuery('#edit-infor-university').val('');
        });
    });
</script> 

<div class="page-header">
    <div class="row">
        <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#4494D8;">
                       填写个人信息
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#ffffff;">
                       需完成测评列表
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
<div class="row">
    <div class="col-md-10 col-md-offset-1" >
        <?php 
        $form = drupal_get_form('review_interviewer_infor_form', $user);
        print drupal_render($form); ?> 
    </div>
</div>

<!-- Modal -->
<div class="modal fade bs-surveyple-modal-lg" id="schoolBox"
     tabindex="-1" role="dialog" aria-labelledby="schoolBox" aria-hidden="true">
    <div class="modal-dialog modal-lg">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">高校选择</h4>
            </div>
            <div class="modal-body">
                <?php print theme('review360_interviewer_school');?>
            </div>
        </div>
    </div>
</div>
