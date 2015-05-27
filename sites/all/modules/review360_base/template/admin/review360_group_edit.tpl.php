<?php 
    drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_group_edit.js');
    global $base_url;
    
    $group = get_group_by_id($group_id);
    
    $group_upload_url = $base_url .'/usermanagement/upload/';
    $group_edit_name_url = $base_url .'/usermanagement/group/changename/';
    $group_export_url = $base_url .'/export_user_file/';
?>
<input id="group_upload_url" type="hidden" value="<?php print $group_upload_url;?>"/>
<input id="group_edit_name_url" type="hidden" value="<?php print $group_edit_name_url;?>"/>
<input id="group_id" type="hidden" value="<?php print $group->group_id;?>"/>
<input id="group_export_url" type="hidden" value="<?php print $group_export_url.$group->group_id;?>"/>

</hr>
<div class="row">
    <div class="col-lg-8">
        <label>分组编辑:</label>
        <hr/>
        <div style="">
            <div class="input-group">
                <div class="form-type-file form-item-files-file-upload form-item form-group">
                    <input class="form-control form-file" 
                           type="text" id="group-name-input"
                           name="files[file_upload]" size="60" value="<?php print $group->group_name?>">
                </div>
                <span class="input-group-btn">
                    <button class="btn btn-primary btn btn-default form-submit" id="edit-group-name-btn" name="op" 
                            data-loading-text="修改中..."
                            value="修改分组名称" type="submit">修改分组名称</button>
                </span>
                
            </div>
        </div>
        <hr/>
        <label>用户上传:</label>
        <?php print drupal_render(drupal_get_form('review360_user_upload_form',$group)) ;?>
    </div>
    <div class="col-lg-8" style='padding-top: 5px;'>
        <span class="label label-warning">请选择导入的文本文件为以下类型：</span>
        <span class="label label-success">CSV</span>
        <span class="label label-success">XSL</span>
        <span class="label label-success">XLSX</span>
    </div>
</div>
<hr/>