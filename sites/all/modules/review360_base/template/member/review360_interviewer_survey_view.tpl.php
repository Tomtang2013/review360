<?php
global $base_url;
if (!isset($user_key) || empty($user_key)) {
    drupal_goto($base_url . '/interviewer/onboard');
    return;
}
$user = get_user_infor_by_key($user_key);
if (!isset($user) || empty($user)) {
    drupal_goto($base_url . '/interviewer/onboard');
    return;
}
$survey = get_survey_by_id($user->survey_id);
$node = node_load($user->nid);
?>

<script type="text/javascript">
    jQuery(function () {
        var labels = new Array();
        jQuery('.form-type-radio').each(function () {
            if(labels.length<4){
                labels.push(jQuery(this).find('label').html());
            }
        });
       
        jQuery('.webform-pager-page-slider').hide();
        jQuery('.panel-title').html('请根据您的实际情况作出选择');
        jQuery('.webform-progressbar').hide();
        var radios = new Array();
        var radiosA = new Array();
        var radiosB = new Array();
        var idx = 1;
        jQuery('.form-radio').each(function () {
            jQuery(this).attr('radio-idx', idx++);
            radios.push(jQuery(this));
            if(idx <= 5){
                radiosA.push(jQuery(this));
            } else {
                radiosB.push(jQuery(this));
            }
        });
        
        var table_body = jQuery(jQuery('#table_body').html());
        var exam_body = table_body.find('.exam_body');
        var exam_row = null;
        var label = null;
        for(var i in labels){
            label = labels[i];
            exam_row = jQuery('<tr></tr>');
            exam_row.append(jQuery('<th scope="row"> <label>'+label+'</label></th>'));
            exam_row.append(prepareTD(radiosA[i]));
            exam_row.append(prepareTD(radiosB[i]));
            exam_body.append(exam_row);
        }
        var panel_body = jQuery('.webform-component-fieldset').find('.panel-body');
        panel_body.empty();
        panel_body.append(table_body);
        
        radioInit();
        jQuery('.form-radio').click(function(){
           radioInit();
        });
        
    });


    function radioInit(){
     jQuery('.form-radio').each(function () {
        if (jQuery(this).is(':checked')) {
            var i = Number(jQuery(this).attr('radio-idx'));
            var i_offset = i > 4 ? i - 4 : i + 4;
            jQuery('.form-radio').each(function () {
               if(Number(jQuery(this).attr('radio-idx')) == i_offset) {
                   jQuery(this).css('visibility', 'hidden');
               } 
            });
        }else {
            var i = Number(jQuery(this).attr('radio-idx'));
            var i_offset = i > 4 ? i - 4 : i + 4;
            jQuery('.form-radio').each(function () {
               if(Number(jQuery(this).attr('radio-idx')) == i_offset) {
                   jQuery(this).css('visibility', '');
               } 
            });
        }
    });
    }
    function prepareTD(label){
        var td = jQuery('<td></td>');
        td.append(label);
        return td;
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
                    <div class="progress-bar" style="width: 30%;background-color:#4494D8;">
                        受访者信息完善
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 40%;background-color:#2C7CC0;" >
                        问卷填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 10%;background-color:#ffffff;" >
                        問卷提交
                    </div>
                </div>
            </div>
        </div>
        <div class="row">
            <div class="col-md-10 col-md-offset-1" >
                <h1><?php print $survey->survey_name; ?> <small>欢迎 <?php print $user->u_name; ?> 参加本次调查!</small></h1>
            </div>
        </div>
    </div>

    <div class="row">
        <div class="col-md-10 col-md-offset-1" >
                <?php
                webform_node_view($node, 'full');
                print theme_webform_view($node->content);
                ?> 
        </div>
    </div>
</div>
<div style="display:none">
    <div id="table_body">
        <table class="table table-bordered table-striped responsive-utilities">
            <thead>
                <tr>
                    <th>选择</th>
                    <th style="text-align:center;">最合适</th>
                    <th style="text-align:center;">最不合适</th>
                </tr>
            </thead>
            <tbody class="exam_body">

            </tbody>
        </table>
    </div>
</div>
