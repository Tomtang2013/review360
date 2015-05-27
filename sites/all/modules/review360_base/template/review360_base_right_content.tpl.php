<div class="region region-sidebar-first well" style='min-height:260px;'>
    <?php
    if ($is_html) {
        print $page_content;
    } else {
        echo drupal_render($page_content);
    }
    ?>
</div>