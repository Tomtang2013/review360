<?php
drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_user_group.js');
//drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_management.js');
global $base_url;
$add_new_group_url = $base_url .'/?q=usermanagement/add';
$group_list_url = $base_url .'/?q=usermanagement/grouplist';

$groups = get_user_group_list();

$user_upload_page = $base_url.'/?q=review360_user_upload/';
$user_group_edit_url = $base_url .'?q=/usermanagement/group/edit/';
$user_group_del_url = $base_url .'/?q=usermanagement/group/del/';
//    
?>

<input id="add_new_group_url" type="hidden" value="<?php print $add_new_group_url;?>"/>
<input id="group_list_url" type="hidden" value="<?php print $group_list_url;?>"/>
<input id="group_del_url" type="hidden" value="<?php print $user_group_del_url;?>"/>
<input id="group_edit_url" type="hidden" value="<?php print $user_group_edit_url;?>"/>


<label>用户分组</label>
<hr/>
<div class="row">
    <div class="col-lg-8">
        <div>
            <div class="input-group"><div class="form-type-textfield form-item-add-user-group form-item form-group">
                <input class="form-control form-text" type="text"
                       id="edit-add-user-group" name="add_user_group" 
                       placeholder="请输入分组名称"
                       value="" size="60" maxlength="128">
            </div>
            <span class="input-group-btn">
                <button class="btn btn-success btn btn-default form-submit" id="edit-submit"
                        data-loading-text="分组添加中..."
                        name="op" value="增加用户分组" type="submit">增加用户分组</button>
                <button class="btn btn-default form-submit" id="edit-submit-reset" 
                        name="op" value="清空" type="button">清空</button>
            </span>
            </div>
        </div>
    </div>
</div>
<hr/>
<label>分组列表</label>

<div class="row">
    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
        <thead>
            <tr>
                <th>#</th>
                <th>分组名称</th>
                <th>人员(数量)</th>
                <th>编辑</th>
                <th>删除</th>
            </tr>
        </thead>
        <tbody id="group_table_tb">
            <?php foreach($groups as $group ):?>
            <tr>
                <td class=""><?php print $group->group_id;?></td>
                <td class=""><?php print $group->group_name;?></td>
                <td class=""><?php print $group->number;?></td>
                <td class=""><a class="icon_edit" href="<?php print $user_group_edit_url.$group->group_id?>"></a></td>
                <td class=""><a class="icon_trash"  type="button"
                                href="<?php print $group->group_id?>" ></a></td>
            </tr>
            <?php  endforeach;?>
        </tbody>
    </table>
</div>
<!-- Modal -->
<div class="modal fade bs-example-modal-sm" id="delCheckBox"
     tabindex="-1" role="dialog" aria-labelledby="delCheckBox" aria-hidden="true">
    <div class="modal-dialog modal-sm">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">确认删除</h4>
            </div>
            <div class="modal-body">
               <div  class="alert alert-danger" >删除用户组会导致该组用户也被删除！您确定要删除该用户组么？</div>
            </div>
            <div class="modal-footer">
                <input id="delGroupId" type="hidden" value=""/>
                <button type="button" class="btn btn-primary" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-danger" 
                         data-loading-text="删除分组中..."
                        id="delGroupBtn">删除</button>
            </div>
        </div>
    </div>
</div>
