<?php 
    global $base_url;
    $sql = variable_get('serach_query_str','');
    $users_infor = array();

    if($sql !=''){
       $users_infor = search_infor_by_condition($sql);
       variable_set('serach_query_str','');
    }
   
    $rst_url = $base_url.'/?q=candidate/filter/surveyrst';

?>
<script type="text/javascript">
    jQuery(function () {
        jQuery('.school-list-btn').click(function(){
            jQuery('#schoolBox').modal({
                    keyboard: true
            });
            return false;
        });
        
        jQuery('.school-remove-btn').click(function(){
            jQuery('#edit-infor-university').val('');
        });
        jQuery('.btn-icon').click(function(){
            var url = '<?php print $rst_url;?>';
            var sid = jQuery(this).attr('data-sid');
            var uk = jQuery(this).attr('data-uk');
            jQuery.post(url,{sid:sid,uk:uk},function(rsp){
                var value = rsp.rst;
                var tb = jQuery('#survey_rst_table_tb');
                tb.empty();
                var nick_name = null;
                var rst = null;
                for(var nid in value){
                    nick_name = value[nid].nick_name;
                    rst = value[nid].rst;
                    appendTRNickName(tb,nick_name);
                    appendTR(tb,rst)                    
                }
             
                
                jQuery('#rstViewBox').modal({
                    keyboard: true
                });
            });
        });
     });   
     function appendTRNickName(tb,name){
        var tr = jQuery('<tr></tr>');
        tr.append(jQuery('<td colspan="5">'+name+'</td>'));
        return  tb.append(tr);
     }
     function appendTR(tb,value){
           tb.append(prepare_tr('D',value[0].d,
                            value[1].d,
                            value[2].d,
                            value[3].d));
            tb.append(prepare_tr('I',value[0].i,
                            value[1].i,
                            value[2].i,
                            value[3].i));
            tb.append(prepare_tr('S',value[0].s,
                            value[1].s,
                            value[2].s,
                            value[3].s ));
            tb.append(prepare_tr('C', value[0].c,
                            value[1].c,
                            value[2].c,
                            value[3].c ));
     }
     
     function prepare_tr(type,v1,v2,v3,v4){
        var tr = jQuery('<tr></tr>');
        tr.append(jQuery('<td>'+type+'</td>'));
        tr.append(jQuery('<td>'+v1+'</td>'));
        tr.append(jQuery('<td>'+v2+'</td>'));
        tr.append(jQuery('<td>'+v3+'</td>'));
        tr.append(jQuery('<td>'+v4+'</td>'));
        return tr;
     }
</script> 
<label>用户筛选</label>
<hr/>
<div class="row">
    <div class="col-lg-11">
         <?php 
        $form = drupal_get_form('review_candidate_filter_form');
        print drupal_render($form) ;?> 
    </div>
</div>


<hr/>

<label>用户列表</label>

<div class="row">
    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
        <thead>
            <tr>
                <th>姓名</th>
                <th>调查名称</th>
                <th>公司</th>
                <th>测验工具</th>
                <th>联系电话</th>
                <th>邮箱</th>
                <th>测试结果</th>
            </tr>
        </thead>
        <tbody id="survey_table_tb">
            <?php foreach($users_infor as $user_infor ):?>
            <tr>
                <td class=""><?php print $user_infor->u_name;?></td>
                <td class=""><?php print $user_infor->survey_name;?></td>
                <td class=""><?php print $user_infor->u_company_name;?></td>
                <td class=""><?php print $user_infor->survey_nid_name;?></td>
                <td class=""><?php print $user_infor->u_p_number;?></td>
                <td class=""><?php print $user_infor->u_email?></td>
                <td><span class=" btn-icon glyphicon glyphicon-th-list"
                          data-uk="<?php print $user_infor->survey_user_key?>"
                          data-sid="<?php print $user_infor->survey_id?>"></span></td>
            </tr>
            <?php  endforeach;?>
        </tbody>
    </table>
</div>

<!-- Modal -->
<div class="modal fade bs-surveyple-modal-sm" id="rstViewBox"
     tabindex="-1" role="dialog" aria-labelledby="rstViewBox" aria-hidden="true">
    <div class="modal-dialog modal-sm">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">测试结果</h4>
            </div>
            <div class="modal-body">
                <div  class="alert " >
                    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
                        <thead>
                            <tr>
                                <th>象限</th>
                                <th>工作中的我</th>
                                <th>天生的我</th>
                                <th>别人眼中的我</th>
                                <th>压力下的我</th>
                            </tr>
                        </thead>
                        <tbody id="survey_rst_table_tb">
                           
                        </tbody>
                    </table>
                </div>
            </div>
            <div class="modal-footer">
                <input id="delSurvyId" type="hidden" value=""/>
                <button type="button" class="btn btn-primary" data-dismiss="modal">关闭</button>
            </div>
        </div>
    </div>
</div>

