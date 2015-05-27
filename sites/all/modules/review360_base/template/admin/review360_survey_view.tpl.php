<?php 
    drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_survey_view.js');
    
    $surveys = get_survey_list();
    global $base_url;
    $add_new_survey_url = $base_url .'/surveymanagement/add';
    $survey_edit_url  = $base_url .'/surveymanagement/edit/';
    $survey_del_url  = $base_url .'/surveymanagement/del';
    $survey_list_url  = $base_url .'/surveymanagement/surveylist';
?>
<input id="add_new_survey_url" type="hidden" value="<?php print $add_new_survey_url;?>"/>
<input id="survey_edit_url" type="hidden" value="<?php print $survey_edit_url;?>"/>
<input id="survey_del_url" type="hidden" value="<?php print $survey_del_url;?>"/>
<input id="survey_list_url" type="hidden" value="<?php print $survey_list_url;?>"/>
<label>调查管理</label>
<hr/>
<div class="row">
    <div class="col-lg-8">
        <div>
            <div class="input-group"><div class="form-type-textfield form-item-add-user-group form-item form-group">
                <input class="form-control form-text" type="text"
                       id="edit-add-survey" name="add_survey" 
                       placeholder="请输入问调查名称"
                       value="" size="60" maxlength="128">
            </div>
            <span class="input-group-btn">
                <button class="btn btn-success btn btn-default form-submit" id="edit-submit"
                        data-loading-text="问卷添加中..."
                        name="op" value="新增问卷" type="submit">新增调查</button>
                <button class="btn btn-default form-submit" id="edit-submit-reset" 
                        name="op" value="清空" type="button">清空</button>
            </span>
            </div>
        </div>
    </div>
</div>
<hr/>
<label>调查列表</label>

<div class="row">
    <table class="table bs-example table-striped table-responsive table-hover" style="margin-left:10px;width:90%;">
        <thead>
            <tr>
                <th>#</th>
                <th>调查名称</th>
                <th>人员(数量)</th>
                <th>状态</th>
                <th>起始时间</th>
                <th>结束时间</th>
                <th>编辑</th>
                <th>删除</th>
            </tr>
        </thead>
        <tbody id="survey_table_tb">
            <?php foreach($surveys as $survey ):?>
            <tr>
                <td class=""><?php print $survey->survey_id;?></td>
                <td class=""><?php print $survey->survey_name;?></td>
                <td class=""><?php print $survey->survey_user_num;?></td>
                <td class=""><?php print $survey->survey_status_str;?></td>
                <td class=""><?php print empty($survey->start_date)?'': prepare_timestamp_to_str($survey->start_date);?></td>
                <td class=""><?php print empty($survey->end_date)?'':prepare_timestamp_to_str($survey->end_date);?></td>
                
                <td class=""><a class="icon_edit" href="<?php print $survey_edit_url.$survey->survey_id?>"></a></td>
                <?php if ($survey->survey_status == 0): ?>
                <td class=""><a class="icon_trash"  type="button"
                                href="<?php print $survey->survey_id ?>" ></a></td>
                <?php else: ?>
                <td class=""><div class="icon_trash"  type="button"
                                data-toggle='tooltip'
                                data-placement='bottom'
                                title='已经被激活的调查无法被删除！' ></div></td>
                <?php endif; ?>
            </tr>
            <?php  endforeach;?>
        </tbody>
    </table>
</div>
<!-- Modal -->
<div class="modal fade bs-surveyple-modal-sm" id="delCheckBox"
     tabindex="-1" role="dialog" aria-labelledby="delCheckBox" aria-hidden="true">
    <div class="modal-dialog modal-sm">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">确认删除</h4>
            </div>
            <div class="modal-body">
                <div  class="alert alert-danger" >
                    <p>删除调查会导致该调查相关信息也被删除！您确定要删除该调查么？</p>
                </div>
            </div>
            <div class="modal-footer">
                <input id="delSurvyId" type="hidden" value=""/>
                <button type="button" class="btn btn-primary" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-danger" 
                         data-loading-text="删除调查中..."
                        id="delSurvyBtn">删除</button>
            </div>
        </div>
    </div>
</div>
