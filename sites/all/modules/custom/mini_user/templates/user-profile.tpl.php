<?php
/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
  <section class="profile-wrapper-display section rw">
    <div class="w-1">
      <fieldset>
        <legend class="visuallyhidden"><?php print t('My connection data')?></legend>
        <h2><?php print t('My connection data')?></h2>
        <p class="rw form-rw"><label><?php print t('First Name: ');?></label><?php print $elements['#account']->firstName; ?></p>
        <p class="rw form-rw"><label><?php print t('Last Name: ');?></label><?php print $elements['#account']->lastName; ?></p>
        <p class="rw form-rw"><label><?php print t('Email: ');?></label><?php print $elements['#account']->mail; ?></p>
        <p class="rw form-rw"><label><?php print t('Phone Number: ');?></label><?php print $elements['#account']->phone; ?></p>
        <p class="rw form-rw"><label><?php print t('Address: ');?></label><?php print $elements['#account']->address; ?></p>

      </fieldset>
    </div>

    <div class="w-2">
      <div class="inner-pad">
        <div class="rtf-focusing">
          <p><?php print t("The information contained in 'My connection data' is important. These data not only permit authentification but also allow you to change your password and to receive confirmation by email or SMS, and to receive the newsletter. Furthermore you may also enter your workplace in the space, 'My location'. This information will complement the company phone directory.<br><br>You can modify all data by clicking 'Edit my profile'.<br><br>Please note that the format required for your telephone number is the international format, that is the '+' sign followed by the international code of the country of your residence followed by your mobile telephone number, but without the first zero. For example: +33612131415"); ?></p>
        </div> <!-- /.rtf-focusing -->
      </div>
    </div>
  </section> <!-- /.profile-wrapper-display -->

  <section class="profile-wrapper-setup section rw">
    <div class="w-1">
      <fieldset>
        <legend class="visuallyhidden"><?php print t('Edit informations'); ?></legend>
        <h2><?php print t('Edit informations'); ?></h2>
        <p class="form-rw form-rw-note"><span class="form-frame"><a href="<?php print url("user/{$elements['#account']->uid}/edit"); ?>" class="ico-editor"><i></i><?php print t('Edit my profile'); ?></a> <a href="<?php print url('user/password'); ?>" class="ico-locker"><i></i><?php print t('Edit my password'); ?></a></span></p>
      </fieldset>
    </div>
  </section> <!-- ./profile-wrapper-setup -->
