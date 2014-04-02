<?php

/**
 * Preprocess the wrapping HTML.
 *
 * @param array $variables
 *   Template variables.
 */
function minorite_preprocess_html(&$variables) {
  $variables['attributes_array']['id'] = 'site-wrapper';

  // Setup IE meta tag to force IE rendering mode.
  $meta_ie_render_engine = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' =>  'IE=edge,chrome=1',
    ),
    '#weight' => -1000,
  );
  drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');

  // Mobile viewport optimized: h5bp.com/viewport.
  $meta_viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' =>  'width=device-width, minimum-scale=1, maximum-scale=1',
    )
  );
  drupal_add_html_head($meta_viewport, 'meta_viewport');

  // Mobile IE allows us to activate ClearType technology for smoothing fonts
  // for easy reading.
  $meta_cleartype = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'cleartype',
      'content' =>  'on',
    )
  );
  drupal_add_html_head($meta_cleartype, 'meta_cleartype');

  drupal_add_library('system', 'ui.draggable', TRUE);

  // TODO : à faire ailleurs pour éviter que le test se fasse sur chaque page
  if (in_array('node-type-simplenews', $variables['classes_array'])) {
    $variables['theme_hook_suggestions'][] = 'html__node__newsletter';
  }

  // TODO : à faire ailleurs pour éviter que le test se fasse sur chaque page
  if (in_array('html__backup', $variables['theme_hook_suggestions'])) {
    $variables['content'] = minorite_backup_page();
  }

}

/**
 * Preprocess variables for the maintenance-page.tpl.php
 */
function minorite_preprocess_maintenance_page(&$variables) {
  $variables['content'] = minorite_backup_page();
  $variables['theme_hook_suggestions'][] = 'html__backup';
}

/**
 * Preprocess variables for region.tpl.php
 */
function minorite_preprocess_region(&$variables) {
  $function = "minorite_preprocess_region_$variables[region]";
  // Preprocess region on a location basis.
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Preprocess variables for region-header.tpl.php
 */
function minorite_preprocess_region_header(&$variables) {
  $variables['front_page']        = url();
  $variables['logo']              = theme_get_setting('logo');
  $variables['site_name']         = filter_xss_admin(variable_get('site_name', 'Drupal'));
  $variables['site_slogan']       = filter_xss_admin(variable_get('site_slogan', ''));
}

/**
 * Preprocess variables for block.tpl.php.
 *
 * @deprecated defined in minorite_system instead.
 */
function minorite_preprocess_block(&$variables) {
  // TODO: deprecate this.
  $variables['theme_hook_suggestions'][] = 'block__' . $variables['block']->region . '__' . strtr($variables['block']->delta, '-', '_');
}

/**
 * Preprocess variables for node.tpl.php
 *
 * @deprecated defined in minorite_system instead.
 */
function minorite_preprocess_node(&$variables) {
  $variables['submitted'] = format_date($variables['created'], 'short'); // TODO: remove this when not needed anymore.
  $variables['datetime'] = format_date($variables['created'], 'custom', 'Y-m-d');

  // TODO: either use only full, either only default. Default is used in panels by complex content type.
  if (($variables['view_mode'] == 'full' || $variables['view_mode'] == 'default') && $variables['type'] != 'panel') {
    $variables['content']['#theme_wrappers'] = array('section');
  }
}

/**
 * Preprocess variables for entities.
 */
function minorite_preprocess_entity(&$variables) {
  $entity = $variables['elements']['#entity'];
  $entity_type = $variables['elements']['#entity_type'];
  if ($body = field_get_items($entity_type, $entity, 'body')) {
    $display = array('label' => 'hidden', 'type' => 'text_summary');
    $variables['content']['summary'] = field_view_value($entity_type, $entity, 'body', $variables['body'][0], $display);
    $variables['content']['summary']['#markup'] = strip_tags($variables['content']['summary']['#markup']);
  }
}

/**
 * Preprocess variables for page.tpl.php
 */
function minorite_preprocess_page(&$variables) {

  // Add a new suggestion for the page theme with node type
  if (isset($variables['node'])) {
    if ($variables['node']->type == 'simplenews') {
      // Special case for simplenews because it is use also on the admin page
      $variables['theme_hook_suggestions'][] = 'page__node__newsletter';
    } else {
      $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
    }
  }
  if (isset($variables['node']) && arg(2) == 'edit') {
    $variables['theme_hook_suggestions'][] = 'page__node__edit__' . $variables['node']->type;
  }
}
