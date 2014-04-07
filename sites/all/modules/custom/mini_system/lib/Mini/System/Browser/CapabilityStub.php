<?php

/**
 * @file
 *
 * @author Sylvain Lecoy <sylvain.lecoy@gmail.com>
 */

namespace Disney\System\Browser;

/**
 * Always return TRUE for 'html5' browser capability.
 *
 * Useful in a test environment for example.
 */
class CapabilityStub implements CapabilityInterface {

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isMobile()
   */
  public function isMobile() {
    return FALSE;
  }

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isTablet()
   */
  public function isTablet() {
    return FALSE;
  }

  /**
   * (non-PHPdoc)
   * @see \Disney\System\Browser\CapabilityInterface::isHtml5()
   */
  public function isHtml5() {
    return TRUE;
  }

}
