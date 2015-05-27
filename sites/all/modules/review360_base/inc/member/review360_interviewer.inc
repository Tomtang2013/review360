<?php

function review360_interviewer_onboard() {
    $action_name = theme('review360_interviewer_onboard_view');
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review_interviewer_onboard_form($form_state, $args) {
    $form = array();
    $form['interview_description'] = array(
        '#type' => 'item',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-12">',
        '#title' => '<h2>'.t('欢迎使用本系统！').'</h2>',
        '#suffix' => '</div></div>',
    );
    $form['interview_email'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-12">
            <span class="input-group-addon" id="sizing-addon1">登陆邮箱</span> ',
        '#suffix' => '<span class="input-group-addon" id="basic-addon1">@</span></div></div>',
//        '#default_value' => $survey->survey_name,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'邮箱地址',
        ),
    );

    $form['interview_key'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-12">
            <span class="input-group-addon" id="sizing-addon1">识别代码</span> ',
        '#suffix' => '</div></div>',
//        '#default_value' => $survey->survey_name,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'识别代码',
        ),
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#default_value' => '登录',
        '#prefix' => '<div class="col-md-12 form-line">'
        . '<div class="btn-group col-md-4 pull-right" role="group" aria-label="" >'
        . '<span class="input-group-btn">',
        '#attributes' => array(
            'class' => array(
                'btn btn-success',
            ),
            'style' => 'width:50%;',
        ),
    );


    $form['submit_reset'] = array(
        '#type' => 'button',
        '#default_value' => '取消',
        '#suffix' => '</span></div></div>',
        '#attributes' => array(
            'class' => array(
                'btn ',
            ),
        'style' => 'width:50%;',
        ),
    );

    return $form;
}


function review_interviewer_onboard_form_validate($form, &$form_state) {
    if (empty($form_state['values']['interview_email'])) {
        form_set_error('interview_email',t("邮箱地址不能为空。"));
    }
    
    
    if (empty($form_state['values']['interview_key'])) {
         form_set_error('interview_key',t("调查识别码不能为空。"));
    } 
    
    $pattern = "/^[a-z0-9]+([._\\-]*[a-z0-9])*@([a-z0-9]+[-a-z0-9]*[a-z0-9]+.){1,63}[a-z0-9]+$/";
    if( !preg_match( $pattern, $form_state['values']['interview_email'] )){
        form_set_error('interview_email', t('邮件地址不合法，请重新填写。'));
    } 
    
    if( !survey_key_validate(  $form_state['values']['interview_key'] )){
        form_set_error('interview_key', t('该识别代码不存在，请核对后重试。'));
    } 
}

function survey_key_validate($key){
     $query = "select count(su_id) num from review360_survey_user
            where survey_user_key = '$key'";
    $result = db_query($query)->fetchField();
    if($result == 1) {
        return true;
    }
    return false;
}

function review_interviewer_onboard_form_submit($form, &$form_state) {
    $onboard = $form_state['values'];
    db_update('review360_survey_user')
      ->fields(array(
        'u_email' => $onboard['interview_email'],
        'update_date' => time(),
      ))
      ->condition('survey_user_key', $onboard['interview_key'])
      ->execute();
//    Global $base_path;
    drupal_goto('interviewer/infor/'.$form_state['values']['interview_key']);
}


function review360_interviewer_infor($key){
    $action_name = theme('review360_interviewer_infor_view',array('user_key'=>$key));
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}


