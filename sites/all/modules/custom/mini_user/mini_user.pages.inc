<?php

/**
 * @file
 * user page callback file for the mini_user module.
 *
 * @author xian chi zhang <xianchi.zhang@gmail.com>
 */

define('MINI_USER_REGISTER_FORM', 1);

/**
 * Employee preferred contact method form, either phone or email.
 */
define('MINI_USER_REGISTER_CONTACT_FORM', 2);

/**
 * Employee confirmation screen.
 */
define('MINI_USER_REGISTER_CONFIRM_FORM', 3);

/**
 * Employee cancel screen in the case no contact method is available.
 */
define('MINI_USER_REGISTER_CANCEL_FORM', 4);

/**
 * Form builder; Primary form builder for the Employee registration wizard.
 */
function mini_user_register_wizard($form, &$form_state) {

  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;

    // This array contains the function to be called at each step to get the
    // relevant form elements. It also store state information for each step.
    $form_state['step_info'] = array(
      MINI_USER_REGISTER_FORM => array(
        // Displays the first registration screen where user enter its employee
        // ID, last and first name, and birth date.
        'form' => 'mini_user_register_form'
      ),
      MINI_USER_REGISTER_CONTACT_FORM => array(
        // When the user have both 'mail' and 'phone' registered, displays a
        // form that allow the preferred contact method.
        'form' => 'mini_user_register_contact_form',
      ),
      MINI_USER_REGISTER_CONFIRM_FORM => array(
        // Displays the confirmation screen where user see indications about
        // the selected contact method and the remaining steps to access the site.
        'form' => 'mini_user_register_confirm_form',
      ),
      MINI_USER_REGISTER_CANCEL_FORM => array(
        // When the user does not have any 'mail' or 'phone' registered,
        // displays a form that invite him to contact the HR service.
        'form' => 'mini_user_register_cancel_form',
      )
    );
  }
  $step = $form_state['step'];

  // Call the function named in $form_state['step_info'] to get the form
  // elements to display for this step. Also set the #step and #title info.
  $form = $form_state['step_info'][$step]['form']($form, $form_state);
  $form['user']['#type'] = 'fieldset';
  // Custom the title base on the url to bypass the problem on the creation of this page
  if (current_path() == 'user/password') {
    $form['user']['#title'] = t('Password forgotten');
  } else {
    $form['user']['#title'] = t('Become a member');
  }
  $form['user']['#description'] = $form['user']['#title'];
  $form['user']['#attributes'] = array('class' => array('form-item-has-shadow'));
  $form['#step'] = $form_state['step'];

  // Shows the 'validate' button only for steps 1 and 2, others are pages only.
  if ($step < MINI_USER_REGISTER_CONFIRM_FORM) {
    $form['user']['identifier']['actions'] = array('#type' => 'actions', '#weight' => 1);
    $form['user']['identifier']['actions']['submit'] = array(
      '#title' => t('Join Us'),
      '#type' => 'submit',
      '#value' => t('Validate'),
    );
  }

  // Shows the 'cancel' button only if this is the first step. The #submit is
  // set to a special submit handler, and the use of #limit_validation_errors
  // allows skipping all complaints about validation when using the reset
  // button. The values entered will be discarded, but not validated.
  if ($step == MINI_USER_REGISTER_FORM) {
    $form['user']['identifier']['actions']['cancel'] = array(
      '#title' => t('Reset'),
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#submit' => array('mini_user_register_wizard_reset'),
      '#limit_validation_errors' => array(),
    );
  }

  // Includes validation function for the different steps.
  if (function_exists($form_state['step_info'][$step]['form'] . '_validate')) {
    $form['#validate'] = array($form_state['step_info'][$step]['form'] . '_validate');
  }

  $form['user']['identifier']['legal'] = array(
    '#markup' => '<p><strong>' . t('Privacy policy') . '</strong></p>' .
                 '<p>' . t('This communication is strictly confidential, dedicated to the exclusive use of persons expressly authorized by Minorite group ® Paris. It is imperative not to disclose, copy or distribute the content presented without having been duly authorized by Minorite group ® Paris.') . '</p>' ,
    '#theme_wrappers' => array('section'),
    '#weight' => 2,
  );

  return $form;
}

/**
 * Form builder; Submit handler for 'reset' button.
 */
function mini_user_register_wizard_reset($form, &$form_state) {
  // Rebuild the form by submitting it.
}

