<?php

/**
 * @file
 *
 * @author Sylvain Lecoy <sylvain.lecoy@gmail.com>
 */

namespace Disney\System\Browser;

/**
 * Returns browser capabilities.
 */
interface CapabilityInterface {

  /**
   * Whether or not the device is mobile.
   */
  function isMobile();

  /**
   * Whether or not the device is tablet.
   */
  function isTablet();

  /**
   * Whether or not the device support HTML5.
   */
  function isHtml5();

}
