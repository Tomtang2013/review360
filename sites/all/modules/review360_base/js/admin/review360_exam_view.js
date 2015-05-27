jQuery(function() {
//    reloadGroupList();
    jQuery('.icon_trash').click(function(){
        jQuery('#delCheckBox').modal({
            keyboard: true
        });
        
        jQuery('#delExamId').val(jQuery(this).attr('href'));
        return false;
    });
    
    jQuery('#delExamBtn').click(function(){
        var btn = jQuery(this).button('loading');
        var link = jQuery('#exam_del_url').val();
        var data = {exam_id:jQuery('#delExamId').val()};
        jQuery.post(link,data,function(req){
            if(req && req.status == 'success'){
                location.reload();
            }
        });
    });
        
    jQuery('#edit-submit-reset').click(function() {
        jQuery('#edit-add-exam').val('');
    });

    jQuery('#edit-submit').click(function() {
        var btn = jQuery(this).button('loading');
        var link = jQuery('#add_new_exam_url').val();
        var data  = {exam_name:jQuery('#edit-add-exam').val()};
        jQuery.post(link,data,function(req){
            if(req && req.status == 'success'){
                reloadExamList();
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

function reloadExamList(){
    var exam_list_url = jQuery('#exam_list_url').val();
    jQuery.post(exam_list_url,{},function(req){
        if(req && req.status == 'success'){
            var tbody = jQuery('#exam_table_tb');
            tbody.empty();
            for(var idx in req.list){
                tbody.append(prepareTR(req.list[idx]));
            }
            
            tbody.find('.icon_trash').click(function(){
                jQuery('#delCheckBox').modal({
                    keyboard: true
                });
                jQuery('#delExamId').val(jQuery(this).attr('href'));
                return false;
            });
        }
    });
}

function prepareTR(obj){
    var tr = jQuery('<tr></tr>');
    var td1 = prepareTD(obj.exam_id);
    var td2 = prepareTD(obj.exam_name);
    var td3 = prepareTD(obj.number);
    var exam_edit_url = jQuery('#exam_edit_url').val()+obj.exam_id;
    var td4 = prepareTD(jQuery('<a class="icon_edit" href="'+exam_edit_url+'"></a>'));
    var td5 = prepareTD(jQuery('<a class="icon_trash"href="'+obj.exam_id+'"></a>'));
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