function review_interviewer_infor_form($form_state, $args) {
    $form = array();
    $user = prepare_form_stdClass($args);
    
    $form['su_id'] = array('#type' => 'hidden', '#value' => $user->su_id);
    
    $form['infor_desc'] = array(
        '#type' => 'item',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-12">',
        '#title' => '<h2>'.t('受访者信息录入').'</h2>',
        '#suffix' => '</div></div><hr/>',
    );
    $form['infor_email'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">登陆邮箱</span> ',
        '#suffix' => '<span class="input-group-addon" id="basic-addon1">@</span></div>',
        '#default_value' => $user->u_email,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'邮箱地址',
        ),
    );

    $form['infor_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">客户姓名</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => prepare_default_value($user->u_name),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'受访者姓名',
        ),
    );
  
    $form['infor_key'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">识别代码</span> ',
        '#suffix' => '</div>',
        '#default_value' => $user->survey_user_key,
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'识别代码',
            'readonly'=>'',
        ),
    );
    
    $form['infor_sex'] = array(
        '#type' => 'radios',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">客户性别</span> ',
        '#suffix' => '</div></div></div>',
        '#default_value' => prepare_default_value($user->u_name),
        
        '#type' => 'radios',
        '#options' => drupal_map_assoc(
            array(
            '男'=>  t('男'),
            '女'=> t('女'),
            )
          ),
        
        '#attributes' => array(
            'class' => array(
                'col-md-12',
                'form-radio-btn'
            ),
             'placeholder'=>'受访者姓名',
        ),
    );
 
    $form['infor_p_number'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">手机号码</span> ',
        '#suffix' => '</div>',
        '#default_value' => prepare_default_value($user->u_p_number),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'手机号码',
        ),
    );

    $form['infor_bachelor'] = array(
        '#type' => 'select',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">最高学位</span> ',
        '#suffix' => '</div></div>',
        '#options' => bachelor_array(),
        '#default_value' => prepare_default_value($user->u_bachelor),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您正在攻读或已获得的最高学位',
        ),
    );
    
     $form['infor_specialty'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">攻读专业</span> ',
        '#suffix' => '</div>',
        '#default_value' => prepare_default_value($user->u_specialty),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您当攻读的专业类别',
        ),
        '#options' => specialty_array(),
    );

    $form['infor_university'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">高校名称</span> ',
        '#suffix' => ' <span class="input-group-addon"><span class="school-remove-btn btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class="school-list-btn btn-icon glyphicon glyphicon-th-list"></span></span>
                </div></div>',
        '#default_value' => prepare_default_value($user->u_university),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'',
            'title'=>'您所在或毕业的高校名称。'
        ),
    );
    
    $form['infor_experience'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">工作经验</span> ',
        '#suffix' => '</div>',
        '#default_value' => prepare_default_value($user->u_experience),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'从事该工作的工作年限',
        ),
        '#options' => experience_array(),
    );

    $form['infor_engaged'] = array(
        '#type' => 'select',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">从事行业</span> ',
        '#suffix' => '</div></div>',
        '#options' => engaged_array(),
        '#default_value' => prepare_default_value($user->u_engaged),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您目前从事的行业',
        ),
    );
    
    $form['infor_company_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">公司名称</span> ',
        '#suffix' => '</div>',
        '#default_value' => prepare_default_value($user->u_company_name),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您当前所在公司名称',
        ),
    );

    $form['infor_department'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">部门姓名</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => prepare_default_value($user->u_department),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'您当前所在部门名称',
        ),
    );
    
    $form['infor_work_nature'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">从事行业</span> ',
        '#suffix' => '</div></div>',
        '#options' => array(
            0=>'-- 请选择 --',
            '管理'=>'管理',
            '非管理'=>'非管理',
        ),
        '#default_value' => prepare_default_value($user->u_work_nature),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您目前从事的工作性质',
        ),
    );
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#default_value' => '提交并开始答题',
        '#prefix' => '<div class="col-md-12 form-line">'
        . '<div class="btn-group col-md-4 pull-right" role="group" aria-label="" >'
        . '<span class="input-group-btn">',
        '#attributes' => array(
            'class' => array(
                'btn btn-success',
            ),
            'style' => 'width:70%;',
        ),
    );


    $form['submit_reset'] = array(
        '#type' => 'button',
        '#default_value' => '取消',
        '#suffix' => '</span></div></div>',
        '#attributes' => array(
            'class' => array(
                'btn ',
            ),
        'style' => 'width:30%;',
        ),
    );

    return $form;
}


