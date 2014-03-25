<?php

/**
 * @file
 * Contains theming function for html elements.
 *
 * @author steve zhang <xianchi.zhang@gmail.com>
 */

/**
 * Returns HTML for a <section> item.
 */
function theme_section($variables){
  $element = $variables['element'];

  if (empty($element['#attributes'])) {
    $element['#attributes'] = array();
  }

  if (isset($element['#section_attributes'])) {
    $element['#attributes'] = $element['#section_attributes'];
  }

  if (!isset($element['#attributes']['id']) && !empty($element['#id'])) {
    // TODO: Check if its not provided by core default functions.
    $element['#attributes']['id'] = $element['#id'];
  }

  if (isset($element['#description'])) {
    // Prepend description to the output if defined.
    $element['#children'] = $element['#description'] . "\n" . $element['#children'];
  }

  if (isset($element['#title'])) {
    // Prepend title to the output if defined.
    $element['#children'] = '<h3>' . $element['#title'] . "</h3>\n" . $element['#children'];
  }

  return '<section' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</section>';
}

/**
 * Returns HTML for a metadata field wrapper.
 *
 * @ingroup themeable
 */
function theme_metadata_wrapper($variables) {
  return '<p' . drupal_attributes($variables['attributes']) . '>' . $variables['children'] . '</p>';
}

/**
 * Returns HTML for a metadata field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Renderable array of meta data, which include raw text.
 *   - attributes: Associative array of attributes to be placed in the b tag.
 *
 * @ingroup themeable
 */
function theme_metadata_formatter($variables) {
  return '<b' . drupal_attributes($variables['attributes']) . '>' . render($variables['item']) . '</b>';
}

/**
 * Returns HTML for a metadata time field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Renderable array of meta data, which include raw text.
 *   - attributes: Associative array of attributes to be placed in the time tag.
 *
 * @ingroup themeable
 */
function theme_metadata_formatter__time($variables) {
  $variables['attributes']['class'][] = 'time';
  return '<time' . drupal_attributes($variables['attributes']) . '>' . render($variables['item']) . '</time>';
}
