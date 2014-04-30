<?php

include 'template.form.inc';
include 'template.pager.inc';
include 'template.preprocess.inc';
include 'template.theme.inc';

/**
 * Implements hook_theme().
 */
function minorite_theme($existing, $type, $theme, $path) {
  $templates = array();

  foreach (module_list() as $name) {
    // Filters modules starting by mini to only register thoses templates.
    if (substr($name, 0, 4) === 'mini') {
      $module_path = drupal_get_path('module', $name);
      $templates += drupal_find_theme_functions($existing, array($theme));
      $templates += drupal_find_theme_templates($existing, '.tpl.php', $module_path);
    }
  }

  return $templates + array(
    // User related templates.
    'user_profile' => array(
      'render element' => 'element',
      'template' => 'user-profile',
      'path' => drupal_get_path('module', 'mini_user') . '/templates',
    ),
    'user_profile_form' => array(
      'render element' => 'form',
      'template' => 'user-profile-form',
      'path' => drupal_get_path('module', 'mini_user') . '/templates',
    ),

    'form_element_help' => array(
      'variables' => array('element' => array('#description' => NULL)),
    ),
    'pager_form' => array(
      'render element' => 'form',
      'template' => 'pager-form',
      'path' => $path . '/templates/system',
    ),
    'aside' => array(
      'render element' => 'elements',
    ),
    'nav' => array(
      'render element' => 'elements',
    ),
    'header' => array(
      'render element' => 'elements',
    ),
    'footer' => array(
      'render element' => 'elements',
    ),
    'article' => array(
      'render element' => 'elements',
    ),
    'list' => array(
      'variables' => array('children' => NULL),
    ),
  );
}

/**
 * Gets a block suitable for drupal_render().
 *
 * @param $module
 *  Name of the module that implements the block to load.
 * @param $delta
 *  Unique ID of the block within the context of $module.
 *
 * @deprecated This function has been deprecated, for performance reasons. Uses
 * minorite_render_blocks() with an (s) to avoid multiple queries instead.
 *
 * @return
 *  A renderable array.
 */
function minorite_render_block($module, $delta) {
  $block = _block_render_blocks(array(block_load($module, $delta)));
  return _block_get_renderable_array($block);
}

/**
 * Gets a block suitable for drupal_render().
 *
 * @param $blocks
 *  An array of blocks to render.
 *
 * @return
 *  A renderable array.
 */
function minorite_render_blocks($blocks) {
  return _block_get_renderable_array(_block_render_blocks($blocks));
}

/**
 * Implements hook_css_alter().
 */
function minorite_css_alter(&$css) {
  // Removes some default css.
  unset($css['modules/system/system.theme.css']);
  unset($css['modules/system/system.menus.css']);
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    unset($css['misc/ui/jquery.ui.theme.css']);
  }
}

/**
 * Implements hook_js_alter().
 */
function minorite_js_alter(&$javascript) {
  $minorite = drupal_get_path('theme', 'minorite');

  // Change the group of draggable to be load after the jquery.ui.core.js and this correct the js error
  if (isset($javascript['sites/all/modules/contrib/jquery_update/replace/ui/ui/minified/jquery.ui.draggable.min.js'])) {
    $javascript['sites/all/modules/contrib/jquery_update/replace/ui/ui/minified/jquery.ui.draggable.min.js']['group'] = '0';
  }

  if (isset($javascript[$minorite . '/js/helper.js'])) {
    $javascript[$minorite . '/js/helper.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/script.js'])) {
    $javascript[$minorite . '/js/script.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/syze.min.js'])) {
    $javascript[$minorite . '/js/syze.min.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/jquery.bxslider.min.js'])) {
    $javascript[$minorite . '/js/jquery.bxslider.min.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/jquery.icheck.min.js'])) {
    $javascript[$minorite . '/js/jquery.icheck.min.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/jquery.fancybox-1.3.4.pack.js'])) {
    $javascript[$minorite . '/js/jquery.fancybox-1.3.4.pack.js']['scope'] = 'footer';
  }
  if (isset($javascript[$minorite . '/js/jquery.nicescroll.min.js'])) {
    $javascript[$minorite . '/js/jquery.nicescroll.min.js']['scope'] = 'footer';
  }
}
/**
 * Gets a block suitable for drupal_render().
 *
 * @param $module
 *  Name of the module that implements the block to load.
 * @param $delta
 *  Unique ID of the block within the context of $module.
 *
 * @deprecated This function has been deprecated, for performance reasons. Uses
 * disney_render_blocks() with an (s) to avoid multiple queries instead.
 *
 * @return
 *  A renderable array.
 */
function mini_render_block($module, $delta) {
  $block = _block_render_blocks(array(block_load($module, $delta)));
  return _block_get_renderable_array($block);
}

/**
 * Gets a block suitable for drupal_render().
 *
 * @param $blocks
 *  An array of blocks to render.
 *
 * @return
 *  A renderable array.
 */
function mini_render_blocks($blocks) {
  return _block_get_renderable_array(_block_render_blocks($blocks));
}