<?php
/**
 * @file
 * mini_voyage.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mini_voyage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function mini_voyage_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function mini_voyage_node_info() {
  $items = array(
    'voyage' => array(
      'name' => t('voyage'),
      'base' => 'node_content',
      'description' => t('note that we saw on our road.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
