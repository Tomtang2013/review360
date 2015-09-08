
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
    <div class="container">
        <div class="navbar-header">
            <?php if ($logo): ?>
                <a class="logo navbar-btn pull-left" href="#" title="<?php print t('Home'); ?>">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                </a>
            <?php endif; ?>

            <?php if (!empty($site_name)): ?>
                <a class="name navbar-brand" href="#" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
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

    <div class="row">
        <section class="col-md-12" >
             <?php if ($messages): ?>
                <div id="messages"><div class="section clearfix">
                  <?php print $messages; ?>
                </div></div> <!-- /.section, /#messages -->
              <?php endif; ?>
             <?php print render($page['content']); ?>
        </section>
    </div>
</div>
<footer class="footer container">
    <?php print render($page['footer']); ?>
</footer>
