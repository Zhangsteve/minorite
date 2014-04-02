<?php

/**
 * @file
 * Default theme implementation to display a pager.
 *
 * @author Sylvain Lecoy <sylvain.lecoy@gmail.com>
 */

?>
<div class="w-1"><p class="inner-pad"><?php print render($form['limit']); ?></p></div>
<div class="w-2"><p class="inner-pad"><?php print render($form['pager']); ?></p></div>

<?php print drupal_render_children($form); ?>
