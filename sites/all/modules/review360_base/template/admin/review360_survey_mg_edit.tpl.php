<?php
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/lib/bootstrap-datetimepicker.js');
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/lib/locales/bootstrap-datetimepicker.zh-CN.js');
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/admin/review360_survey_edit.js');
global $base_url;
$survey = get_survey_by_id($survey_id);
$survey_edit_submit_url = $base_url . '/?q=surveymanagement/submit/';
$survey_file_export_url = $base_url . '/?q=surveymanagement/export/';
$survey_report_export_url = $base_url . '/?q=surveymanagement/report_export/';
$survey_report_excel_export_url = $base_url . '/?q=surveymanagement/report_excel_export/';

$exams = get_selectable_exam();
?>
<script type="text/javascript">
    jQuery(function () {
        var survey_status = <?php print $survey->survey_status; ?>;
        if (survey_status === null || survey_status === '')
            survey_status = 0;
        if(survey_status === 0){
            jQuery('.exam_remove_btn').click(function () {
                jQuery('#edit-survey-exams-str').val('');
                jQuery('#edit-survey-exams-nid').val('');
            });

            jQuery('.glyphicon-th-list').click(function () {
                jQuery('#examSelectBox').modal({
                    keyboard: true
                });
                return false;
            });
        } if (survey_status === 1 
                || survey_status === 2) {
            jQuery('.form-line').each(function () {
                jQuery(this).find('.form-text').each(function () {
                    jQuery(this).attr('readonly', '');
                });
                jQuery(this).find('.input-group-addon').each(function () {
                    jQuery(this).unbind('click');
                });
            });

            jQuery('.exam_remove_btn').click(function () {
                return false;
            });
            jQuery('.glyphicon-th-list').click(function () {
                return false;
            });
        } else if (survey_status > 2) {
            jQuery('.form-line').each(function () {
                jQuery(this).find('.form-text').each(function () {
                    jQuery(this).attr('readonly', '');
                });
                jQuery(this).find('.btn').each(function () {
                    jQuery(this).hide();
                });
                jQuery(this).find('.input-group-addon').each(function () {
                    jQuery(this).unbind('click');
                });
                jQuery('.exam_remove_btn').click(function () {
                    return false;
                });
                jQuery('.glyphicon-th-list').click(function () {
                    return false;
                });
            });
        }
    });

</script> 
<input id="survey_id" type="hidden" value="<?php print $survey->survey_id; ?>"/>
<input id="survey_edit_submit_url" type="hidden" value="<?php print $survey_edit_submit_url; ?>"/>
<input id="survey_file_export_url" type="hidden" value="<?php print $survey_file_export_url . $survey->survey_id; ?>"/>
<input id="survey_report_export_url" type="hidden" value="<?php print $survey_report_export_url . $survey->survey_id; ?>"/>
<input id="survey_report_excel_export_url" type="hidden" value="<?php print $survey_report_excel_export_url . $survey->survey_id; ?>"/>



<div class="row" style='margin-right:15px;margin-left:15px;'>
    <label>问卷编辑:</label>
    <hr/>
    <?php 
        $form = drupal_get_form('review360_survey_edit_form', $survey);
        print drupal_render($form); 
    ?>
</div>

<!-- Modal -->
<div class="modal fade bs-surveyple-modal-sm" id="examSelectBox"
     tabindex="-1" role="dialog" aria-labelledby="examSelectBox" aria-hidden="true">
    <div class="modal-dialog modal-sm">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">问卷选择</h4>
            </div>
            <div class="modal-body">
                <div class="row">
                    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
                        <thead>
                            <tr>
                                <th>勾选</th>
                                <th>编号</th>
                                <th>问卷名称</th>
                                <th>题目(数量)</th>
                            </tr>
                        </thead>
                        <tbody id="exam_table_tb">
                            <?php foreach ($exams as $exam): ?>
                                <tr>
                                    <td class=""><input class="exam_checkbox"
                                                        data-exam-name="<?php print $exam->exam_name; ?>"
                                                        type="checkbox" name="exam_ids" aria-label="" value="<?php print $exam->nid; ?>"></td>
                                    <td class=""><?php print $exam->exam_id; ?></td>
                                    <td class=""><?php print $exam->exam_name; ?></td>
                                    <td class=""><?php print $exam->number; ?></td>
                                </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                </div>
            </div>
            <div class="modal-footer">
                <input id="delSurvyId" type="hidden" value=""/>
                <button type="button" class="btn btn-primary" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-danger" 
                        data-loading-text="问卷选择中..."
                        id="selectExamsBtn">确定</button>
            </div>
        </div>
    </div>
</div>