function review_interviewer_infor_form_validate($form, &$form_state) {
    if (empty($form_state['values']['infor_email'])) {
        form_set_error('infor_email',t("邮箱地址不能为空。"));
    }
    
    if (empty($form_state['values']['infor_name'])) {
        form_set_error('infor_name',t("受访者姓名不能为空。"));
    }
    
    $pattern = "/^[a-z0-9]+([._\\-]*[a-z0-9])*@([a-z0-9]+[-a-z0-9]*[a-z0-9]+.){1,63}[a-z0-9]+$/";
    if( !preg_match( $pattern, $form_state['values']['infor_email'] )){
        form_set_error('infor_email', t('邮件地址不合法，请重新填写。'));
    } 
}

function review_interviewer_infor_form_submit($form, &$form_state) {
    drupal_goto('interviewer/survey/'.$form_state['values']['infor_key']);
}


function engaged_array(){
    return array(
            0 => '-- 请选择 --',
            'IT/软硬件服务/电子商务/因特网运营' => 'IT/软硬件服务/电子商务/因特网运营',
            '快速消费品(食品/饮料/化妆品)' => '快速消费品(食品/饮料/化妆品)',
            '批发/零售' => '批发/零售',
            '服装/纺织/皮革' => '服装/纺织/皮革',
            '家具/工艺品/玩具' => '家具/工艺品/玩具',
            '教育/培训/科研/院校' => '教育/培训/科研/院校',
            '家电' => '家电',
            '通信/电信运营/网络设备/增值服务' => '通信/电信运营/网络设备/增值服务',
            '制造业 ' => '制造业',
            '汽车及零配件' => '汽车及零配件',
            '餐饮/娱乐/旅游/酒店/生活服务' => '餐饮/娱乐/旅游/酒店/生活服务',
            '办公用品及设备' => '办公用品及设备',
            '会计/审计' => '会计/审计',
            '法律' => '法律',
            '银行/保险/证券/投资银行/风险基金' => '银行/保险/证券/投资银行/风险基金',
            '电子技术/半导体/集成电路' => '电子技术/半导体/集成电路',
            '仪器仪表/工业自动化' => '仪器仪表/工业自动化',
            '贸易/进出口' => '贸易/进出口',
            '机械/设备/重工' => '机械/设备/重工',
            '制药/生物工程/医疗设备/器械' => '制药/生物工程/医疗设备/器械',
            '医疗/护理/保健/卫生' => '医疗/护理/保健/卫生',
            '广告/公关/媒体/艺术' => '广告/公关/媒体/艺术',
            '出版/印刷/包装' => '出版/印刷/包装',
            '房地产开发/建筑工程/装潢/设计' => '房地产开发/建筑工程/装潢/设计',
            '物业管理/商业中心' => '物业管理/商业中心',
            '中介/咨询/猎头/认证' => '中介/咨询/猎头/认证',
            '交通/运输/物流' => '交通/运输/物流',
            '航天/航空/能源/化工' => '航天/航空/能源/化工',
            '农业/渔业/林业' => '农业/渔业/林业',
            '其他行业' => '其他行业',
        );
}

function experience_array(){
    return array(
            0=>'-- 请选择 --',
            1=>'1年以下',
            2=>'1~2年',
            3=>'2~3年',
            4=>'3~5年',
            5=>'5~10年',
            6=>'10~20年',
            7=>'20年以上',
        );
}

function specialty_array(){
    return array(
            0 => '-- 请选择 --',
            '哲学' => '哲学',
            '经济学' => '经济学',
            '法学' => '法学',
            '教育学' => '教育学',
            '文学' => '文学',
            '历史学' => '历史学',
            '理学' => '理学',
            '工学' => '工学',
            '农学' => '农学',
            '医学' => '医学',
            '哲学' => '军事学',
            '管理学' => '管理学',
        );
}

function bachelor_array(){
    return array(
            0=>'-- 请选择 --',
            1=>'高中以下',
            2=>'中专或高中',
            3=>'大专',
            4=>'大学本科',
            5=>'硕士研究生',
            6=>'博士研究生及以上',
        );
}

