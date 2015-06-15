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
    $query = "select u_name,survey_name,u_company_name,survey_nid_name,u_p_number,u_email,rsu.nid
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
    $nid = $_POST['nid'];
    $rst = get_survey_rst_by_nid($nid);
    if ($rst) {
        echo drupal_json_output(array('status' => 'success','rst'=>$rst));
    } else {
        echo drupal_json_output(array('status' => 'failed','rst'=>$rst));
    }
}

function get_survey_rst_by_nid($nid){
    $dis_like_str  = '最不符合';
    $like_str= '最符合';
//    $nid = create_new_webform_node($survey_name);
    $query = "select wc.name,wsd.cid,wsd.data from webform_component wc
        inner join webform_submitted_data
        wsd on wc.nid = wsd.nid and wc.cid = wsd.cid
        where wc.nid = $nid
        and (wc.name = '$dis_like_str' or wc.name = '$like_str')
        group by wc.name,wsd.cid";

    $query_rst = db_query($query)->fetchAll();
    $like = prepare_rst_std('like');
    $dis_like = prepare_rst_std('dis_like');
    foreach($query_rst as $item){
        if($item->name == $dis_like_str){
            sum_rst_data($item,$dis_like);
        } else if($item->name == $like_str){
            sum_rst_data($item,$like);
        }
    }
   
    return generate_survey_rst($like,$dis_like);
}

function prepare_rst_std($type){
    $std = new stdClass();
    $std->type = $type;
    $std->d =0;
    $std->i =0;
    $std->s =0;
    $std->c =0;
    return $std;
}

function sum_rst_data($item,&$std){
   switch($item->data){
       case 'D': $std->d++; return $std;
       case 'I': $std->i++; return $std;
       case 'S': $std->s++; return $std;
       case 'C': $std->c++; return $std;
   }
   return $std;
}

function prepare_result($like,$dis_like,$type){
    switch($type){
       case 'd': return prepare_result_parm($like->d,$dis_like->d);
       case 'i': return prepare_result_parm($like->i,$dis_like->i);
       case 's': return prepare_result_parm($like->s,$dis_like->s);
       case 'c': return prepare_result_parm($like->c,$dis_like->c);
    }
}

function prepare_result_parm($like,$dis_like){
    $std = new stdClass();
    $std->in_working_me = $like;
    $std->innate = 6 - $dis_like;
    $std->other = $std->in_working_me + $std->innate;
    $std->stress = $std->in_working_me - $std->innate;
    return $std;
}

function generate_survey_rst($like,$dis_like){
    $d = prepare_result($like,$dis_like,'d');
    $i = prepare_result($like,$dis_like,'i');
    $s = prepare_result($like,$dis_like,'s');
    $c = prepare_result($like,$dis_like,'c');
    
    $rst = new stdClass();
    $rst->in_working_me = new stdClass();
    $rst->in_working_me->d = $d->in_working_me;
    $rst->in_working_me->i = $i->in_working_me;
    $rst->in_working_me->s = $s->in_working_me;
    $rst->in_working_me->c = $c->in_working_me;
    
    $rst->innate = new stdClass();
    $rst->innate->d = $d->innate;
    $rst->innate->i = $i->innate;
    $rst->innate->s = $s->innate;
    $rst->innate->c = $c->innate;
    
    $rst->other = new stdClass();
    $rst->other->d = $d->other;
    $rst->other->i = $i->other;
    $rst->other->s = $s->other;
    $rst->other->c = $c->other;
    
    $rst->stress = new stdClass();
    $rst->stress->d = $d->stress;
    $rst->stress->i = $i->stress;
    $rst->stress->s = $s->stress;
    $rst->stress->c = $c->stress;
    
    return $rst;
}