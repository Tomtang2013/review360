<?php 
drupal_add_js(drupal_get_path('module','vw_progressbar').'/js/jquery.filedrop.js');
drupal_add_js(drupal_get_path('module','vw_progressbar').'/js/script.js');
drupal_add_css(drupal_get_path('module','vw_progressbar').'/css/progressbar.css');
global $base_url;
$upload_url = $base_url .'/vw/progress_example/progressbar/uploadtemp';
?>
<div class="form-item form-group">
    <label for="">file </label>
    <div class="file-widget form-managed-file clearfix input-group">
        <input class="form-control form-file" type="file" id="edit-field-file-und-0-upload" 
               name="files[field_file_und_0]" size="22" style="display: none;">
        <span class="input-group-btn">
            <button class="btn btn-default form-submit ajax-processed" 
                    id="edit-field-file-und-0-upload-button" 
                    name="field_file_und_0_upload_button" value="Upload" 
                    type="submit" style="display: none;">Upload</button>
        </span></div><input type="hidden" name="field_file[und][0][fid]" value="0">
    <input type="hidden" name="field_file[und][0][display]" value="1">
    <div class="file-resup-wrapper"><input class="file-resup file-resup-processed" data-upload-name="files[field_file_und_0]" data-upload-button-name="field_file_und_0_upload_button" data-max-filesize="2147483648" data-description="Files must be less than <strong>2 GB</strong>.<br />Allowed file types: <strong>txt</strong>." data-url="/review360/file_resup/upload/field_file/und/0/form-MEITBvRPZURqpoavwNqSpsdAeX-xJOpX1UA-jQVWFKY" data-drop-message="Drop a file here or click <em>Browse</em> below." data-extensions="txt" data-max-files="1" type="hidden" name="field_file[und][0][resup]" value="" id="file-resup-0">
        <div class="item-list drop" id="dropbox" style="display: table;
                                            box-sizing: border-box;
                                            width: 100%;
                                            border: 1px dashed #ccc;
                                            height: 180px;">
            <div class="drop-message" style="  display: table-cell;
                            text-align: center;
                            vertical-align: middle;
                            padding: 0 1em;
                            color: #bbb;
                            cursor: default;">
                Drop a file here or click <em>Browse</em> below.</div></div>
    <p class="help-block">Files must be less than <strong>2 GB</strong>.
    <br>Allowed file types: <strong>txt</strong>.
    <br>uploaded : <strong id="progress_num">0</strong>%.</p>
</div> 

<input type="hidden" id="uploadFileTemp" value="<?php echo $upload_url; ?>">