<?php
/**
 * @file
 * mini_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function mini_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: cast-experience.
  $menus['voyage'] = array(
    'menu_name' => 'voyage',
    'title' => 'Voyage',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: footer.
  $menus['footer'] = array(
    'menu_name' => 'footer',
    'title' => 'Footer',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: guest-experience.
  $menus['life'] = array(
    'menu_name' => 'life',
    'title' => 'Life',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: headlines.
  $menus['headlines'] = array(
    'menu_name' => 'headlines',
    'title' => 'Headlines',
    'description' => 'The <em>Headlines</em> menu contains links intended for heading news.',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: links.
  $menus['game'] = array(
    'menu_name' => 'game',
    'title' => 'Game',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: my-company.
  $menus['my-company'] = array(
    'menu_name' => 'my-company',
    'title' => 'My company',
    'description' => 'The <em>My company</em> menu contains links related to company history, figures and internals.',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: my-team.
  $menus['my-team'] = array(
    'menu_name' => 'my-team',
    'title' => 'My team',
    'description' => 'The <em>My team</em> menu contains links for operating, support and human resources content.',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Voyage');
  t('Footer');
  t('Life');
  t('Headlines');
  t('My company');
  t('My team');
  t('The <em>Headlines</em> menu contains links intended for heading news.');
  t('The <em>My company</em> menu contains links related to company history, figures and internals.');
  t('The <em>My team</em> menu contains links for operating, support and human resources content.');
  t('The <em>My tools</em> menu contains links intended for internal work.');
  t('The <em>Other sites</em> menu contains Disney links to Other sites and is displayed in the footer.');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('User menu');


  return $menus;
}