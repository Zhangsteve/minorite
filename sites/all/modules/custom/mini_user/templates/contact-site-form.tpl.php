<?php print drupal_render($form['contact_information']); ?>
<fieldset class="contact-form form-item-has-shadow">
  <legend class="visuallyhidden">Mes coordonnées</legend>
  <div class="rw form-rw">
    <p class="w-1"><?php print drupal_render($form['name']); ?></p>
    <p class="w-2"><?php print drupal_render($form['firstname']); ?></p>
  </div>
  <div class="rw form-rw">
    <p class="w-1"><?php print drupal_render($form['mail']); ?></p>
  </div>
  <div class="rw form-rw">
    <p class="w-3"><?php print drupal_render($form['subject']); ?></p>
  </div>
  <div class="rw form-rw">
    <?php print drupal_render($form['message']); ?>
  </div>
  <div class="rw form-actions">
    <p class="w-1"><?php print drupal_render_children($form['actions']); ?></p>
  </div>
</fieldset>
<?php print drupal_render_children($form); ?>
