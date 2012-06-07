<?php
/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Note that modules and themes may implement their own search type and theme
 * function completely bypassing this template.
 *
 * Available variables:
 * - $result_count: Number of results.
 * - $spellcheck: Possible spelling suggestions from Search spellcheck module. 
 * - $search_results: All results rendered as list items in a single HTML string.
 * - $items: All results as it is rendered through search-result.tpl.php.
 * - $search_performance: The number of results and how long the query took.
 * - $sec: The number of seconds it took to run the query. 
 * - $pager: Row of control buttons for navigating between pages of results.
 * - $index:
 * - $keys: The keywords of the executed search.
 * - $page_machine_name: Machine name of the current Search API Page.
 * - $feed_icon: The feed for this search results.
 *
 * View Mode is set in the Search page settings. If you select
 * "Themed as search results", then the child template will be used for
 * theming the individual result. Any other view mode will bypass the
 * child template.
 *
 * @see template_preprocess_search_api_page_results()
 */
?>
<?php if (!empty($result_count)) : ?>
  <div class="search-api-page <?php print 'search-api-page-' . $page_machine_name . ' view-mode-' . $variables['view_mode'];?>">
    <?php if ($result_count > 0) : ?>
      <?php print render($search_performance); ?>
  	  <?php if ($feed_icon): ?>
  	    <div class="feed-icon">
  		  <?php print $feed_icon; ?>
  	    </div>
	    <?php endif; ?>
      <?php print render($spellcheck); ?>

      <?php print $pager; ?>
      <?php if($variables['view_mode'] == 'search_api_page_result') : // Uses child template. ?>
        <?php print render($search_results); ?>
      <?php else : // All other view modes (Teaser, Full content, RSS and so forth). ?>
        <div class="search-results">
          <?php print render(entity_view($index->item_type, $items, $variables['view_mode'])); ?>
        </div>
      <?php endif; ?>
      <?php print $pager; ?>
      <?php if ($variables['view_mode'] == 'rss') : // RSS only. ?>
        <div class="search-feed">
          <?php print render(entity_view($index->item_type, $items, $variables['view_mode'])); ?>
        </div>
      <?php endif; ?>      
    <?php endif; ?>
  </div>
<?php else : ?>
  <h2><?php print t('Your search yielded no results.');?></h2>
  <p><?php print t('Try to broaden your search using fewer words, or enter just the front part of a word.');?></p>
<?php endif; ?>
