<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
$form_items_per_page = drupal_get_form('mini_search_items_per_page');
$items_per_page = render($form_items_per_page);
?>
<div class="<?php print $classes; ?>">
  <h1><?php echo t('Results of the search'); ?></h1>
  <!-- classified-ad-form wrapper -->

  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed){
    echo $exposed;
  } ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <section class="section search-results-list-wrapper">
    <nav class="rw pager-wrapper">
      <div class="w-1">
        <div class="inner-pad"><?php echo $items_per_page; ?></div>
      </div>
      <?php if ($pager): ?>
        <div class="w-2">
          <p class="inner-pad"><?php echo $pager; ?></p>
        </div>
      <?php endif; ?>
    </nav>
    <?php
    if ($rows) {
      echo $rows;
    } elseif ($empty) {
      echo $empty;
    } ?>
    <nav class="rw pager-wrapper">
      <div class="w-1">
        <div class="inner-pad"><?php echo $items_per_page; ?></div>
      </div>
      <?php if ($pager): ?>
        <div class="w-2">
          <p class="inner-pad"><?php echo $pager; ?></p>
        </div>
      <?php endif; ?>
    </nav>
  </section>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>