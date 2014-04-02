<?php

/**
 * @file
 * Templates for form.
 */

/**
 * Returns HTML for a fieldset form element and its children.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #children, #collapsed, #collapsible,
 *     #description, #id, #title, #value.
 *
 * @ingroup themeable
 */
function minorite_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#description'])) {
    $output .= '<legend class="visuallyhidden">' . $element['#description'] . '</legend>';
  }

  if (!empty($element['#title'])) {
    $output .= '<h2>' . $element['#title'] . '</h2>';
  }

  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= "</fieldset>\n";
  return $output;
}

/**
 * Format a date popup element.
 */
function minorite_date_popup($variables) {
  return $variables['element']['#children'];
}

function minorite_date_popup_fromto_process_alter(&$element, &$form_state, $context) {
  $element['from']['#attributes']['class'][] = 'date-from';
  $element['from']['#attributes']['title'] = t('Date: from');
  $element['from']['#attributes']['placeholder'] = t('from mm/dd/yyyy');
  $element['upto']['#attributes']['class'][] = 'date-upto';
  $element['upto']['#attributes']['title'] = t('Date: to');
  $element['upto']['#attributes']['placeholder'] = t('to mm/dd/yyyy');
}

/**
 * Alter the process function for date_popup.
 */
function minorite_date_popup_process_alter(&$element, &$form_state, $context) {
  $element['date']['#attributes']['class'][] = 'has-datepicker';
  $element['date']['#title_display'] = 'none';
}

/**
 * Returns HTML for a radio button form element.
 *
 * Note: The input "name" attribute needs to be sanitized before output, which
 *       is currently done by passing all attributes to drupal_attributes().
 */
function minorite_radio($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'radio';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-custom-radio'));

  drupal_add_js("
  jQuery('.form-custom-radio').iCheck({
    checkboxClass: 'icheckbox_square-blue',
    radioClass: 'iradio_square-blue',
    increaseArea: '20%' // optional
  });", array('type' => 'inline', 'scope' => 'footer', 'group' => JS_THEME));

  return '<label for="' . $element['#id'] . '"><input' . drupal_attributes($element['#attributes']) . '><span>' . $element['#title'] . '</span></label>';
}

/**
 * Returns HTML for a set of radio button form elements.
 */
function minorite_radios($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  return '<span class="form-frame form-input-group">' . $element['#children'] . '</span>';
}

/**
 * Returns HTML to wrap child elements in a container.
 *
 * Used for grouped form items. Can also be used as a #theme_wrapper for any
 * renderable element, to surround it with a <p> and add attributes such as
 * classes.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #children, #grid.
 *
 * @ingroup themeable
 */
function minorite_container($variables) {
  $element = $variables['element'];

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Add the 'rw' and 'form-rw' class.
    $element['#attributes']['class'][] = 'rw';

    switch ($element['#type']) {
      case 'actions':
        break;

      default:
        $element['#attributes']['class'][] = 'form-rw';
    }
  }

  // Add the grid when specified.
  if (isset($element['#grid'])) {
    $element['#children'] = '<p class="' . $element['#grid'] . '">' . $element['#children'] . '</p>';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

/**
 * Returns HTML for a button.
 */
function minorite_button($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'title', 'value'));

  if ($element['#type'] == 'submit') {
    $element['#attributes']['type'] = 'submit';
  }

  // Adds CSS selector on icon button.
  if (isset($element['#icon'])) {
    $element['#value'] = '<i></i>' . $element['#value'];
    $element['#attributes']['class'][] = $element['#icon'];
  }

  return '<button' . drupal_attributes($element['#attributes']) . '>' . $element['#value'] . '</button>';
}

/**
 * Returns HTML for a phone element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function minorite_phone($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'tel';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-tel'));

  // Adds attributes required and readonly.
  if (!empty($element['#required'])) {
    $element['#attributes']['required'] = '';
  }
  if (!empty($element['#readonly'])) {
    $element['#attributes']['readonly'] = 'readonly';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Returns HTML for a textfield element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function minorite_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = isset($element['#attributes']['type']) ? $element['#attributes']['type'] : 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder'));
  _form_set_class($element, array('form-text'));

  // Adds attributes required and readonly.
  if (!empty($element['#required'])) {
    $element['#attributes']['required'] = '';
  }
  if (!empty($element['#readonly'])) {
    $element['#attributes']['readonly'] = 'readonly';
  }

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />' . $extra;
}

/**
 * Returns HTML for a textarea element.
 */
function minorite_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
  }

  // Add required attribute.
  if (!empty($element['#required'])) {
    $element['#attributes']['required'] = '';
  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

/**
 * Returns HTML for a form.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #action, #method, #attributes, #children
 */
function minorite_form($variables) {
  $element = $variables['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}

/**
 * Returns HTML for a form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name, #help.
 *
 * @ingroup themeable
 */
function minorite_form_element($variables) {
  $element = &$variables['element'];

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }

  if (!isset($element['#title_display'])) {
    $element['#title_display'] = 'invisible';
  }

  $output = '';
  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= theme('form_element_label', $variables);
      $output .= $element['#children'] . "\n";
      break;

    case 'grid':
      $output .= '<p class="w-1">' . theme('form_element_label', $variables) . "</p>\n";
      $output .= '<p class="w-2">' . $element['#children'] . "</p>\n";
      break;

    case 'none':
    case 'after': // TODO.
      $output .= $element['#children'] . "\n";
      break;
  }

  // If the element has help specified, append an icon.
  if (!empty($element['#description'])) {
    $help = theme('form_element_help', $variables);
    $grid = $element['#title_display'] == 'grid';
    $output .= ($grid ? '<p class="w-3">' . $help . '</p>' : $help) . "\n";
  }

  // If the element has grid specified, append a <p> tag.
  if (!empty($element['#grid'])) {
    $output = '<p class="' . $element['#grid'] . "\">\n" . $output . "</p>\n";
  }

  return $output;
}

/**
 * Returns HTML for a marker for required form elements.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *
 * @ingroup themeable
 */
function minorite_form_required_marker($variables) {
  return '<i><span class="visuallyhidden">' . t('This field is required.') . '</span></i>';
}

/**
 * Returns HTML for a form element label and required marker.
 *
 * Form element labels include the #title and a #required marker. The label is
 * associated with the element itself by the element #id.
 *
 * For elements that have an empty #title and are not required, this function
 * will output no label (''). For required elements that have an empty #title,
 * this will output the required marker alone within the label.
 * The label will use the #id to associate the marker with the field that is
 * required. That is especially important for screenreader users to know
 * which field is required.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #required, #title, #id, #value, #description.
 *
 * @ingroup themeable
 */
function minorite_form_element_label($variables) {
  $element = $variables['element'];

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '')) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  $attributes = array();
  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }
  // Add a class for required elements to facilitate cross-browser styling.
  if (!empty($element['#required'])) {
    $attributes['class'] = array('form-required');
  }

  return '<label' . drupal_attributes($attributes) . '>' . $title . $required . '</label>';
}

/**
 * Returns HTML for a button help.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *   Properties used: #description,
 *
 * @ingroup themeable
 */
function minorite_form_element_help($variables) {
  drupal_add_library('system', 'ui.tooltip', TRUE);

  return '<button class="ico-help" title="' . check_plain($variables['element']['#description']) . '"><i></i></button>';
}

/**
 * Returns HTML for an exposed filter form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: An associative array containing the structure of the form.
 *
 * @return
 *   A string containing an HTML-formatted form.
 *
 * @ingroup themeable
 */
function minorite_exposed_filters($variables) {
  return drupal_render_children($variables['form']);
}
