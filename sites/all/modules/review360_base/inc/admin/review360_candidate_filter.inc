<?php

function review360_candidate_filter_view(){
    $action_name = theme('review360_candidate_filter_view');
    $pageContent = theme('right_content', array('page_content' => $action_name, 'is_html' => true));
    return $pageContent;
}

function review_candidate_filter_form($form_state, $args) {
    $form = array();
 
    $form['candidate_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">用户姓名</span>',
        '#suffix' => '</div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'用户姓名',
        ),
    );
    
    $form['candidate_survey_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6">
            <span class="input-group-addon" id="sizing-addon1">调查名称</span>',
        '#suffix' => '</div></div>',
        '#default_value' => '',
         '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'调查名称',
            'title'=>'用户所在调查的名称'
        ),
    );
    
    
     $form['candidate_email'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">登陆邮箱</span> ',
        '#suffix' => '<span class="input-group-addon" id="basic-addon1">@</span></div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'邮箱地址',
        ),
    );

 
 $form['candidate_sex'] = array(
        '#type' => 'radios',
        '#prefix' => '
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">客户性别</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => '',
        
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
 
    $form['candidate_p_number'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">手机号码</span> ',
        '#suffix' => '</div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'手机号码',
        ),
    );

    $form['candidate_bachelor'] = array(
        '#type' => 'select',
        '#prefix' => '
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">最高学位</span> ',
        '#suffix' => '</div></div>',
        '#options' => bachelor_array(),
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您正在攻读或已获得的最高学位',
        ),
    );
    
     $form['candidate_specialty'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">攻读专业</span> ',
        '#suffix' => '</div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您当攻读的专业类别',
        ),
        '#options' => specialty_array(),
    );

    $form['candidate_university'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">高校名称</span> ',
        '#suffix' => 
        //' <span class="input-group-addon"><span class="school-remove-btn btn-icon glyphicon glyphicon-remove"></span></span>
         //       <span class="input-group-addon"><span class="school-list-btn btn-icon glyphicon glyphicon-th-list"></span></span>
           '     </div></div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
        //    'readonly' =>'',
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'placeholder'=>'',
            'title'=>'您所在或毕业的高校名称。'
        ),
    );
    
    $form['candidate_experience'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">工作经验</span> ',
        '#suffix' => '</div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'从事该工作的工作年限',
        ),
        '#options' => experience_array(),
    );

    $form['candidate_engaged'] = array(
        '#type' => 'select',
        '#prefix' => '
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">从事行业</span> ',
        '#suffix' => '</div></div>',
        '#options' => engaged_array(),
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您目前从事的行业',
        ),
    );
    
    $form['candidate_company_name'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">公司名称</span> ',
        '#suffix' => '</div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您当前所在公司名称',
        ),
    );

    $form['candidate_department'] = array(
        '#type' => 'textfield',
        '#prefix' => '
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">部门姓名</span> ',
        '#suffix' => '</div></div>',
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
             'placeholder'=>'您当前所在部门名称',
        ),
    );
    
    $form['candidate_work_nature'] = array(
        '#type' => 'select',
        '#prefix' => '
            <div class="col-md-12 form-line">
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">从事行业</span> ',
        '#suffix' => '</div>',
        '#options' => array(
            0=>'-- 请选择 --',
            '管理'=>'管理',
            '非管理'=>'非管理',
        ),
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'您目前从事的工作性质',
        ),
    );
    
    $form['candidate_tools'] = array(
        '#type' => 'textfield',
        '#prefix' => '
           
            <div class="input-group col-md-6 user-candidate-item">
            <span class="input-group-addon" id="sizing-addon1">测验工具</span> ',
        '#suffix' => '</div></div>',
        
        '#default_value' => '',
        '#attributes' => array(
            'class' => array(
                'form-control',
            ),
            'placeholder'=>'测验工具',
        ),
    );
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => '检索',
        '#prefix' => ' <div class="col-md-12 form-line"> '
        . '<div class="input-group col-md-offset-6 col-md-6 user-candidate-item">'
        . '<span class="input-group-btn">',
        '#suffix' => '</span></div></div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-success',
            ),
            'style'=>array('float:right;'),
            'data-toggle' =>'tooltip',
            'data-placement'=>'bottom',
            'title'=>'根据筛选条件进行检索。'
        ),
    );
	
    return $form;
}

function review_candidate_filter_form_validate($form, &$form_state) {
//    $file = file_save_upload('file_upload', array(
//        'file_validate_is_excel' => array(),
//        'file_validate_extensions' => array('CSV XLSX XLS'),
//    ));
//
//    if ($file) {
//        if ($file = file_move($file, 'public://')) {
//            $form_state['storage']['file'] = $file;
//        } else {
//            form_set_error('file', t("写入文件失败，请检查权限。"));
//        }
//    } else {
//        form_set_error('file', t('文件上传失败，请检查文件类型。'));
//    }
}

function review_candidate_filter_form_submit($form, &$form_state) {
    $infor = $form_state['values'];
    $serach_query_str = generate_search_infor_by_condition_sql($infor);
    variable_set('serach_query_str',$serach_query_str);
}
function generate_search_infor_by_condition_sql($infor){
    $query = "select rsu.survey_id,rsu.survey_user_key, u_name,survey_name,u_company_name,survey_nid_name,u_p_number,u_email,rsu.nid
            from review360_survey_user rsu
            inner join review360_survey  rs on rsu.survey_id = rs.survey_id
            where u_name is not null ";

    $query .=append_condition($infor['candidate_name'], 'rsu.u_name');
    $query .=append_condition($infor['candidate_survey_name'], 'rs.survey_name');
    $query .=append_condition($infor['candidate_email'], 'rsu.u_email');
    $query .=append_condition($infor['candidate_sex'], 'rsu.u_sex');
    $query .=append_condition($infor['candidate_p_number'], 'rsu.u_p_number');
    $query .=append_condition($infor['candidate_bachelor'], 'rsu.u_bachelor',true);
    $query .=append_condition($infor['candidate_specialty'], 'rsu.u_specialty');
    $query .=append_condition($infor['candidate_university'], 'rsu.u_university');
    $query .=append_condition($infor['candidate_experience'], 'rsu.u_experience',true);
    $query .=append_condition($infor['candidate_engaged'], 'rsu.u_engaged');
    $query .=append_condition($infor['candidate_company_name'], 'rsu.u_company_name');
    $query .=append_condition($infor['candidate_department'], 'rsu.u_department');
    $query .=append_condition($infor['candidate_work_nature'], 'rsu.u_work_nature');
    $query .=append_condition($infor['candidate_tools'], 'rs.survey_nid_name');
   
    return $query;
}

function append_condition($value,$col_name,$equal = false){
    if(!$equal){
        if(!empty($value)){
            return " and $col_name like '%$value%' ";
        }
    } else {
         if(!empty($value)){
            return " and $col_name = $value ";
        }
    }
   
    return '';
}

function search_infor_by_condition($query){
   return $result = db_query($query)->fetchAll();
}
function get_survey_rst_ajax(){
    $sid = $_POST['sid'];
    $user_key = $_POST['uk'];
    $exams = load_survey_user_exam_by_sid_user_key($sid,$user_key);
    $result = get_survey_result($exams,$sid,$user_key);
    if ($result) {
        echo drupal_json_output(array('status' => 'success','rst'=>$result));
    } else {
        echo drupal_json_output(array('status' => 'failed','rst'=>$result));
    }
}

//function perpare_exam_result($nick_name,$nid,$survey_exam){
//    
//}



