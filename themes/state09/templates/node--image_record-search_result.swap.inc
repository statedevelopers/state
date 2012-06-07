	  <div class="content clearfix"<?php print $content_attributes; ?>>
		  <div class="node-image-wrapper">
		      <div class="node-image">
				<div class="node-image">
			    	<div class="field field-name-field-image field-type-image field-label-hidden">
			    		<div class="field-items">
			    			<div class="field-item even">
			    				<?php 			    				
			    					if (!empty($_GET['mode'])) {
						  				$node_url.='?mode='.$_GET['mode'];
						  				if (!empty($_GET['width'])) {
						  					$node_url.='&width='.$_GET['width'];
						  				}
					  				}
					  				$filename = $node->field_image["und"][0]['filename'];
					  				$filepath = "/sites/default/files/styles/thumbnail_squeezed/public/contributed_images/" . $filename;
					  			?>
			    				<a href="<?php print $node_url; ?>">
			    					<img typeof="foaf:Image" src="<?php print $filepath; ?>" alt="">
			    				</a>
			    			</div>
			    		</div>
			    	</div>
			    </div>					
		    	<?php
//print_r ($node->field_image['und'][0]['filename']); exit;
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
		    ?>
		  </div>
	  </div>