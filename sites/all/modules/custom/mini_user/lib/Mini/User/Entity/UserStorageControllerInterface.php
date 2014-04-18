<?php

/**
 * @file
 * Contains UserStorageControllerInterface.
 */

namespace Mini\User\Entity;

/**
 * Defines an interface for User controller classes.
 */
interface UserStorageControllerInterface extends \EntityAPIControllerInterface {

  /**
   * Loads one or more entities.
   *
   * @param string|array $eids
   *   An (array of) employee ID(s), or FALSE to load all entities.
   *
   * @return
   *   An array of entity objects indexed by their ids. When no results are
   *   found, an empty array is returned.
   */
  function loadByUserId($eids = array());

  /**
   * Deletes permanently an entity.
   *
   * @param $eids
   *   An array of employee IDs.
   */
  function deleteByUserId($eids = array());
}
