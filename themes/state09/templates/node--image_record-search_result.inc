<?php 
// Used for Teasers & Search Results.

// Set node_url
if (!empty($_GET['mode'])) {
	$node_url.='?mode='.$_GET['mode'];
	if (!empty($_GET['width'])) {
		$node_url.='&width='.$_GET['width'];
	}
}

global $theme_path;
ctools_include('modal');
ctools_modal_add_js();
drupal_add_js(
  array(
    'entitypopup-modal-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 400,
        'height' => 500,
      ),
      'modalOptions' => array(
        'background' => '#000',
        'opacity' => .50, 
      ),
      'animation' => 'fadeIn',
      'animationSpeed' => 'medium',
      'loadingText' => '&nbsp;',
      'closeText' => '&nbsp;',
      'closeImage' => theme('image', 
        array(
          'path' => $theme_path . '/images/d7convert/CloseX.png', 
          'alt' => t('Close window'), 
          'title' => t('Close window'),
        )
      ),
      'throbber' => theme('image', 
        array(
          'path' => ctools_image_path('throbber.gif'), 
          'alt' => t('Loading...'), 
          'title' => t('Loading'))
      ),
    )
  ), 'setting');
?>
	  <div class="content clearfix image-teaser"<?php print $content_attributes; ?>>
		  <div class="node-image-wrapper ctools-use-modal entitypopup entitypopup-full" id="node-<?php print $nid;?>">
		      <div class="node-image">
		    	<?php
	  				$content['field_image'][0]['#path']['path'] = "entitypopup/node/$nid/full";
            /* DISPLAY TITLE AS TOOLTIP. $content['field_image'][0]['#path']['options']['attributes']['title'] = $title;*/
            $content['field_image'][0]['#path']['options']['attributes']['class'] = 'ctools-use-modal ctools-modal-entitypopup-modal-style';
				    print render($content['field_image']);
			    ?>
		      </div>
		  </div>
		  <div class="node-header">
		  	<h3>
				  <a class="ctools-use-modal ctools-modal-entitypopup-modal-style" href="/entitypopup/node/<?php print $nid; ?>/full"><?php print $title; ?></a>
		    </h3>
		    <?php
				//print render($content['field_locationtag']);
				print render($content['field_country']);
				print render($content['field_imagedate']);
		    ?>
		  </div>
	  </div>