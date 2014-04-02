<?php

/**
 * @file
 * Default theme implementation to display a menu header.
 *
 * Available variables:
 * - title: The title of the menu.
 * - nodes: The node to be displayed.
 * - children: An HTML string containing the tree's items.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 */
?>
<li>
  <?php print $title; ?>
  <div class="rw meganav-wrapper">
    <div class="w-1">
      <p><strong><?php print t('Sections'); ?></strong></p>
      <?php print $children; ?>
    </div>
    <div class="w-2">
      <p><strong><?php print t('Highlighted'); ?></strong></p>
      <ul class="nav">
        <?php print render($nodes); ?>
      </ul>
    </div>
  </div>
</li>
