<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['top']: Items for the tool bar at the top of the page.
 * - $page['header']: Items for the header region.
 * - $page['navigation']: Items for the navigation region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['left']: Items for the left sidebar.
 * - $page['content']: The main content of the current page.
 * - $page['right']: Items for the right sidebar.
 * - $page['footer']: Items for the footer region.
 * - $page['bottom]: Items for the tool bar at the bottom of the page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

  <noscript>
    <p><?php print t('JavaScript is disabled - This website requires JavaScript to be enabled.'); ?></p>
  </noscript>

  <div id="access-shortcuts-wrapper">
    <ul class="nav">
      <li><a href="#content"><?php print t('Skip to content'); ?></a></li>
      <li><a href="#nav-primary"><?php print t('Skip to main content'); ?></a></li>
      <li><a href="#form-search-global"><?php print t('Skip to search'); ?></a></li>
      <li><a href="#footer"><?php print t('Skip to footer'); ?></a></li>
    </ul>
  </div> <!-- /#access-shortcuts-wrapper -->

  <?php print render($page['top']); ?>

  <div id="main-layout" class="site-width-setter">

    <?php print render($page['header']); ?>

    <?php print render($page['navigation']); ?>

    <?php print $messages; ?>

    <div id="content" role="main">

      <?php if ($breadcrumb): ?>
        <nav class="crumbread-wrapper"><?php print $breadcrumb; ?></nav>
      <?php endif; ?>

      <div class="contentcol rw">

        <div class="w-1and2">
          <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>

          <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
          <?php print render($page['help']); ?>
          <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

          <?php print render($page['content']); ?>
          <?php print $feed_icons; ?>
        </div>

        <?php print render($page['right']); ?>
      </div> <!-- /.contentcol, /.col-retractable -->

    </div> <!-- /#content -->

  </div> <!-- /#main-layout -->

  <?php print render($page['footer']); ?>

  <?php print render($page['bottom']); ?>
