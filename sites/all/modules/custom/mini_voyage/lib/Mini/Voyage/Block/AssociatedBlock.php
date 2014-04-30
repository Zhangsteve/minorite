<?php

/**
 * @file
 *
 * @author xianchi zhang<xianchi.zhang@gmail.com>
 */

namespace Mini\Voyage\Block;

use Mini\System\Block\CacheBlock;
use Mini\Voyage\VoyageFieldQuery;

class AssociatedBlock extends CacheBlock {

  public function __construct() {
    parent::__construct('mini_voyage', 'associated', 24 * 60 * 60);
  }

  public function info() {
    return array('info' => t('Associated voyages'), 'cache' => DRUPAL_CACHE_PER_PAGE | DRUPAL_CACHE_PER_MANAGEMENT);
  }
}
