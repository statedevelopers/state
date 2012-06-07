	  <div class="content clearfix"<?php print $content_attributes; ?>>
		  <div class="node-image-wrapper">
		      <div class="node-image">
		    	<?php
					if (!empty($_GET['mode'])) {
		  				$node_url.='?mode='.$_GET['mode'];
		  				if (!empty($_GET['width'])) {
		  					$node_url.='&width='.$_GET['width'];
		  				}
	  				}
				    print render($content['field_image']);
			    ?>
		      </div>
		  </div>
		  <div class="node-header">
		  	<h2<?php print $title_attributes; ?>>
		    	<a href="<?php print $node_url; ?>"><?php print $title; ?></a>
		    </h2>
		    <?php
				print render($content['field_imagedate']);
				//print render($content['field_locationtag']);
				print render($content['field_country']);
				print render($content['field_internalrating']);
		    ?>
		  </div>
	  </div>