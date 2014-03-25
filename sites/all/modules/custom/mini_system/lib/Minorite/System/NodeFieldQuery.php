<?php

/**
 * @file
 *
 * @author Sylvain Lecoy <sylvain.lecoy@gmail.com>
 */

namespace Minorite\System;

/**
 * Retrieves entities matching a given set of conditions.
 *
 * This class adds EntityFieldQuery capabilities to use node access checks and
 * not display private content which has been set as restricted.
 *
 * Default configuration:
 *  - 'status': 1
 *  - 'entity_type': node
 *
 * @see EntityFieldQuery
 */
class NodeFieldQuery extends \EntityFieldQuery {

  public function __construct() {
    // This query is interested in nodes only.
    $this->entityCondition('entity_type', 'node');
    // Default to published content.
    $this->propertyCondition('status', 1);
  }

  /**
   * Restricts the query to the desired section only.
   *
   * @param string|array $id
   *   (Optional) ID(s) of section(s), corresponding to 'access_id' column in
   *   the workbench access table.
   *   Depending on the value given:
   *    - If id is numeric or a string, restrict to section only.
   *    - If id is an array, restrict to group of sections.
   *    - If is is null, use the current section (works for menu only).
   *
   * @return NodeFieldQuery
   */
  public function addSection($id = NULL) {
    // Adds workbench access check tag.
    $this->addTag('workbench');

    if (empty($id)) {
      $item = menu_get_item();
      // If we are calling this function for a menu item that corresponds to a
      // local task (for example, admin/tasks), then we want to retrieve the
      // parent item's child links, not this item's (since this item won't have
      // any).
      if ($item['tab_root'] != $item['path']) {
        $item = menu_get_item($item['tab_root_href']);
      }
      if (!isset($item['mlid'])) {
        $item['mlid'] = mlid($item['path']);
      }

      $id = $item['mlid'];
    }

    $this->addMetaData('workbench_access_id', $id);
    // Removes the type meta data to avoid conflicts.
    unset($this->metaData['workbench_access_type_id']);
    return $this;
  }

  /**
   * Restricts the query to multiple sections.
   *
   * @param string $type
   *   The type of section, corresponding to 'access_type_id' column in the
   *   workbench access table.
   *
   * @return NodeFieldQuery
   */
  public function addSectionType($type) {
    // Adds workbench access check tag.
    $this->addTag('workbench');
    $this->addMetaData('workbench_access_type_id', $type);
    // Removes the id meta data to avoid conflicts.
    unset($this->metaData['workbench_access_id']);
    return $this;
  }

  /**
   * (non-PHPdoc)
   * @see EntityFieldQuery::execute()
   */
  public function execute() {
    if (empty($this->fields)) {
      // The SQL driver adds the 'entity_field_access' already if there is
      // fields, only adds 'node_access' when there is no fields.
      // @see https://drupal.org/node/1440976.
      $this->addTag('node_access');
    }
    return parent::execute();
  }
}