/**
 * Form builder; Submits the employee registration form.
 */
function mini_user_register_wizard_submit($form, &$form_state) {
  $mini_account =  $form_state['mini_account'];
  // If no contact method is provided, display the cancel page.
  if ($form_state['step'] == 1) {
    $form_state['step']++;
    $form_state['rebuild'] = TRUE;
  }
  // If both contact method are provided, display the choose form.
  // Excepted when coming from step 2 where both contact methods are still
  // available, skip this directly to last screen.
  else if ($form_state['step'] == 2 && empty($form_state['values']['mail'])) {
    $form_state['step'] = MINI_USER_REGISTER_CANCEL_FORM;
    $form_state['rebuild'] = TRUE;
  }
  // Try to register the employee, and display the thanks page.
  else {
    if (!preg_match('/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/', $form_state['values']['mail'])) {
      form_set_error('name', t('Your email address is not correct.'));
      $form_state['step'] = MINI_USER_REGISTER_CANCEL_FORM;
      $form_state['rebuild'] = TRUE;
    }
      $mini_account['values'] = array_merge($mini_account['values'], $form_state['values']);
      // Try to register the employee.
      $form_state['step'] = MINI_USER_REGISTER_CONFIRM_FORM;
      $form_state['rebuild'] = TRUE;
      $form['#user'] = drupal_anonymous_user();
      user_register_submit($form, $mini_account);
     // mini_user_client()->register($user, $form_state['values']['media']);
  }
}

/**
 * Form builder; Step 1 - Employee registration form.
 */
function mini_user_register_form($form, &$form_state) {
  $form['user']['help'] = array(
    '#type' => 'section',
    '#title' => t('When to use this form ?'),
    '#description' => '<p>' . t('You have forgotten your credentials or want to register.') . '</p>'
                    . '<p>' . t('This form allows you to request a username and temporary password change when you must first login.') . '</p>',
  );

  $form['user']['identifier'] = array(
    '#type' => 'section',
    '#title' => t('Application identifier'),
    '#description' => '<div class="rw form-rw">' . t('Note: All fields are mandatory.')
                    . "</div>\n<div class=\"error error-wrapper\"></div>\n",
  );
  $form['user']['identifier']['name'] = array(
    '#title' => t('Name'),
    '#title_display' => 'grid',
    '#description' => t('Please enter your nick name.This will '),
    '#type' => 'textfield',
    '#placeholder' => 'Nick name',
    '#required' => TRUE,
    '#theme_wrappers' => array('form_element', 'container'),
  );
  $form['user']['identifier']['firstName'] = array(
      '#title' => t('First name'),
      '#title_display' => 'grid',
      '#description' => t('Please enter your first name.'),
      '#type' => 'textfield',
      '#placeholder' => 'Lenon',
      '#required' => TRUE,
      '#theme_wrappers' => array('form_element', 'container'),
  );
  $form['user']['identifier']['lastName'] = array(
    '#title' => t('Last name'),
    '#title_display' => 'grid',
    '#description' => t('Please enter your last name.'),
    '#type' => 'textfield',
    '#placeholder' => 'John',
    '#required' => TRUE,
    '#theme_wrappers' => array('form_element', 'container'),
  );

  $form['user']['identifier']['phone'] = array(
    '#title' => t('Mobile number'),
    '#title_display' => 'grid',
    '#description' => t('Please enter your mobile number.'),
    '#type' => 'textfield',
    '#placeholder' => '0600000000',
    '#required' => TRUE,
    '#theme_wrappers' => array('form_element', 'container'),
  );
  $form['user']['identifier']['address'] = array(
      '#title' => t('Address'),
      '#title_display' => 'grid',
      '#description' => t('Please enter your address.'),
      '#type' => 'textfield',
      '#placeholder' => 'Rue',
      '#required' => TRUE,
      '#theme_wrappers' => array('form_element', 'container'),
  );
  return $form;
}

/**
 * Form builder; Validates the employee registration form.
 */
