<?php

/**
 * @file
 *
 * @author Sylvain Lecoy <sylvain.lecoy@gmail.com>
 */

namespace Disney\System\Browser;

/**
 * Returns browser capabilities based on 'browscap' and 'mobile' module.
 */
class CapabilityBrowser implements CapabilityInterface {

  /**
   * Browser name.
   *
   * @var string
   */
  protected $browser;

  /**
   * Browser version.
   *
   * @var string
   */
  protected $version;

  /**
   * User agent.
   *
   * @var string
   */
  protected $agent;

  /**
   * Mobile information.
   *
   * @return array
   */
  protected $info;

  public function __construct() {
    // TODO: use a factory ?
    $browscap = browscap_get_browser();

    $this->browser = $browscap['browser'];
    $this->version = $browscap['version'];
    $this->agent = $browscap['useragent'];
    $this->info = mobile_switch_mobile_detect();
  }

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isMobile()
   */
  public function isMobile() {
    return $this->info['ismobiledevice'];
  }

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isTablet()
   */
  public function isTablet() {
    return $this->info['istablet'];
  }

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isHtml5()
   */
  public function isHtml5() {
    switch ($this->browser) {
      case 'Chrome':
        return TRUE;
      case 'IE':
        if (version_compare($this->version, '9.0', '>=')) {
          return TRUE;
        }
        else {
          // Test the IE8 or bellow compatibility mode which is seen as IE7.
          preg_match('#Trident/([0-9]*)#', $this->agent, $matches);
          if (isset($matches[1])) {
            return version_compare($matches[1], '5', '>=');
          }
        }
        return FALSE;

      case 'Firefox':
        return version_compare($this->version, '4.0', '>=');

      case 'Safari':
        return version_compare($this->version, '4.0', '>=');

      case 'Opera':
        return version_compare($this->version, '11.1', '>=');

      case 'iOS Safari':
        return version_compare($this->version, '4', '>=');

      case 'Android Browser':
        return version_compare($this->version, '2.2', '>=');

      case 'Blackberry Browser':
        return version_compare($this->version, '7.0', '>=');

      case 'Opera Mobile':
        return version_compare($this->version, '11.0', '>=');

      case 'Chrome for Android':
        return TRUE;

      case 'Firefox for Android':
        return version_compare($this->version, '23.0', '>=');

      case 'IE Mobile':
        return version_compare($this->version, '10.0', '>=');

    }

    return TRUE;
  }

}
