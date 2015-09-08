<?php 
    global $base_url;
    if(!isset($user_key) || empty($user_key)){
        drupal_goto($base_url.'/interviewer/onboard');
        return;
    } 
    $user = get_user_infor_by_key($user_key);
    if(!isset($user) || empty($user)){
        drupal_goto($base_url.'/interviewer/onboard');
        return;
    } 

    $goto_url = $base_url."/?q=interviewer/introduction/";
                           
    $exam_nids = get_user_exam_by_key($user_key);
    
?>
<div class="row">
     <div class="page-header">
        <div class="row">
            <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#69B4F4;">
                       填写个人信息
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#4494D8;">
                       需完成测评列表
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#ffffff;" >
                       评测填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 20%;background-color:#ffffff;" >
                       评测提交
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-10 col-md-offset-1" >
        <table class="table bs-example table-striped table-responsive table-hover" style="">
        <thead>
            <tr>
                <th>操作</th>
                <th>评测</th>
                <th>状态</th>
                <th>作答时间</th>
            </tr>
        </thead>
        <tbody id="exam_table_tb">
            <?php foreach($exam_nids as $exam_nid): 
                $exam = node_load($exam_nid->nid);
                $url = $goto_url.$user_key."/$exam_nid->nid";
                $is_submited = is_submited($exam_nid->nid);
                if($exam->webform['redirect_url'] == '<confirmation>'){
                   $exam->webform['redirect_url'] ='interviewer/survey/submitted/' . $user->survey_user_key."/".$exam->nid;
                   node_object_prepare($exam);
                   node_submit($exam);
                   node_save($exam);
                }
                $exam_infor = get_selectable_exam_by_name($exam_nid->nick_name);

            ?>
            <tr>
                <td class="" style="line-height:60px;">
                    <?php if($is_submited == 0):?>
                        <a class="btn btn-primary " 
                        id="edit-exam-name-btn" 
                        href="<?php print $url;?>"
                             type="submit">开始评测</a>
                    <?php else: ?>
                        <div class="btn btn-success " 
                            id="edit-exam-name-btn" 
                             type="submit">已经完成</div>
                     <?php endif;?>
                </td >
                <td class=""  style="line-height:60px;"><?php print $exam_nid->nick_name; ?></td>
                <td class=""  style="line-height:60px;"><?php print $is_submited == 0?"未答题":"已完成"?></td>
                <td class=""  style="line-height:60px;"><?php print $exam_infor->spend_time." 分钟"?></td>
            </tr>
            <?php endforeach;?>
        </tbody>
    </table> 
    </div>
</div>