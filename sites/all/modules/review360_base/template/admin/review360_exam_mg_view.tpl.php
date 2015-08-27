<?php 
    drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_exam_view.js');
    
    $exams = get_exam_list();
    global $base_url;
    $add_new_exam_url = $base_url .'/?q=exammanagement/add';
    $exam_edit_url  = $base_url .'/?q=exammanagement/edit/';
    $exam_del_url  = $base_url .'/?q=exammanagement/del';
    $exam_list_url  = $base_url .'/?q=exammanagement/examlist';
?>
<input id="add_new_exam_url" type="hidden" value="<?php print $add_new_exam_url;?>"/>
<input id="exam_edit_url" type="hidden" value="<?php print $exam_edit_url;?>"/>
<input id="exam_del_url" type="hidden" value="<?php print $exam_del_url;?>"/>
<input id="exam_list_url" type="hidden" value="<?php print $exam_list_url;?>"/>
<label>问卷管理</label>
<hr/>
<div class="row">
    <div class="col-lg-8">
        <div>
            <div class="input-group"><div class="form-type-textfield form-item-add-user-group form-item form-group">
                <input class="form-control form-text" type="text"
                       id="edit-add-exam" name="add_exam" 
                       placeholder="请输入问卷名称"
                       value="" size="60" maxlength="128">
            </div>
            <span class="input-group-btn">
                <button class="btn btn-success btn btn-default form-submit" id="edit-submit"
                        data-loading-text="问卷添加中..."
                        name="op" value="新增问卷" type="submit">新增问卷</button>
                <button class="btn btn-default form-submit" id="edit-submit-reset" 
                        name="op" value="清空" type="button">清空</button>
            </span>
            </div>
        </div>
    </div>
</div>
<hr/>
<label>问卷列表</label>

<div class="row">
    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
      <!--<caption>用户分组列表：</caption>-->
        <thead>
            <tr>
                <th>#</th>
                <th>问卷名称</th>
                <th>题目(数量)</th>
                <th>编辑</th>
                <th>删除</th>
            </tr>
        </thead>
        <tbody id="exam_table_tb">
            <?php foreach($exams as $exam ):?>
            <tr>
                <td class=""><?php print $exam->exam_id;?></td>
                <td class=""><?php print $exam->exam_name;?></td>
                <td class=""><?php print $exam->number;?></td>
                <td class=""><a class="icon_edit" href="<?php print $exam_edit_url.$exam->exam_id?>"></a></td>
                <td class=""><a class="icon_trash"  type="button"
                                href="<?php print $exam->exam_id?>" ></a></td>
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
               <div  class="alert alert-danger" >删除问卷会导致该问卷问题也被删除！您确定要删除该问卷么？</div>
            </div>
            <div class="modal-footer">
                <input id="delExamId" type="hidden" value=""/>
                <button type="button" class="btn btn-primary" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-danger" 
                         data-loading-text="删除问卷中..."
                        id="delExamBtn">删除</button>
            </div>
        </div>
    </div>
</div>