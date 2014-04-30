<?php
/**
* @file
* This template handles the layout of the views exposed filter form.
*
* Variables available:
* - $widgets: An array of exposed form widgets. Each widget contains:
* - $widget->label: The visible label to print. May be optional.
* - $widget->operator: The operator for the widget. May be optional.
* - $widget->widget: The widget itself.
* - $sort_by: The select box to sort the view using an exposed form.
* - $sort_order: The select box with the ASC, DESC options to define order. May be optional.
* - $items_per_page: The select box with the available items per page. May be optional.
* - $offset: A textfield to define the offset of the view. May be optional.
* - $reset_button: A button to reset the exposed filter applied. May be optional.
* - $button: The submit button for the form.
*
* @ingroup views_templates
*/
?>
<?php if (!empty($q)): ?>
<?php
  // This ensures that, if clean URLs are off, the 'q' is added first so that
  // it shows up first in the URL.
  print $q;
?>
<?php endif; ?>

<section class="section search-results-form-wrapper view-hidden">
  <fieldset class="form-search-wrapper form-item-has-shadow">
    <legend><span><?php echo t('Advanced search'); ?></span></legend>

    <?php
    $i = $j = 1;
    foreach ($widgets as $id => $widget):
      if ($i%2) {
        if ($i != 1) {
          echo '</div>';
        }
        echo '<div class="rw form-rw">';
        $j = 0;
      }
      if ($i == 1) {
        $i++;
      }
      $i++;
      $j++;
    ?>
      <p id="<?php print $widget->id; ?>-wrapper" class="w-<?php echo $j; ?>">
      <?php if (!empty($widget->label)): ?>
        <label for="<?php print $widget->id; ?>">
        <?php print $widget->label; ?>
        </label>
      <?php endif; ?>
      <?php print $widget->widget; ?>
      </p>
    <?php endforeach; ?>

    <?php if (!empty($sort_by)): ?>
      <div class="views-exposed-widget views-widget-sort-by">
      <?php print $sort_by; ?>
      </div>
      <div class="views-exposed-widget views-widget-sort-order">
      <?php print $sort_order; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($items_per_page)): ?>
      <div class="views-exposed-widget views-widget-per-page">
      <?php print $items_per_page; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($offset)): ?>
      <div class="views-exposed-widget views-widget-offset">
      <?php print $offset; ?>
      </div>
    <?php endif; ?>

    <div class="rw form-actions view-hidden">
      <p class="w-1">
        <?php
        echo $button;
        if (!empty($reset_button)) {
          echo $reset_button;
        }
        ?>
      </p>
    </div>
  </fieldset>
</section>