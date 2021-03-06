<?php 
    drupal_add_js(drupal_get_path('module','review360_base').'/js/admin/review360_exam_edit.js');
    global $base_url;
    
    $exam = get_exam_by_id($exam_id);
    
    $exam_export_url = $base_url .'/?q=export_exam_file/';
    $exam_upload_url = $base_url .'/?q=exammanagement/upload/';
    $exam_edit_name_url = $base_url .'/?q=exammanagement/changename/';
?>
<input id="exam_export_url" type="hidden" value="<?php print $exam_export_url.$exam->exam_id;?>"/>
<input id="exam_upload_url" type="hidden" value="<?php print $exam_upload_url;?>"/>
<input id="exam_edit_name_url" type="hidden" value="<?php print $exam_edit_name_url;?>"/>
<input id="exam_id" type="hidden" value="<?php print $exam->exam_id;?>"/>
</hr>
<div class="row">
    <div class="col-lg-8">
        <label>问卷编辑:</label>
        <hr/>
        <div class="row">
            <div class="col-lg-6">
                <div class="input-group">
                    <span class="input-group-addon" id="sizing-addon1">试卷名称</span>
                    <div class="form-type-file form-item-files-file-upload form-item form-group">

                        <input class="form-control form-file" 
                               type="text" id="exam-name-input"
                               name="" size="60" value="<?php print $exam->exam_name ?>">
                    </div>
                </div>
            </div>
             <div class="col-lg-6">
                <div class="input-group">
                    <span class="input-group-addon" id="sizing-addon1">作答时间</span>
                    <div class="form-type-file form-item-files-file-upload form-item form-group">

                        <input class="form-control form-file" 
                               type="text" id="exam-spend-time-input" data-toggle="tooltip"
                               data-placement="bottom"
                               data-original-title="预计完成该试卷所需时间，单位为分钟。"
                               name="" size="60" value="<?php print $exam->spend_time ?>">
                    </div>
                </div>
            </div>
            <div class="col-lg-6 col-lg-offset-6" style="padding-top: 20px;">
                    <button class="btn btn-primary btn btn-default form-submit" 
                        id="edit-exam-name-btn" name="op" style="float:right;"
                        data-loading-text="修改中..."
                        value="修改问卷名称" type="submit">修改问卷信息</button>
            </div>
        </div>
        <hr/>
        
        <label>问卷上传:</label>
        <div class="row">
             <?php 
                $form = drupal_get_form('review360_exam_upload_form',$exam);
                print drupal_render($form) ;
             ?>
             <div class="col-lg-8" style='padding-top: 5px;'>
                <span class="label label-warning">请选择导入的文本文件为以下类型：</span>
                <span class="label label-success">CSV</span>
                <span class="label label-success">XSL</span>
                <span class="label label-success">XLSX</span>
            </div>
        </div>
    </div>
   
</div>
<hr/>