<?php
global $base_url;
if (!isset($user_key) || empty($user_key)) {
    drupal_set_message(
            t('您的调查编码有误，请重新登录。')
    );
    drupal_goto($base_url . '/?q=interviewer/onboard');
    return;
}
$user = get_user_infor_by_key($user_key);
if (!isset($user) || empty($user)) {
    drupal_set_message(
            t('您的调查编码有误，请重新登录。')
    );
    drupal_goto($base_url . '/?q=interviewer/onboard');
    return;
}

if (!isset($nid) || empty($nid)) {
    drupal_set_message(
            t('请选择评测后开始答题。')
    );
    drupal_goto($base_url . '/?q=interviewer/exam/' . $user_key);

    return;
}
$survey = get_survey_by_id($user->survey_id);
$node = node_load($nid);
  
$exam = get_user_exam_by_nid($nid);
?>

<script type="text/javascript">
    jQuery(function () {
        var labels = new Array();
        jQuery('.form-type-radio').each(function () {
            if (labels.length < 4) {
                labels.push(jQuery(this).find('label').html());
            }
        });

        jQuery('.webform-pager-page-slider').hide();
        jQuery('.panel-title').html('选出一个最能贴切地描述你的短句，再选出一个最不适合来描述你的<strong>短句</strong>');
        jQuery('.webform-progressbar').hide();
        var radios = new Array();
        var radiosA = new Array();
        var radiosB = new Array();
        var idx = 1;
        jQuery('.form-radio').each(function () {
            jQuery(this).attr('radio-idx', idx++);
            radios.push(jQuery(this));
            if (idx <= 5) {
                radiosA.push(jQuery(this));
            } else {
                radiosB.push(jQuery(this));
            }
        });

        var table_body = jQuery(jQuery('#table_body').html());
        var exam_body = table_body.find('.exam_body');
        var exam_row = null;
        var label = null;
        var rows = [];
        for (var i in labels) {
            label = labels[i];
            exam_row = jQuery('<tr></tr>');
            exam_row.append(jQuery('<th scope="row"> <label>' + label + '</label></th>'));
            exam_row.append(prepareTD(radiosA[i]));
            exam_row.append(prepareTD(radiosB[i]));
            rows.push(exam_row);
        }

        rows.sort(function () {
            return Math.random() > 0.5 ? -1 : 1;
        });

        for (var i in rows) {
            exam_body.append(rows[i]);
        }

        var panel_body = jQuery('.webform-component-fieldset').find('.panel-body');
        panel_body.empty();
        panel_body.append(table_body);

        radioInit();
        appendPage();
        click_td_select_radio();
        jQuery('#exam_box').show();
        jQuery('.form-radio').click(function () {
            radioInit();
        });

    });


    function radioInit() {
        jQuery('.form-radio').each(function () {
            if (jQuery(this).is(':checked')) {
                var i = Number(jQuery(this).attr('radio-idx'));
                var i_offset = i > 4 ? i - 4 : i + 4;
                jQuery('.form-radio').each(function () {
                    if (Number(jQuery(this).attr('radio-idx')) == i_offset) {
                        jQuery(this).css('visibility', 'hidden');
                    }
                });
            } else {
                var i = Number(jQuery(this).attr('radio-idx'));
                var i_offset = i > 4 ? i - 4 : i + 4;
                jQuery('.form-radio').each(function () {
                    if (Number(jQuery(this).attr('radio-idx')) == i_offset) {
                        jQuery(this).css('visibility', '');
                    }
                });
            }
        });
    }
    
    function appendPage(){
        var div = jQuery('.webform-client-form > div');
        var page = jQuery("input[name='details[page_num]']").val();
        var total =  jQuery("input[name='details[page_count]']").val();
        var h = jQuery("<h4 style='display:inline-block;'> 当前第"+page +"题 / 总共" + total+"题</h4>");
        div.append(h);
    }
        
    function prepareTD(label) {
        var td = jQuery('<td></td>');
        td.append(label);
        return td;
    }
    
    function click_td_select_radio(){
        jQuery('.exam_body').find('td').each(function(){
            var radio = jQuery(this).find('radio');
            if(radio){
                jQuery(this).click(function(){
                    radio.trigger('click');
                });
            }
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
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#4494D8;" >
                        评测填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#ffffff;" >
                        评测提交
                    </div>
                </div>
            </div>
        </div>
        <div class="row">
            <div class="col-md-10 col-md-offset-1" >
                <h3> <small>欢迎 <strong><?php print $user->u_name; ?></strong> 参加本次调查!</small></h3>
            </div>
        </div>
    </div>

    <div class="row" style="display:none;" id="exam_box">
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
