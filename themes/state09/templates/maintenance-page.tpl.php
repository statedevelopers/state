<?php
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>">
	<head>
	  <?php print $head; ?>
	  <link rel="apple-touch-icon" href="/favicon_apl.png">
	  <title><?php print $head_title; ?></title>
	  <?php print $styles; ?>
	  <?php print $scripts; ?>
  	<!--[if lte IE 7]>
      <script type="text/javascript">
        alert('This website is not designed to support versions of InternetExplorer prior to version 8.');
      </script>
    <![endif]-->
	</head>
	<body class="<?php print $classes; ?>" <?php print $attributes;?>>
	  <?php print $page_top; ?>


	<div id="page-wrapper">
	<div id="banner4print"><img src="/<?php print $directory; ?>/images/2010/printbanner950_2010.jpg"><br></div><div id="ie6msg">You are using an older version of Internet Explorer.<br><br>
	In order to get the most out of our website, you can get a free update of Internet Explorer.<br>
	If you're using a work computer, please contact your IT administrator.<br><br>
	[CLOSE]
	</div>
	
	<div id="wrapper-plain"><div id="page">
	
	  <div id="masthead">
	  	<div class="section clearfix">
				<div id="logo-assets">
				    <?php if ($logo): ?>
						<a title="<?php print t('Home'); ?>" href="<?php print $front_page; ?>" rel="home" id="logo">
							<img class="png-fix" src="<?php print $logo; ?>" alt="U.S. Department of State - Great Seal" id="usdos-logo-seal">
						</a>
				    <?php endif; ?>
					<h1 id="usdos-logo-text">
					    <?php if ($site_name || $site_slogan): ?>
					      <div id="name-and-slogan">
					        <?php if ($site_name): ?>
					          <?php if ($title): ?>
					            <div id="site-name"><strong>
					              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
					            </strong></div>
					          <?php else: /* Use h1 when the content title is empty */ ?>
					            <h1 id="site-name">
					              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
					            </h1>
					          <?php endif; ?>
					        <?php endif; ?>
					
					        <?php if ($site_slogan): ?>
					          <div id="site-slogan"><?php print $site_slogan; ?></div>
					        <?php endif; ?>
					      </div><!-- /#name-and-slogan -->
					    <?php endif; ?>
					</h1>
				</div>
			
			    <?php print render($page['header_cap']); // Header Cap region ?>
			
			    <?php print render($page['header']); // Header region ?>
			
			
			 </div></div><!-- /.section, /#header -->
			
			  <div id="content-well"><div id="main" class="clearfix">
			    <div id="content" class="column">
			     <div class="section">
			      <?php if ($title): ?>
			        <h1 class="title" id="page-title"><?php print $title; ?></h1>
			      <?php endif; ?>
            <?php if ($messages): ?>
              <div id="console"><?php print $messages; ?></div>
            <?php endif; ?>
            <?php if ($help): ?>
              <div id="help">
                <?php print $help; ?>
              </div>
            <?php endif; ?>
            <?php print $content; ?>
			    </div></div><!-- /.section, /#content -->
						
			   </div>
			  </div><!-- /#main, /#main-wrapper -->
	
			</div>
		</div>
	</div><!-- /#page, /#wrapper-plain, /#page-wrapper -->
	


	<?php print render($page['bottom']); ?>


	  <?php print $page_bottom; ?>
	</body>
</html>
