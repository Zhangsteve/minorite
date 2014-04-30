<?php

/**
 * @file
 *
 * @author xianchi  zhang <xianchi.zhang@gmail.com>
 */

namespace Mini\Voyage\Block;

use Mini\System\Block\CacheBlock;

class HomeBlock extends CacheBlock {

  public function __construct() {
    parent::__construct('mini_voyage', 'home', 1);
  }

  public function info() {
    return array('info' => t('Home voyages'), 'cache' => DRUPAL_CACHE_PER_MANAGEMENT);
  }
}
