<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_suffix); ?>
  <h2><?php print t('In video'); ?></h2>
  <!-- -->
  <?php print $markup; ?>
 <!-- -->
  <?php if (!empty($title_video) || !empty($link)) { ?>
    <div class="box-footer">
        <?php if (!empty($title_video)) { ?>
          <h3><?php print render($title_video); ?></h3>
        <?php } ?>
        <?php if (!empty($link)) { ?>
          <p><?php print l(t('See the transcription'),$link, array('prefix'=>'http://','external'=>TRUE)); ?></p>
        <?php } ?>
    </div>
  <?php } ?>
</div>
