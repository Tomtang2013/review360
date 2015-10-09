<?php


function review360_system_powered_by(){
    
    return '<div style="text-align:center;width:100%;"><span>' . t('<a href="@poweredby">关于我们</a>', array('@poweredby' => '')) . '</span>'
        . " | ". '<span>' . t('<a href="@poweredby">联系方式</a>', array('@poweredby' => '')) . '</span></div>';
}
