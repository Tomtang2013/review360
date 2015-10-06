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
//        '#default_value' => $infor->survey_name,
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
//        '#default_value' => $infor->survey_name,
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
    
    if(survey_key_already_used($form_state['values']['interview_key'],$form_state['values']['interview_email'] )){
        form_set_error('interview_key', t('该识别代码已被他人使用，请联系管理员。'));
    }
}

function survey_key_already_used($key,$email){
    $query = "select count(su_id) used from 
            review360_survey_user
            where 1=1
            and survey_user_key = '$key'
            and (u_email is Null or u_email = '$email')";

    $result = db_query($query)->fetchField();
    if($result == 1) {
        return false;
    }
    return true;
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
        '#default_value' => prepare_default_value($user->u_sex),
        
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
 
    $form['infor_u_birthday'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
             <div class="input-group date form_date " data-date="2015-01-01" 
             data-date-format="yyyy-mm-dd" data-link-field="dtp_start_date">
             <span class="input-group-addon" id="sizing-addon1">出生年月</span>',
        '#suffix' => '
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-remove"></span></span>
                <span class="input-group-addon"><span class="btn-icon glyphicon glyphicon-th"></span></span>
                </div>
                <input type="hidden" id="dtp_start_date" value="" /></div>',
          '#default_value' => prepare_timestamp_to_str($user->u_birthday),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'出生年月',
            'title'=>'出生年月。'
        ),
    );
    
    $form['infor_p_number'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">手机号码</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => prepare_default_value($user->u_p_number),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'手机号码',
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
    
    
    $form['infor_work_nature'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">从事行业</span> ',
        '#suffix' => '</div>',
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
    
    $form['infor_department'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-infor-item">
            <span class="input-group-addon" id="sizing-addon1">部门名称</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => prepare_default_value($user->u_department),
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'您当前所在部门名称',
        ),
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#default_value' => '提交',
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
  
    if (empty($form_state['values']['infor_sex'])) {
        form_set_error('infor_sex',t("请选择性别。"));
    }
    
    if (empty($form_state['values']['infor_company_name'])) {
        form_set_error('infor_company_name',t("公司名称不能为空。"));
    }
    
    $pattern = "/^[a-z0-9]+([._\\-]*[a-z0-9])*@([a-z0-9]+[-a-z0-9]*[a-z0-9]+.){1,63}[a-z0-9]+$/";
    if( !preg_match( $pattern, $form_state['values']['infor_email'] )){
        form_set_error('infor_email', t('邮件地址不合法，请重新填写。'));
    } 
    
    $pattern = "/^13[0-9]{1}[0-9]{8}$|15[0189]{1}[0-9]{8}$|189[0-9]{8}$/";
    if(!preg_match($pattern,$form_state['values']['infor_p_number'])){    
        form_set_error('infor_p_number', t('手机号码不合法，请重新填写。'));
    }
    
    
    
//    $pattern = "/^13[0-9]{1}[0-9]{8}$|15[0189]{1}[0-9]{8}$|189[0-9]{8}$/";
//    if(!preg_match($pattern,$form_state['values']['infor_p_number'])){    
//        form_set_error('infor_p_number', t('手机号码不合法，请重新填写。'));
//    }
//    
   
}

function review_interviewer_infor_form_submit($form, &$form_state) {
    $infor = $form_state['values'];
    update_infor_by_key($infor);
    drupal_goto('interviewer/exam/'.$form_state['values']['infor_key']);
}

function update_infor_by_key($infor){
    
    $q = db_update('review360_survey_user')
            ->fields(array(
                'u_email' => $infor['infor_email'],
                'u_name' => $infor['infor_name'],
                'u_sex' => $infor['infor_sex'],
                'u_birthday' => prepare_date_to_timestamp($infor['infor_u_birthday']),
                'u_p_number' => $infor['infor_p_number'],
                'u_bachelor' => $infor['infor_bachelor'],
                'u_specialty' => $infor['infor_specialty'],
                'u_university' => $infor['infor_university'],
                'u_experience' => $infor['infor_experience'],
                'u_engaged' => $infor['infor_engaged'],
                'u_company_name' => $infor['infor_company_name'],
                'u_department' => $infor['infor_department'],
                'u_work_nature' => $infor['infor_work_nature'],
                'update_date' => time(),
            ))
            ->condition('survey_user_key', $infor['infor_key']);
			
			
            $q->execute();

    drupal_set_message(t("个人信息保存成功，请选择评测。"));
}