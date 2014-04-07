<?php

/**
 * @file
 *
 * @author Steve zhang <xianchi.zhang@gmail.com>
 */

namespace Minorite\System\Block;

/**
 * Prepares a block for caching based on granularity.
 *
 * This object is an adapter for drupal Block API, it is seen as an array
 * althought it is a plain object designed to ease the use of Cache API.
 */
class CacheBlock {

  protected $module;
  protected $delta;
  protected $expire;
  protected $granularity;

  /**
   * @param string $module
   *   Module implementing the block.
   * @param string $delta
   *   Delta of the block within the module.
   * @param string $expire
   *   Cache expire time, passed eventually to cache_set().
   */
  public function __construct($module, $delta, $expire = CACHE_TEMPORARY) {
    $this->module = $module;
    $this->delta = $delta;
    $this->expire = $expire;
    $tmp = $this->info();
    $this->granularity = $tmp['cache'];
  }

  /**
   * Expires data from the cache.
   */
  public function clear() {
    cache_clear_all($this->module . ':' . $this->delta, 'cache_block', TRUE);
  }

  /**
   * Prepares a block for caching based on granularity.
   *
   * @return
   *   A renderable array with the following keys and values:
   *   - #pre_render: function to render the block: MODULE_block_DELTA().
   *   - #cache: An associative array prepared for drupal_render_cache_set().
   *
   * @see settings.php where $external variable is set.
   */
  public function view() {
    global $external, $user;
    $cid_parts = array($this->module, $this->delta);

    if (!empty($this->granularity)) {
      // 'PER_MANAGEMENT' caches the block by management level. Further
      // granularity are added eventually such as theme key and language by the
      // drupal_render function.
      if ($this->granularity & DRUPAL_CACHE_PER_MANAGEMENT) {
        $cid_parts[] = 'm.' . $user->managementLevel;
      }
      // 'PER_NETWORK' caches the block by network access.
      if ($this->granularity & DRUPAL_CACHE_PER_NETWORK) {
        $cid_parts[] = 'n.' . $external;
      }
      // 'PER_USER' can conflict with super admin.
      if ($user->uid == 1 && !($this->granularity & DRUPAL_CACHE_PER_USER)) {
        $cid_parts[] = 'u.1';
      }
    }

    return array(
      '#pre_render' => array($this->module . '_block_' . strtr($this->delta, '_', '-')),
      '#cache' => array(
        'bin' => 'cache_block',
        'keys' => $cid_parts,
        'expire' => $this->expire,
        'granularity' => $this->granularity,
      ),
    );
  }

  public function info() {
    return array('info' => t('Block'), 'cache' => DRUPAL_NO_CACHE);
  }

}
