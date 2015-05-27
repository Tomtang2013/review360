jQuery(function() {
    jQuery('#edit-group-name-btn').click(function(){
        var btn = jQuery(this).button('loading');
        var link = jQuery('#group_edit_name_url').val();
       
        var data  = {group_name:jQuery('#group-name-input').val(),
                     group_id:jQuery('#group_id').val()};
        jQuery.post(link,data,function(req){
            btn.button('reset');
        });
    });
    
    jQuery('#edit-submit-reset').click(function() {
        jQuery('#edit-file-upload').val('');
    });

    jQuery('#edit-submit-export').click(function() {
            var link = jQuery('#group_export_url').val();
            location.href = link;
    });
    
    
});