function mini_user_register_form_validate($form, &$form_state) {

  if ($form_state['values']['name']){
    $user = user_load_by_name($form_state['values']['name']);
    if($user){
      // User exist
      form_set_error('name', t('Your name is already exist.'));
      return;
    }
  } else {
    form_set_error('name', t('Your name is not correct.'));
    return;
  }

  if (!$form_state['values']['firstName']) {
    form_set_error('name', t('Your first name is not correct.'));
    return;
  }

  if (!$form_state['values']['lastName']) {
    form_set_error('name', t('Your last name is not correct.'));
    return;
  }

  if (!$form_state['values']['address']) {
    form_set_error('name', t('Your address is not correct.'));
    return;
  }

  if ($form_state['values']['phone']) {
    if (!preg_match('/^[0-9]{10}$/', $form_state['values']['phone']) ) {
      form_set_error('name', t('Your mobile number is not correct.'));
      return;
    }
  } else {
    form_set_error('name', t('Your mobile number is not correct.'));
    return;
  }

  if (form_get_errors()) {
    // Only cache the form if no errors are encountered during validation.
    $form_state['cache'] = FALSE;
  }
  $form_state['mini_account'] = $form_state;
}

/**
 * Form builder; Step 2 - Employee registration choose media form.
 */
function mini_user_register_contact_form($form, &$form_state) {
  $form['user']['contact'] = array(
    '#type' => 'section',
    '#description' => '<p>' . t('Your login information will be sent to you by email or by SMS based on the information originally furnished to Human Resources or the information updated by you in the intranet rubric, \'My profile\'.') . '</p>'
                    . '<p>' . t('If email and portable telephone information are available in your connection data, you may choose the reception mode which may suit you best.')
                    . "</p>\n<div class=\"error error-wrapper\"></div>\n",
  );

  $form['user']['contact']['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#required' => TRUE,
    '#placeholder' => 'john@minoritegroup.com',
    '#theme_wrappers' => array('form_element', 'container'),
    '#maxlength' => 255,
  );
  return $form;
}

/**
 * Form builder; Step 3 - Confirmation page.
 */
function mini_user_register_confirm_form($form, &$form_state) {

  $form['user']['help'] = array(
    '#type' => 'section',
    '#title' => t('Assignment of Username and temporary password'),
    '#description' => '<p style="word-break:break-word;">' . t('A message specifying your username and your temporary password will be sent to the following address:') . '</p>',
  );

  $form['user']['confirm'] = array(
    '#type' => 'section',
  );

  if ($form_state['values']['mail']) {
    $title = t('Email');
    $value = $form_state['values']['mail'];
  }

  $form['user']['confirm']['contact'] = array(
    '#prefix' => '<div class="rw form-rw">',
    '#markup' => '<p class="w-1"><label>' . $title . '</label></p><p class="w-2 show_email">' . $value . '</p>',
    '#suffix' => '</div>',
  );

  $form['user']['extra'] = array(
    '#markup' => '<p>' . t('If you do not receive this message please contact your Human Resources representative (*) to verify the contact data.') . '</p>'
               . '<p>' . t('Welcome to the intranet.') . '</p>'
               . '<p>' . t('The Hub team') . '</p>',
  );

  $form['user']['notabene'] = array(
    '#prefix' => '<div id="notabene01" class="rw notabene-wrapper">',
    '#markup' => '<p>' . t('(*) If you do not know who your Human Resources contact is, ask your manager or department assistant.') . '</p>',
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Form builder; Step 4 - No contact data page.
 */
function mini_user_register_cancel_form($form, &$form_state) {
  $form['user']['help'] = array(
    '#type' => 'section',
    '#title' => t('Lack of contact data'),
    '#description' => '<p>' . t('We’re sorry.') . '<strong>' . t(' We are unable to send you your login information. ').'</strong>' . '</p>'
                    . '<p>' . '<strong>' . t('Contact your Human Resources representative and specify your email address ') . '</strong>' . '(<a href="#notabene01" title="Voir la note">*</a>)' . t(' and/or portable telephone number. ') . '</p>'
                    . '<p>' . t("Subsequently, you will receive your login information by email or SMS.  After connection you may provide all your contact data in the 'My profile' space.") . '</p>'
                    . '<p>' . t('Thank you for your understanding.') . '</p>'
                    . '<p>' . t('The Hub team') . '</p>',
  );

  $form['user']['notabene'] = array(
    '#prefix' => '<div id="notabene01" class="rw notabene-wrapper">',
    '#markup' => '<p>' . t('(*) If you do not know who your Human Resources contact is, ask your manager or department assistant.') . '</p>',
    '#suffix' => '</div>',
  );

  return $form;
}
