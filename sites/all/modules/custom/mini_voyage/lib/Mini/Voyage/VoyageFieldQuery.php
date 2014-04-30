<?php

/**
 * @file
 *
 * @author xianchi zhang <xianchi.Zhang@gmail.com>
 */

namespace Mini\Voyage;

use Mini\System\NodeFieldQuery;

/**
 * Retrieves voyages matching a given set of conditions.
 *
 * This class adds EntityFieldQuery capabilities to use node access checks and
 * not display private content which has been set as restricted.
 *
 * Default configuration:
 *  - 'status': 1
 *  - 'entity_type': node
 *  - 'bundle': voyage
 *
 * @see EntityFieldQuery
 */
class VoyageFieldQuery extends NodeFieldQuery {

  public function __construct() {
    // This query is interested in nodes only.
    $this->entityCondition('entity_type', 'node');
    // This query is interested in articles only.
    $this->entityCondition('bundle', 'voyage');
    // Default to published content.
    $this->propertyCondition('status', 1);
  }

}
