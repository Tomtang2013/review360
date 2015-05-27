jQuery(function() {
//    reloadGroupList();
    
    jQuery('.icon_trash').click(function(){
        jQuery('#delCheckBox').modal({
            keyboard: true
        });
        jQuery('#delGroupId').val(jQuery(this).attr('href'));
        return false;
    });
    
    jQuery('#delGroupBtn').click(function(){
        var btn = jQuery(this).button('loading');
        var link = jQuery('#group_del_url').val();
        var data = {group_id:jQuery('#delGroupId').val()};
        jQuery.post(link,data,function(req){
            if(req && req.status == 'success'){
                location.reload();
            }
        });
    });
        
    jQuery('#edit-submit-reset').click(function() {
        jQuery('#edit-add-user-group').val('');
    });

    jQuery('#edit-submit').click(function() {
        var btn = jQuery(this).button('loading');
        var link = jQuery('#add_new_group_url').val();
        var data  = {group_name:jQuery('#edit-add-user-group').val()};
        jQuery.post(link,data,function(req){
            if(req && req.status == 'success'){
                reloadGroupList();
            }
            btn.button('reset');
        });
    });
});

function verify_total_number(value) {
    var reg1 = /^\d+$/;
    if (value.match(reg1) == null)
        return false;
    else
        return true;
}

function reloadGroupList(){
    var group_list_url = jQuery('#group_list_url').val();
    jQuery.post(group_list_url,{},function(req){
        if(req && req.status == 'success'){
            var tbody = jQuery('#group_table_tb');
            tbody.empty();
            for(var idx in req.list){
                tbody.append(prepareTR(req.list[idx]));
            }
            tbody.find('.icon_trash').click(function(){
                jQuery('#delCheckBox').modal({
                    keyboard: true
                });
                jQuery('#delGroupId').val(jQuery(this).attr('href'));
                return false;
            });
        }
    });
}

function prepareTR(obj){
    var tr = jQuery('<tr></tr>');
    var td1 = prepareTD(obj.group_id);
    var td2 = prepareTD(obj.group_name);
    var td3 = prepareTD(obj.number);
    var group_edit_url = jQuery('#group_edit_url').val()+obj.group_id;
    var td4 = prepareTD(jQuery('<a class="icon_edit" href="'+group_edit_url+'"></a>'));
    var td5 = prepareTD(jQuery('<a class="icon_trash"href="'+obj.group_id+'"></a>'));
    tr.append(td1);
    tr.append(td2);
    tr.append(td3);
    tr.append(td4);
    tr.append(td5);
    return tr;
}


function prepareTD(element){
    var td = jQuery('<td></td>');
    td.append(element);
    return td;
}
