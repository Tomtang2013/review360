jQuery(function () {
    jQuery('#edit-exam-name-btn').click(function(){
        var btn = jQuery(this).button('loading');
        var link = jQuery('#exam_edit_name_url').val();
       
        var data  = {exam_name:jQuery('#exam-name-input').val(),
                     spend_time:jQuery('#exam-spend-time-input').val(),
                     exam_id:jQuery('#exam_id').val()};
        jQuery.post(link,data,function(req){
//            btn.button('reset');
            location.reload();
        });
    });
    
    jQuery('#edit-submit-reset').click(function () {
        jQuery('#edit-file-upload').val('');
    });

    jQuery('#edit-submit-export').click(function () {
        if(!jQuery(this).hasClass('btn-warning')){
            var link = jQuery('#exam_export_url').val();
            location.href = link;
        } else {
            return false;
        }
    });
    
    
});