<?php

/**
 * @file
 * Default theme implementation for profiles.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) profile type label.
 * - $url: The URL to view the current profile.
 * - $page: TRUE if this is the main view page $url points too.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-profile
 *   - profile-{TYPE}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */

?>
<?php if ($view_mode == 'teaser'): ?>
  <div class="teaser profile-teaser panel-display panel-2col clearfix" id="profile-teaser-<?php print $elements['#entity']->uid; ?>">
    <div class="image-column"> 
      <div class="views-field views-field-field-userimage">
        <div class="field-content">
          <?php print(render($content['field_userimage'])); ?>
        </div>
      </div>
    </div>
    <div class="text-column">
      <div class="views-field views-field-field-fullname">
        <div class="field-content">
          <h3><a href="<?php print $url; ?>"><?php print(render($content['field_fullname'])); ?></a></h3>
        </div>
      </div>  
      <div class="views-field views-field-field-userlocation">
        <?php print(render($content['field_userlocation'])); ?>
      </div>
    </div>
  </div>

<?php else: ?>
  <div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php if (!$page): ?>
      <h2<?php print $title_attributes; ?>>
          <a href="<?php print $url; ?>"><?php print $title; ?></a>
      </h2>
    <?php endif; ?>
  
    <div class="content"<?php print $content_attributes; ?>>
      <?php //print render($content); ?>
      <div id="profile-content-row">
        <div id="profile-picture-column">
          <?php print(render($content['field_userimage'])); ?>
          <?php if ($page): // insert affiliated groups block ?>
            <div class="field field-name-field-groups field-type-text-long field-label-above">
              <div class="field-label">Affiliate Groups:&nbsp;</div>
              <div class="field-items">
                <?php
                  $block = module_invoke('views', 'block_view', 'og_user_groups-block_1');
                  print render($block);
                ?>
              </div>
            </div>
          <?php endif; ?>
          <?php //print(render($content['field_location'])); ?>
          <?php print(render($content['field_country'])); ?>
          <?php print(render($content['field_office'])); ?>
          <?php print(render($content['field_hometown'])); ?>
          <?php print(render($content['field_languages'])); ?>
          <?php print(render($content['field_interests'])); ?>
          <?php print(render($content['field_experience'])); ?>
        </div>
        <div id="profile-center">
          <div id="profile-heading-row">
            <h2><?php print(render($content['field_fullname'])); ?></h2>
            <?php print(render($content['field_jobtitle'])); ?>
            <?php print(render($content['field_userlocation'])); ?>
          </div>
          <?php print(render($content['field_bio'])); ?>
          <?php if ($page): // insert latest photos block ?>
            <div class="field field-name-field-groups field-type-text-long field-label-above">
              <div class="field-label">Latest Photos</div>
              <div class="field-items">
                <?php
                  $cl_block = module_invoke('views', 'block_view', 'contributors_latest-block');
                  print render($cl_block);
                ?>
              </div>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </div>
<?php endif; ?>