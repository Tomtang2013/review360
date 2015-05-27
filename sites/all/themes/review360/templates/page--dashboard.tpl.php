
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
    <div class="container">
        <div class="navbar-header">
            <?php if ($logo): ?>
                <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                </a>
            <?php endif; ?>

            <?php if (!empty($site_name)): ?>
                <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
            <?php endif; ?>

            <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
        </div>
    </div>
</header>

<div class="main-container container">

    <header role="banner" id="page-header">
        <?php print render($page['header']); ?>
    </header> <!-- /#page-header -->

    <div class="row">
        <section class="col-md-2" role="complementary">
             <?php global $user;  if($user->uid == 1):?>
            <div class="region region-sidebar-first well">
                <?php
                     print rend_block_by_name('review360_base','left_menu');
                ?>
            </div>
            <?php endif; ?>
        </section>  
        <section class="col-md-10" >
             <?php global $user;
                if($user->uid == 0):
              ?>
            <div class="region region-sidebar-first well">
                <?php
                    print rend_block_by_name('user','login');
                ?>
            </div>
            <?php else:?>
                <?php print render($page['content']); ?>
            <?php endif; ?>
        </section>


    </div>
</div>
<footer class="footer container">
    <?php print render($page['footer']); ?>
</footer>
