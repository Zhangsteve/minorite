<?php
/**
 * @file
 * mini_voyage.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function mini_voyage_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'voyage';
  $view->description = 'voyage liste ';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'voyage';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'views_content_cache';
  $handler->display->display_options['cache']['results_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_max_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['output_max_lifespan'] = '21600';
  $handler->display->display_options['cache']['keys'] = array(
    'comment' => array(
      'changed' => 0,
    ),
    'node' => array(
      'voyage' => 'voyage',
      'article' => 0,
      'page' => 0,
      'simplenews' => 0,
      'webform' => 0,
    ),
    'node_only' => array(
      'node_changed' => 0,
    ),
    'og' => array(
      'current' => 0,
      'user' => 0,
    ),
    'votingapi' => array(
      'tag:vote' => 0,
      'function:count' => 0,
      'function:average' => 0,
      'function:sum' => 0,
    ),
  );
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'OK';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'sort by';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: vignette */
  $handler->display->display_options['fields']['field_vignette']['id'] = 'field_vignette';
  $handler->display->display_options['fields']['field_vignette']['table'] = 'field_data_field_vignette';
  $handler->display->display_options['fields']['field_vignette']['field'] = 'field_vignette';
  $handler->display->display_options['fields']['field_vignette']['label'] = '';
  $handler->display->display_options['fields']['field_vignette']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_vignette']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_vignette']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '250',
  );
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_voyage_tags']['id'] = 'field_voyage_tags';
  $handler->display->display_options['fields']['field_voyage_tags']['table'] = 'field_data_field_voyage_tags';
  $handler->display->display_options['fields']['field_voyage_tags']['field'] = 'field_voyage_tags';
  $handler->display->display_options['fields']['field_voyage_tags']['label'] = '';
  $handler->display->display_options['fields']['field_voyage_tags']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['timezone'] = 'Europe/Paris';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Tags (field_voyage_tags) */
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['id'] = 'field_voyage_tags_tid';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['table'] = 'field_data_field_voyage_tags';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['field'] = 'field_voyage_tags_tid';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_voyage_tags_tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'voyage' => 'voyage',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'voyage/all';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'All';
  $handler->display->display_options['menu']['name'] = 'voyage';
  $translatables['voyage'] = array(
    t('Master'),
    t('more'),
    t('OK'),
    t('Reset'),
    t('sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('All'),
    t('Page'),
  );
  $export['voyage'] = $view;

  return $export;
}
