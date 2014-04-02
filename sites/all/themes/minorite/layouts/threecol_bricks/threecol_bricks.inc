<?php

/**
 * @file
 * Implementation for the two column bricked layout
 */

// Plugin definition
$plugin = array(
  'title' => t('Three column bricks'),
  'category' => t('Columns: 2'),
  'icon' => 'threecol_bricks.png',
  'theme' => 'panels_threecol_bricks',
  'css' => 'threecol_bricks.css',
  'regions' => array(
    'top' => t('Top'),
    'left_above' => t('Left above'),
    'right_above' => t('Right above'),
    'middle' => t('Middle'),
    'left_below' => t('Left below'),
    'right_below' => t('Right below'),
    'bottom' => t('Bottom'),
    'right' => t('Right'),
  ),
);
