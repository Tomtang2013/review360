<?php 
drupal_add_js(drupal_get_path('module', 'review360_base') . '/js/member/school.js');

?>

<script type="text/javascript">
    jQuery(function () {
        var schoolName = "";
        var dp = '';
        function initProvince() {
            jQuery('#choose-a-province').html('');
            for (i = 0; i < schoolList.length; i++) {
                jQuery('#choose-a-province').append('<a class="province-item" province-id="' + schoolList[i].id + '">' + schoolList[i].name + '</a>');
            }
            jQuery('.province-item').bind('click', function () {
                var item = jQuery(this);
                var province = item.attr('province-id');
                var choosenItem = item.parent().find('.choosen');
                if (choosenItem)
                    jQuery(choosenItem).removeClass('choosen');
                item.addClass('choosen');
                initSchool(province);
            }
            );
        }
        Array.prototype.indexOf = function (vItem) {
            for (var i = 0, l = this.length; i < l; i++) {
                if (this[i] == vItem) {
                    return i;
                }
            }
            return -1;
        };
        function initSchool(provinceID) {
            jQuery('#choose-a-school').html('');
            var schools = schoolList[provinceID - 1].school;
            for (i = 0; i < schools.length; i++) {
                var limitSchool = window.parent.limitSchool;
                var sName = schools[i].name;
                if (limitSchool) {
                    if (limitSchool.indexOf(sName) == -1)
                        continue;
                }
                jQuery('#choose-a-school').append('<a class="school-item" school-id="' + schools[i].id + '">' + sName + '</a>');
            }
            jQuery('.school-item').bind('click', function () {
                var item = jQuery(this);
                var school = item.attr('school-id');
                schoolName = item.text();
                hide();
            }
            );
        }
        jQuery(function () {
            initProvince();

            jQuery('[province-id="1"]').addClass('choosen');
            var pid = 1;
            if (dp) {
                for (i = 0; i < schoolList.length; i++) {
                    if (dp.indexOf(schoolList[i].name) > -1 || schoolList[i].name.indexOf(dp) > -1) {
                        pid = schoolList[i].id;
                        jQuery('#choose-a-province').hide();
                        jQuery('#choose-a-school').height(250);
                        jQuery('#choose-box-title').html("<span>选择" + schoolList[i].name + "的高校</span>");
                        break;
                    }
                }
            }
            initSchool(pid);
        });
        function hide() {
            if (!schoolName) {
                alert("请选择学校！");
                return;
            }
             jQuery('#edit-infor-university').val(schoolName);
             jQuery('#schoolBox').modal('hide');
        }
    });

</script> 

<style>
    #choose-box-wrapper{
      //  width: 502px;
        padding:10px;
        padding-top:0;
    }
    #choose-box{
      //  max-width:500px;
        background-color:white;
    }
    #choose-box-title{
        padding: 4px 10px 5px;
        font-size: 16px;
        font-weight: 700;
        margin: 0;
    }
    #choose-box-title span{
        font-family: Tahoma, Verdana, STHeiTi, simsun, sans-serif;
    }

    #choose-a-province, #choose-a-school{
        margin:5px 8px 10px 8px;
        border: 1px solid #C3C3C3;
    }
    #choose-a-province a{
        display:inline-block;
        height: 18px;
        line-height: 18px;
        color:#005EAC;
        text-decoration: none;
        font-size: 9pt;
        font-family: Tahoma, Verdana, STHeiTi, simsun, sans-serif;
        margin:2px 5px;
        padding: 1px;
        text-align: center;
    }
    #choose-a-province a:hover{
        text-decoration:underline;
        cursor:pointer;
    }
    #choose-a-province .choosen{
        background-color: #005EAC;
        color:white;
    }

    #choose-a-school{
        overflow-x: hidden;
        overflow-y: auto;
        height: 200px;
    }
    #choose-a-school a{
        height: 20px;
        line-height: 20px;
        color:#005EAC;
        text-decoration: none;
        font-size: 9pt;
        font-family: Tahoma, Verdana, STHeiTi, simsun, sans-serif;
        float: left;
        width: 180px;
        margin: 4px 12px;
        padding-left:10px;
        //background:url(http://pic002.cnblogs.com/images/2012/70278/2012072500060712.gif) no-repeat 0 9px;
    }
    #choose-a-school a:hover{
        background-color:#005EAC;
        color:white;
        cursor:pointer;
    }
</style>
<div id="choose-box-wrapper" class="row">
    <div id="choose-box" class="col-md-12">
        <div id="choose-box-title">
            <span>选择学校</span>
        </div>
        <div id="choose-a-province">

        </div>
        <div id="choose-a-school">
          
        </div>
    </div>
</div>