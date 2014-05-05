<?php
/**
 * @file
 * Template for a 3 column panel layout.
 *
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left_above']: Content in the left column in row 2.
 *   - $content['right_above']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['left_below']: Content in the left column in row 4.
 *   - $content['right_below']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 *   - $content['right']: Content in the right column.
 */
// Get the title of the node
// TODO : use a preprocess to send the title for every node
$node = menu_get_object();
?>
<div class="w-2">
  <article class="rtf-wrapper">
    <h1><?php echo $node->title; ?></h1>

    <?php print $content['top']; ?>

    <div class="rtf-fiftyfifty-wrapper">
      <div class="rw">
        <div class="w-1">
          <div class="inner-pad">
            <?php print $content['left_above']; ?>
          </div>
        </div>
        <div class="w-2">
          <div class="inner-pad">
            <?php print $content['right_above']; ?>
          </div>
        </div>
      </div>
    </div>

    <?php print $content['middle']; ?>

    <div class="rtf-fiftyfifty-wrapper">
      <div class="rw">
        <div class="w-1">
          <div class="inner-pad">
            <?php print $content['left_below']; ?>
          </div>
        </div>
        <div class="w-2">
          <div class="inner-pad">
            <?php print $content['right_below']; ?>
          </div>
        </div>
      </div>
    </div>

    <?php print $content['bottom']; ?>
  </article>
</div>

<aside class="w-3 aside">
  <?php
  $arg = arg(2);
  if (empty($arg)) {
    // Show roster block on every complex page
    $block_roster = disney_render_block('disney_roster', 'search');
    echo render($block_roster);
  }

  // Show right content
  print $content['right'];
  ?>
</aside>
