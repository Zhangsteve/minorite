<?php global $language; ?>

<div class="w-2" role="search">
<form name="input" action="/<?php print $language->language; ?>/search-api-page-result" method="get">
<fieldset class="form-search-global-wrapper">
<legend class="visuallyhidden"><?php print t('Search in website'); ?></legend>
      <p>
        <label for="form-search-global" class="visuallyhidden"><?php print t('Search in website'); ?></label>
        <input type="text" placeholder="<?php print t('Search in website'); ?>" name="search_api_views_fulltext" id="search_api_views_fulltext" value="<?php print (isset($_GET['search_api_views_fulltext']) ? $_GET['search_api_views_fulltext'] : ''); ?>">
        <button type="submit" title="<?php print t('Search'); ?>" class="ico-search"><i><?php print t('Ok'); ?></i></button>
      </p>
      <p><a href="/<?php print $language->language; ?>/search-api-page-result"><?php print t('Advanced Search'); ?></a></p>
    </fieldset>
  </form>
</div>
