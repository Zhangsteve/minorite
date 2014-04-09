<?php

/**
 * @file
 * User page callback file for the mini_user module.
 */

/**
 * Form builder; mini User administration page.
 * Base on the User administration page in user.admin.inc
 *
 * @ingroup forms
 * @see mini_user_admin_account_validate()
 * @see mini_user_admin_account_submit()
 */
function mini_user_admin_account() {
  $header = array(
    'username' => array('data' => t('Nick name'), 'field' => 'u.name'),
    'firstName' => array('data' => t('First Name'), 'field' => 'u.firstName'),
    'lastName' => array('data' => t('Last Name'), 'field' => 'u.lastName'),
    'phone' => array('data' => t('Phone'), 'field' => 'u.phone'),
    'address' => array('data' => t('Address'), 'field' => 'u.address'),
    'status' => array('data' => t('Status'), 'field' => 'u.status'),
    'roles' => array('data' => t('Roles')),
    'member_for' => array('data' => t('Member for'), 'field' => 'u.created', 'sort' => 'desc'),
    'access' => array('data' => t('Last access'), 'field' => 'u.access'),
    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('users', 'u');
  $query->condition('u.uid', 0, '<>');
  user_build_filter_query($query);

  $count_query = clone $query;
  $count_query->addExpression('COUNT(u.uid)');

  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query
    ->fields('u', array('uid', 'name', 'firstName', 'lastName', 'phone', 'address', 'status', 'created', 'access'))
    ->limit(50)
    ->orderByHeader($header)
    ->setCountQuery($count_query);
  $result = $query->execute();

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
  );
  $options = array();
  foreach (module_invoke_all('user_operations') as $operation => $array) {
    $options[$operation] = $array['label'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'unblock',
  );
  $options = array();
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  $destination = drupal_get_destination();

  $status = array(t('blocked'), t('active'));
  $roles = array_map('check_plain', user_roles(TRUE));
  $accounts = array();
  foreach ($result as $account) {
    $users_roles = array();
    $roles_result = db_query('SELECT rid FROM {users_roles} WHERE uid = :uid', array(':uid' => $account->uid));
    foreach ($roles_result as $user_role) {
      $users_roles[] = $roles[$user_role->rid];
    }
    asort($users_roles);

    $options[$account->uid] = array(
      'username' => theme('username', array('account' => $account)),
      'firstName' => $account->firstName,
      'lastName' => $account->lastName,
      'phone' => $account->phone,
      'address' => $account->address,
      'status' =>  $status[$account->status],
      'roles' => theme('item_list', array('items' => $users_roles)),
      'member_for' => format_interval(REQUEST_TIME - $account->created),
      'access' =>  $account->access ? t('@time ago', array('@time' => format_interval(REQUEST_TIME - $account->access))) : t('never'),
      'operations' => array('data' => array('#type' => 'link', '#title' => t('edit'), '#href' => "user/$account->uid/edit", '#options' => array('query' => $destination))),
    );
  }

  $form['accounts'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No people available.'),
  );
  $form['pager'] = array('#markup' => theme('pager'));

  return $form;
}

/**
 * Submit the mini user administration update form.
 * By calling the user administration update form.
 */
function mini_user_admin_account_submit($form, &$form_state) {
  user_admin_account_submit($form, $form_state);
}

function mini_user_admin_account_validate($form, &$form_state) {
  user_admin_account_validate($form, $form_state);
}

/**
 * Form callback; Return the legal terms form.
 */
function mini_user_legal_terms_form($form, &$form_state) {
  global $user;

  drupal_add_js(drupal_get_path('theme', 'mini') . '/misc/jquery.nicescroll.min.js');

  $form['form_search'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#attributes' => array(
      'class' => array('form-terms-wrapper', 'form-item-has-shadow'),
    ),
  );

  $terms_block = mini_render_block('mini_user', 'legal_terms');
  $form['form_search']['terms_content'] = array(
    '#markup' => render($terms_block),
  );

  $form['form_search']['terms_acceptance'] = array(
    '#type' => 'radios',
    '#title' => '',
    '#default_value' => !mini_user_legal_terms_access(),
    '#options' => array(0 => t('I refuse'), 1 => t('I agree')),
    '#prefix' => '<div class="rw form-rw"><p class="w-1">',
    '#suffix' => '</span></p></div>',
    '#disabled' => !mini_user_legal_terms_access(),
    '#access' => ($user->uid) ? TRUE : FALSE,
  );

  $form['form_search']['submit'] = array(
    '#type' => 'submit',
    '#value' => '<i></i>' . t('Validate'),
    '#prefix' => '<div class="rw form-button-rw"><p class="w-1">',
    '#suffix' => '</div></p>',
    '#attributes' => array(
      'value' => array(t('Validate')),
      'name' => 'submit_button',
      'class' => array('button-ico-go'),
    ),
    '#access' => mini_user_legal_terms_access(),
  );

  // Redirect the user to its destination after terms acceptance.
  $form['#redirect'] = drupal_get_destination();

  return $form;
}

/**
 * Save the legal terms acceptance by the user.
 *
 * @param array $form
 *   Array, containing the form structure.
 * @param array &$form_state
 *   $form_state['values'] stores the submitted values from the form.
 */
function mini_user_legal_terms_form_submit($form, &$form_state) {
  if($form_state['values']['terms_acceptance'] == 1) {
    global $user;
    $user->termsAcceptance = 1;
    mini_user_storage()->save($user);
  } else {
    form_set_error('terms_acceptance', t('Error : you have to accept the legal terms if you want to access to the intranet.'));
  }
}
