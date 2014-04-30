<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<ul class="search-results">
<?php foreach ($rows as $id => $row){
  echo $row;
} ?>
</ul>
