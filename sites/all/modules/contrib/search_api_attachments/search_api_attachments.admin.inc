<?php


/**
 * @file
 * Admin settings
 */

/**
 * Page callback to show the settings for the attachments.
 */
function search_api_attachments_settings_form($form, &$form_state) {
  $form['search_api_attachments_extract_using'] = array(
    '#type' => 'radios',
    '#title' => t('Extraction method'),
    '#options' => array(
      'tika' => t('Tika (local java application)'),
      'solr' => t('Solr (remote server)'),
    ),
    '#description' => t('Choose extraction method, remote or local (extraction will be faster if run locally using tika).'),
    '#default_value' => variable_get('search_api_attachments_extract_using', 'tika'),
  );
  $form['search_api_attachments_tika_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tika settings'),
    '#description' => t('Required if using the "Tika" extraction method (above).'),
    '#collapsible' => TRUE,
  );
  $form['search_api_attachments_tika_settings']['search_api_attachments_tika_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Tika directory path:'),
    '#default_value' => variable_get('search_api_attachments_tika_path', ''),
    '#description' => t('The full path to tika directory. All library jars must be in the same directory. E.g. /var/apache-tika-4.0/'),
  );
  $form['search_api_attachments_tika_settings']['search_api_attachments_tika_jar'] = array(
    '#type' => 'textfield',
    '#title' => t('Tika jar file:'),
    '#default_value' => variable_get('search_api_attachments_tika_jar', 'tika-app-1.4.jar'),
    '#description' => t('The name of the tika CLI application jar file, e.g. tika-app-1.4.jar.'),
  );
  return system_settings_form($form);
}

/**
 * Validation handler for the settings form.
 */
function search_api_attachments_settings_form_validate($form, &$form_state) {
  // We only need to validate the tika path if we're using local extraction.
  if ($form_state['values']['search_api_attachments_extract_using'] == 'tika') {
    if (empty($form_state['values']['search_api_attachments_tika_jar'])) {
      form_set_error('search_api_attachments_tika_jar', t('Tika jar is mandatory.'));
    }
    $path = realpath($form_state['values']['search_api_attachments_tika_path']);
    if (!file_exists($path . '/' . $form_state['values']['search_api_attachments_tika_jar'])) {
      form_set_error('search_api_attachments_tika_path', t('Tika jar file not found at this path.'));
    }
  }
}
