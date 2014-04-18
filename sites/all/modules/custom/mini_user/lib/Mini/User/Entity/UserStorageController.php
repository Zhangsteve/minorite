<?php

/**
 * @file
 * Contains UserStorageController.
 */

namespace Mini\User\Entity;

/**
 * Defines the User storage controller classes.
 */
class UserStorageController extends \DrupalDefaultEntityController implements UserStorageControllerInterface {

  /**
   * (non-PHPdoc)
   * @see UserController::attachLoad()
   */
  protected function attachLoad(&$queried_users, $revision_id = FALSE) {
    foreach ($queried_users as $key => $record) {
      $queried_users[$key]->data = unserialize($record->data);
      $queried_users[$key]->roles = array();
      if ($record->uid) {
        $queried_users[$record->uid]->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';
      }
      else {
        $queried_users[$record->uid]->roles[DRUPAL_ANONYMOUS_RID] = 'anonymous user';
      }
    }

    // Adds any additional roles from the database only if not connecting from
    // external network.
    /*if (!$GLOBALS['external']) {
      $result = db_query('SELECT r.rid, r.name, ur.uid FROM {role} r INNER JOIN {users_roles} ur ON ur.rid = r.rid WHERE ur.uid IN (:uids)', array(':uids' => array_keys($queried_users)));
      foreach ($result as $record) {
        $queried_users[$record->uid]->roles[$record->rid] = $record->name;
      }
    }*/

    // Calls the default attachLoad() method. This will add fields and call
    // hook_user_load().
    parent::attachLoad($queried_users, $revision_id);
  }

  /**
   * {@inheritdoc}
   */
  public function loadByUserId($eids = array()) {
    if ($eids) {
      $uids = db_select('users', 'u')
        ->fields('u', array('uid'))
        ->condition('name', $eids)
        ->execute()
        ->fetchCol();
    }

    return isset($uids) ? user_load_multiple($uids) : FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function deleteByUserId($eids = array()) {
    $uids = db_select('users', 'u')
      ->fields('u', array('uid'))
      ->condition('name', $eids)
      ->execute()
      ->fetchCol();

    if (empty($uids)) {
      // Throws an exception in case no user has been found.
      throw new \Exception('User(s) not found in storage.');
    }
    else {
      $this->delete($uids);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function save($account) {
    // Saves account with the help of entity module APIs.
    module_load_include('inc', 'entity', 'modules/callbacks');
    entity_metadata_user_save($account);
  }

  /**
   * {@inheritdoc}
   */
  public function create(array $values = array()) {
    module_load_include('inc', 'entity', 'modules/callbacks');
    return entity_metadata_create_object($values, 'user');
  }

  /**
   * {@inheritdoc}
   */
  public function delete($ids) {
    user_delete_multiple($ids);
  }

  /**
   * {@inheritdoc}
   */
  public function invoke($hook, $entity) {
    module_invoke_all($hook, $entity);
  }

  /**
   * {@inheritdoc}
   */
  public function export($entity, $prefix = '') {
    // Not used.
  }

  /**
   * {@inheritdoc}
   */
  public function import($export) {
    // Not used.
  }

  /**
   * {@inheritdoc}
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL) {
    // Not used.
  }

  /**
   * {@inheritdoc}
   */
  public function view($entities, $view_mode = 'full', $langcode = NULL, $page = NULL) {
    // Not used.
  }
}
