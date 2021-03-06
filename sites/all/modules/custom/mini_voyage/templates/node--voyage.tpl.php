<?php

/**
 * @file
 * Default theme implementation to display an article.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Article" it would result in "node-article". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. page, article, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>

<article class="article-wrapper">
  <?php print render($content['metadata']); ?>

  <p class="article-tool-wrapper">
    <span class="ico-tool-wrapper">
      <span title="<?php print t('Print this news.'); ?>" class="ico-printer"><i></i><span class="visuallyhidden"><?php print t('Print this news.'); ?></span></span>
      <span title="<?php print t('Send by email');?>" class="ico-email">
        <a href ="/<?php print $content['links']['print_mail']['#links']['print_mail']['href']?>">
          <?php print $content['links']['print_mail']['#links']['print_mail']['title'];?>
        </a>
      </span>
    </span>
  </p>

  <h1><?php print $title; ?></h1>
 <?php //var_dump($content['field_voyage_image']);die();?>
 <div class="rw album-dataitem-desc-wrapper">
   <div class="w-1">
      <ul class="album-datalist">
        <li class="album-has-children">
          <?php print  render($content['field_vignette']);?>
        </li>
      </ul>
    </div>
    <div class="w-2">
     <?php if (count($content['field_voyage_image']) > 1):?>
      <p class="form-button-rw form-actions">
        <a href="#" onclick="javascript:media_slideshow();" class="button-like button-ico-slider"><i></i><?php print t('Launch the slideshow'); ?></a>
      </p>
     <?php endif;?>
     <div class ="album-dataitem-hidden">
       <ul class="album-datalist album-dataitem">
        <?php
          // Asset is an Image
          //var_dump($content['field_voyage_image']);die();
          if (!empty($content['field_voyage_image']['#items'])) {
            foreach ($content['field_voyage_image']['#items'] as $key => $image) {
              $output_image = render($content['field_voyage_image'][$key]);
              $output = '<li style="display:none;">';
              // Title of the asset
              $title = truncate_utf8($image['title'], 60, FALSE, TRUE);
              $path = file_create_url($image['uri']);
              // Make link
              $output .= l($output_image, $path, array('html' => TRUE, 'attributes' => array('alt' => $title, 'title' => $title, 'rel' => 'album01')));
              $output .= '</li>';
              echo $output;
            }
          }
        ?>
       </ul>
     </div>
    </div>
 </div>

  <div class="article-body">
    <?php print render($content['body']); ?>
  </div> <!-- ./article-body -->
</article>
