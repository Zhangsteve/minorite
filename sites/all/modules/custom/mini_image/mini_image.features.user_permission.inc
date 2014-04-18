<?php
/**
 * @file
 * mini_image.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mini_image_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
    'module' => 'image',
  );

  return $permissions;
}
