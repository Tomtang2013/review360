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

    $goto_url = $base_url."/?q=interviewer/survey/";
                           
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
                    <div class="progress-bar" style="width: 20%;background-color:#4494D8;">
                       受访者信息完善
                    </div>
                    <div class="progress-bar" style="width: 20%;background-color:#2C7CC0;">
                       评测选择
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
                <th>预计时间</th>
            </tr>
        </thead>
        <tbody id="exam_table_tb">
            <?php foreach($exam_nids as $exam_nid): 
                $exam = node_load($exam_nid->nid);
                $url = $goto_url.$user_key."/$exam_nid->nid";
                $is_submited = is_submited($exam_nid->nid);
                dd($is_submited);
                if($is_submited == 1){
                    update_user_exam_status($exam_nid->nid);
                }
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
                <td class=""  style="line-height:60px;">12分钟</td>
            </tr>
            <?php endforeach;?>
        </tbody>
    </table> 
    </div>
</div>