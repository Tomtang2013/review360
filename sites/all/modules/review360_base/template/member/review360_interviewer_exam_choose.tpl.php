<?php 
    global $base_url;
//    $user = get_user_infor_by_key($user_key);
    $exam_nids = get_user_exam_by_key($user_key);
    dd($exam_nids);
?>
<div class="row">
     <div class="page-header">
        <div class="row">
            <div class="col-md-10 col-md-offset-1">
                <div class="progress ">
                    <div class="progress-bar " style="width: 20%;background-color:#69B4F4;">
                       识别代码登陆
                    </div>
                    <div class="progress-bar" style="width: 30%;background-color:#ffffff;">
                       受访者信息完善
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 40%;background-color:#ffffff;" >
                       问卷填写
                    </div>
                    <div class="progress-bar progress-bar-striped" style="width: 10%;background-color:#ffffff;" >
                       問卷提交
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-10 col-md-offset-1" >
        <table class="table bs-example table-striped table-responsive table-hover" style="">
      <!--<caption>用户分组列表：</caption>-->
        <thead>
            <tr>
                <th>操作</th>
                <th>评测</th>
                <th>状态</th>
                <th>预计时间</th>
            </tr>
        </thead>
        <tbody id="exam_table_tb">
            <tr>
                <td class="" style="line-height:60px;">
                    <a class="btn btn-primary " 
                            id="edit-exam-name-btn" 
                             type="submit">开始评测</a>
                </td class="" style="line-height:60px;">
                <td class=""  style="line-height:60px;border-bottom:1px solid #ddd">风向认证0.1</td>
                <td class=""  style="line-height:60px;">24</td>
                <td class=""  style="line-height:60px;">12分钟</td>
            </tr>
        </tbody>
    </table> 
    </div>
</div>