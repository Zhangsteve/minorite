<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

// For complex content type we have to change the url to go on the page
if (disney_complex_node_insert_update_check_type($row->_entity_properties['type'])) {
  // Request to find the complex page node of the section selected
  $menu = menu_link_load($row->_entity_properties['workbench_access_id']);
  if (!empty($menu)) {
    $title = field_get_items('node', $row->entity, 'title_field');
    print '<h2>' . l($title[0]['safe_value'], $menu['link_path'], array('html' => TRUE)) . '</h2>';
  } else {
    print $output;
  }
} else {
  print $output;
}
