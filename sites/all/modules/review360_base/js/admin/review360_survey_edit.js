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
    

    jQuery('#edit-submit-export-report').click(function () {
        var link = jQuery('#survey_report_export_url').val();
        location.href = link;
    });
    jQuery('#edit-submit-export').click(function () {
        var link = jQuery('#survey_file_export_url').val();
        location.href = link;
    });

    jQuery('#edit-submit-reset').click(function () {
        location.reload();
    });

    jQuery('#selectExamsBtn').click(function () {
        var exam_ids = new Array();
        var exam_str = new Array();
        jQuery(".exam_checkbox").each(function () {
            if (jQuery(this).prop('checked') === true) {
                exam_ids.push(jQuery(this).val());
                exam_str.push(jQuery(this).attr('data-exam-name'));
            }
        });
        jQuery('#edit-survey-exams-str').val(prepare_array_to_str(exam_str));
        jQuery('#edit-survey-exams-nid').val(prepare_array_to_str(exam_ids));
        jQuery('#examSelectBox').modal('hide');
        return false;
    });
});

function prepare_array_to_str(array){
    var str = '';
    for(var i in array ){
        str +=array[i];
        str +=',';
    }
    return str.substring(0,str.length-1);
}
