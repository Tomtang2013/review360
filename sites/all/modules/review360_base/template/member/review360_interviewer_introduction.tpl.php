<?php
global $base_url;
if (!isset($user_key) || empty($user_key)) {
    drupal_set_message(
            t('您的调查编码有误，请重新登录。')
    );
    drupal_goto($base_url . '?q=/interviewer/onboard');
    return;
}
$user = get_user_infor_by_key($user_key);
if (!isset($user) || empty($user)) {
    drupal_set_message(
            t('您的调查编码有误，请重新登录。')
    );
    drupal_goto($base_url . '?q=/interviewer/onboard');
    return;
}

if (!isset($nid) || empty($nid)) {
    drupal_set_message(
            t('请选择评测后开始答题。')
    );
    drupal_goto($base_url . '/?q=interviewer/exam/' . $user_key);

    return;
}
$user = get_user_infor_by_key($user_key);
$goto_url = $base_url . "/?q=interviewer/survey/". $user_key."/".$nid;
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
        <div>
            <h2>指导语</h2>
            <p>欢迎您，<strong><?php print $user->u_name; ?></strong>，你正在迈出深入了解你的第一步，这种方式快捷、科学且有效。</p>
            <p>DISC是有深厚理论基础的专业工具，用于促进自我了解和人际沟通。它不是一个测验，不会有及格或不及格。</p>
            <div>
                <div>完成DISC可以帮助你：<div>
                        <div>* 更清楚地了解自己和他人</div>
                        <div>* 改善人际沟通</div>
                        <div>* 更成功地处理各类关系</div>
                        <div>* 做事更有成效</div>
                        <div>* 促进团队发展</div>
                    </div>
                    <p></p>
                    <div>
                        <div>DISC由24组短句组成，仅需10分钟左右即可完成。</div>
                        <div>* 首先细读四个短句的每一个</div>
                        <div>* 选出一个短句最能贴切地描述你</div>
                        <div>* 然后，选出哪个短句最不适合来描述你的特点</div>
                        <div>* 重复这一过程，完成全部24组短句</div>
                    </div>
                    <p></p>
                    <p> 这不存在什么正确答案，只需要根据你对自己的看法对每组词做出选择就可以了。</p>
                    <p>  这不是让你选择你未来要成为什么样子，也不是关于你认为别人会怎么看你，这仅仅是关于在大多数情况下，大多数时间里，与大多数人相处时，你认为自己是什么样的。</p>
                    <p> 在一些情况下，你可能认为在一组短句中，哪一个都不能准确地反映你，然而，你仍然必须做出选择，排定那个能最接近地描述你情况的词，然后继续。</p>
                </div>
            </div>
        </div>
        <p></p>
        <div>
              <a class="btn btn-primary " style="float:right"
                        id="edit-exam-name-btn" 
                        href="<?php print $goto_url;?>"
                             type="submit">开始答题</a>
        </div>
    </div>