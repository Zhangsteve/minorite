<?php
/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
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
 *
 * @ingroup themeable
 */
?>
<?php if (count($block->carrousel)): ?>
<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_suffix); ?>
  <div class="content"<?php print $content_attributes; ?>>
    <div class="news-slider-wrapper title-strip-wrapper">
      <h2 class="title-strip"><?php echo t('Headline'); ?></h2>
      <ul class="slider-list">
        <?php foreach ($block->carrousel as $item): ?>
          <?php if ($item['image']): ?>
            <li>
              <div class='news-slider-img'>
                <?php if ($item['link']): ?><a href="<?php print $item['link']; ?>"><?php endif; ?>
                  <?php print $item['image']; ?>
                <?php if ($item['link']): ?></a><?php endif; ?>
              </div>
              <div class="news-slider-text">
                <?php if ($item['title']): ?>
                  <h3 class='title'>
                    <?php if ($item['link']): ?><a href="<?php print $item['link']; ?>"><?php endif; ?>
                      <?php print $item['title']; ?>
                    <?php if ($item['link']): ?></a><?php endif; ?>
                  </h3>
                <?php endif; ?>
                <?php if ($item['description']): ?>
                  <p class='chapo'>
                    <?php if ($item['link']): ?><a href="<?php print $item['link']; ?>"><?php endif; ?>
                      <?php print $item['description']; ?><?php /*if ($item['link']): ?><span class="readmore"><?php print t('Read more'); ?></span><?php endif; */ ?>
                    <?php if ($item['link']): ?></a><?php endif; ?>
                  </p>
                <?php endif; ?>
              </div>
            </li>
          <?php endif; ?>
        <?php endforeach; ?>
      </ul>
      <?php if (count($block->carrousel) > 1):?>
        <div class="slider-controller">
          <div class="slider-pager"></div>
          <span class="slider-button-prev"></span>
          <span class="slider-button-next"></span>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
<?php endif; ?>
