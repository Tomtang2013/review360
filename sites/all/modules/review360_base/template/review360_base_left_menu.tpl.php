<?php 
$get_q = $_GET['q'];
global $user; if($user->uid > 0):?>
<div>
    <h4><strong>工作栏</strong></h4>
    <ul class="nav nav-pills nav-stacked" role="tablist" style="max-width: 300px;">
        <?php print rend_left_menu_li($get_q,'用户管理','usermanagement')?>
        <?php print rend_left_menu_li($get_q,'调查管理','surveymanagement')?>
        <?php print rend_left_menu_li($get_q,'题库管理','exammanagement')?>
    </ul>
</div>
<!--
<div style="padding-top: 10px;">
    <h4>成员</h4>
    <ul class="nav nav-pills nav-stacked" role="tablist" style="max-width: 300px;">
        <?php // print rend_left_menu_li($get_q,'分配情况','accountinfo/member_allocation_status')?>
        <?php // print rend_left_menu_li($get_q,'使用状态录入','accountinfo/member_status_record')?>
         <?php // print rend_left_menu_li($get_q,'账号修改','accountinfo/account_info_update')?>
    </ul>
</div> -->
<?php endif ?>