<?php
/**
 * @file
 * Default theme implementation for displaying a single search result.
 *
 * This template renders a single search result and is collected into
 * search_api_page-results.tpl.php. This and the parent template are
 * dependent to one another sharing the markup for definition lists.
 *
 * View Mode is set in the Search page settings. If you select
 * "Themed as search results", then the child template will be used for
 * theming the individual result. Any other view mode will bypass the
 * child template.
 *
 * Available variables:
 * - $url: URL of the result.
 * - $title: Title of the result.
 * - $snippet: A small preview of the result. Does not apply to user searches.
 * - $info: String of all the meta information ready for print. Does not apply
 *   to user searches.
 * - $info_split: Contains same data as $info, split into a keyed array.
 * - $list_classes: CSS classes for this list element.
 *
 * Default keys within $info_split:
 * - $info_split['user']: Author of the node linked to users profile. Depends
 *   on permission.
 * - $info_split['date']: Last update of the node. Short formatted.
 *
 * Since $info_split is keyed, a direct print of the item is possible.
 * This array does not apply to user searches so it is recommended to check
 * for its existence before printing. The default keys of 'user' and
 * 'date' always exist for node searches.
 *
 * To check for all available data within $info_split, use the code below.
 * @code
 *   <?php print '<pre>'. check_plain(print_r($info_split, 1)) .'</pre>'; ?>
 * @endcode
 *
 * @see template_preprocess()
 * @see template_preprocess_search_result()
 * @see template_process()
 */
?>
<li<?php print $list_classes; ?>>
  <h3 class="title">
    <?php print $url ? l($title, $url['path'], $url['options']) : check_plain($title); ?>
  </h3>
  <div class="search-snippet-info">
    <?php if ($snippet) : ?>
      <p class="search-snippet"><?php print $snippet; ?></p>
    <?php endif; ?>
    <?php if ($info) : ?>
      <p class="search-info"><?php print $info; ?></p>
    <?php endif; ?>
  </div>
</li>
