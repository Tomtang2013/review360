jQuery(function() {
//    reloadGroupList();
    jQuery('.icon_trash').click(function(){
        if('tooltip' === jQuery(this).attr('data-toggle')){
            return false;
        }
        jQuery('#delCheckBox').modal({
            keyboard: true
        });
        
        jQuery('#delSurvyId').val(jQuery(this).attr('href'));
        return false;
    });
    
    jQuery('#delSurvyBtn').click(function(){
        var btn = jQuery(this).button('loading');
        var link = jQuery('#survey_del_url').val();
        var data = {survey_id:jQuery('#delSurvyId').val()};
        jQuery.post(link,data,function(req){
            console.log(req);
            if(req && req.status == 'success'){
                location.reload();
            }
        });
    });
        
    jQuery('#edit-submit-reset').click(function() {
        jQuery('#edit-add-survey').val('');
    });

    jQuery('#edit-submit').click(function() {
        var btn = jQuery(this).button('loading');
        var link = jQuery('#add_new_survey_url').val();
        var data  = {survey_name:jQuery('#edit-add-survey').val()};
        jQuery.post(link,data,function(req){
            if(req && req.status == 'success'){
                reloadSurvyList();
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

function reloadSurvyList(){
    var survey_list_url = jQuery('#survey_list_url').val();
    console.log(survey_list_url);
    jQuery.post(survey_list_url,{},function(req){
        if(req && req.status == 'success'){
            var tbody = jQuery('#survey_table_tb');
            tbody.empty();
            for(var idx in req.list){
                tbody.append(prepareTR(req.list[idx]));
            }
            
            tbody.find('.icon_trash').click(function(){
                jQuery('#delCheckBox').modal({
                    keyboard: true
                });
                jQuery('#delSurvyId').val(jQuery(this).attr('href'));
                return false;
            });
        }
    });
}

function prepareTR(obj){
    var tr = jQuery('<tr></tr>');
    var td1 = prepareTD(obj.survey_id);
    var td2 = prepareTD(obj.survey_name);
    var td3 = prepareTD(obj.survey_user_num);
    var td4 = prepareTD(obj.survey_status_str);
    var td5 = prepareTD(obj.start_date);
    var td6 = prepareTD(obj.end_date);
    var survey_edit_url = jQuery('#survey_edit_url').val()+obj.survey_id;
    var td7 = prepareTD(jQuery('<a class="icon_edit" href="'+survey_edit_url+'"></a>'));
    var td8 = prepareTD(jQuery('<a class="icon_trash"href="'+obj.survey_id+'"></a>'));
    tr.append(td1);
    tr.append(td2);
    tr.append(td3);
    tr.append(td4);
    tr.append(td5);
    tr.append(td6);
    tr.append(td7);
    tr.append(td8);
    return tr;
}


function prepareTD(element){
    var td = jQuery('<td></td>');
    td.append(element);
    return td;
}