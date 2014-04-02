<?php

/**
 * @file
 * The theme system, which controls the output of Drupal.
 */

/**
 * Theming function : add li element for list view_mode.
 */
function minorite_list($variables){
  return '<li>' . $variables['children'] . '</li>';
}

/**
 * Theming function : add a header wrapper for html5 theme.
 */
function minorite_header($variables){
  return '<header'.drupal_attributes($variables['elements']['#wrapper_attributes']).'>'.$variables['elements']['#children'].'</header>';
}

/**
 * Theming function : add a nav wrapper for html5 theme.
 */
function minorite_nav($variables){
  return '<nav'.drupal_attributes($variables['elements']['#wrapper_attributes']).'>'.$variables['elements']['#children'].'</nav>';
}

/**
 * Theming function : add a aside wrapper for html5 theme.
 */
function minorite_aside($variables){
  return '<aside'.drupal_attributes($variables['elements']['#wrapper_attributes']).'>'.$variables['elements']['#children'].'</aside>';
}

/**
 * Theming function : add a footer wrapper for html5 theme.
 */
function minorite_footer($variables){
  return '<footer'.drupal_attributes($variables['elements']['#wrapper_attributes']).'>'.$variables['elements']['#children'].'</footer>';
}

/**
 * Theming function : add a article wrapper for html5 theme.
 */
function minorite_article($variables){
  return '<article'.drupal_attributes($variables['elements']['#wrapper_attributes']).'>'.$variables['elements']['#children'].'</article>';
}

/**
 * Returns HTML for a list or nested list of items.
 *
 * @param $variables
 *   An associative array containing:
 *   - items: An array of items to be displayed in the list. If an item is a
 *     string, then it is used as is. If an item is an array, then the "data"
 *     element of the array is used as the contents of the list item. If an item
 *     is an array with a "children" element, those children are displayed in a
 *     nested list. All other elements are treated as attributes of the list
 *     item element.
 *   - type: The type of list to return (e.g. "ul", "ol").
 *   - attributes: The attributes applied to the list element.
 */
function minorite_item_list($variables) {
  $items = $variables['items'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $output = '';

  if (!empty($items)) {
    $output = "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= minorite_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  return $output;
}

/**
 * Returns HTML for a "more" link, like those used in blocks.
 *
 * @param $variables
 *   An associative array containing:
 *   - url: The URL of the main page.
 *   - title: A descriptive verb for the link, like 'Read more'.
 */
function minorite_more_link($variables) {
  return '<p class="readmore">' . l($variables['title'], $variables['url'], array('attributes' => array('title' => $variables['title']), 'query' => $variables['query'])) . '</p>';
}

/**
 * Returns HTML for a set of links.
 *
 * @param $variables
 *   An associative array containing:
 *   - links: An associative array of links to be themed. The key for each link
 *     is used as its CSS class. Each link should be itself an array, with the
 *     following elements:
 *     - title: The link text.
 *     - href: The link URL. If omitted, the 'title' is shown as a plain text
 *       item in the links list.
 *     - html: (optional) Whether or not 'title' is HTML. If set, the title
 *       will not be passed through check_plain().
 *     - attributes: (optional) Attributes for the anchor, or for the <span>
 *       tag used in its place if no 'href' is supplied. If element 'class' is
 *       included, it must be an array of one or more class names.
 *     If the 'href' element is supplied, the entire link array is passed to
 *     l() as its $options parameter.
 *   - attributes: A keyed array of attributes for the UL containing the
 *     list of links.
 *   - heading: (optional) A heading to precede the links. May be an
 *     associative array or a string. If it's an array, it can have the
 *     following elements:
 *     - text: The heading text.
 *     - level: The heading level (e.g. 'h2', 'h3').
 *     - class: (optional) An array of the CSS classes for the heading.
 *     When using a string it will be used as the text of the heading and the
 *     level will default to 'h2'. Headings should be used on navigation menus
 *     and any list of links that consistently appears on multiple pages. To
 *     make the heading invisible use the 'element-invisible' CSS class. Do not
 *     use 'display:none', which removes it from screen-readers and assistive
 *     technology. Headings allow screen-reader and keyboard only users to
 *     navigate to or skip the links. See
 *     http://juicystudio.com/article/screen-readers-display-none.php and
 *     http://www.w3.org/TR/WCAG-TECHS/H42.html for more information.
 */
function minorite_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
          && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'nav-selected';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Returns HTML for a breadcrumb trail.
 *
 * @param $variables
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 */
function minorite_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    return '<ul class="nav"><li>' . implode('</li><li>', $breadcrumb) . '</li></ul>';
  }
}

/**
 * Returns HTML for a field.
 *
 * This is the disney theme implementation to display the value of a field.
 * Theme developers who are comfortable with overriding theme functions may do
 * so in order to customize this markup. This function can be overridden with
 * varying levels of specificity. For example, for a field named 'body'
 * displayed on the 'article' content type, any of the following functions will
 * override this default implementation. The first of these functions that
 * exists is used:
 * - THEMENAME_field__body__article()
 * - THEMENAME_field__article()
 * - THEMENAME_field__body()
 * - THEMENAME_field()
 *
 * Theme developers who prefer to customize templates instead of overriding
 * functions may copy the "field.tpl.php" from the "modules/field/theme" folder
 * of the Drupal installation to somewhere within the theme's folder and
 * customize it, just like customizing other Drupal templates such as
 * page.tpl.php or node.tpl.php. However, it takes longer for the server to
 * process templates than to call a function, so for websites with many fields
 * displayed on a page, this can result in a noticeable slowdown of the website.
 * For these websites, developers are discouraged from placing a field.tpl.php
 * file into the theme's folder, but may customize templates for specific
 * fields. For example, for a field named 'body' displayed on the 'article'
 * content type, any of the following templates will override this default
 * implementation. The first of these templates that exists is used:
 * - field--body--article.tpl.php
 * - field--article.tpl.php
 * - field--body.tpl.php
 * - field.tpl.php
 * So, if the body field on the article content type needs customization, a
 * field--body--article.tpl.php file can be added within the theme's folder.
 * Because it's a template, it will result in slightly more time needed to
 * display that field, but it will not impact other fields, and therefore,
 * is unlikely to cause a noticeable change in website performance. A very rough
 * guideline is that if a page is being displayed with more than 100 fields and
 * they are all themed with a template instead of a function, it can add up to
 * 5% to the time it takes to display that page. This is a guideline only and
 * the exact performance impact depends on the server configuration and the
 * details of the website.
 *
 * @param $variables
 *   An associative array containing:
 *   - label_hidden: A boolean indicating to show or hide the field label.
 *   - title_attributes: A string containing the attributes for the title.
 *   - label: The label for the field.
 *   - content_attributes: A string containing the attributes for the content's
 *     div.
 *   - items: An array of field items.
 *   - item_attributes: An array of attributes for each item.
 *   - classes: A string containing the classes for the wrapping div.
 *   - attributes: A string containing the attributes for the wrapping div.
 *
 * @see template_preprocess_field()
 * @see template_process_field()
 * @see field.tpl.php
 *
 * @ingroup themeable
 */
function minorite_field($variables) {
  return render($variables['items']);
}

/**
 * Returns HTML for an image field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Associative array of image data, which may include "uri", "alt",
 *     "title" and "attributes".
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
function minorite_image_formatter($variables) {
  $item = $variables['item'];
  $image = array(
    'path' => $item['uri'],
  );

  if (is_array($item) && array_key_exists('alt', $item)) {
    $image['alt'] = $item['alt'];
  }

  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  // Do not output an empty 'title' attribute.
  if (isset($item['title']) && drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  if ($variables['image_style']) {
    $image['style_name'] = $variables['image_style'];
    $output = theme('image_style', $image);
  }
  else {
    $output = theme('image', $image);
  }

  // The link path and link options are both optional, but for the options to be
  // processed, the link path must at least be an empty string.
  if (isset($variables['path']['path'])) {
    $path = $variables['path']['path'];
    $options = isset($variables['path']['options']) ? $variables['path']['options'] : array();
    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;
    $output = l($output, $path, $options);
  }

  // Adds the caption content to the output.
  if (isset($item['caption']) && $item['caption'] != '') {
    $output .= '<p class="figure-caption">' . $item['caption'] . '</p>';
  }

  // Adds the block position string.
  $position = isset($item['position']) ? $item['position'] : 'fullwidth';

  return '<figure class="figure block-' . $position . '">' . $output . "</figure>\n";
}

/**
 * Returns HTML for an image.
 *
 * @param $variables
 *   An associative array containing:
 *   - path: Either the path of the image file (relative to base_path()) or a
 *     full URL.
 *   - alt: The alternative text for text-based browsers. HTML 4 and XHTML 1.0
 *     always require an alt attribute. The HTML 5 draft allows the alt
 *     attribute to be omitted in some cases. Therefore, this variable defaults
 *     to an empty string, but can be set to NULL for the attribute to be
 *     omitted. Usually, neither omission nor an empty string satisfies
 *     accessibility requirements, so it is strongly encouraged for code
 *     calling theme('image') to pass a meaningful value for this variable.
 *     - http://www.w3.org/TR/REC-html40/struct/objects.html#h-13.8
 *     - http://www.w3.org/TR/xhtml1/dtds.html
 *     - http://dev.w3.org/html5/spec/Overview.html#alt
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 */
function minorite_image($variables) {
  $attributes = $variables['attributes'];
  $attributes['src'] = file_create_url($variables['path']);

  foreach (array('alt', 'title') as $key) {

    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}

/**
 * Returns HTML for the set of links of the locale block.
 */
function minorite_links__locale_block($variables) {
  $variables['attributes']['class'] = array('nav', 'switch-tongue');
  // Removes class as it is not used.
  $variables['links']['en']['title'] = 'En';
  $variables['links']['en']['attributes']['title'] = t('English site');
  unset($variables['links']['en']['attributes']['class']);
  $variables['links']['fr']['title'] = 'Fr';
  $variables['links']['fr']['attributes']['title'] = t('French site');
  unset($variables['links']['fr']['attributes']['class']);

  return theme('links', $variables);
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function minorite_menu_tree($variables) {
  return '<ul class="nav meganav">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function minorite_menu_tree__primary($variables) {
  return '<ul class="nav" id="nav-primary">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function minorite_menu_tree__secondary($variables) {
  return '<ul class="nav" id="nav-secondary">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function minorite_menu_tree__user_menu(array $variables) {
  $links = '';
  $options = '';
  global $user;

  if ($user->uid) {
    // TODO: add this as a menu link.
    $text = t('Welcome !first_name', array('!first_name' => $user->firstName));
    $options .= '<option>' . l($text, 'user', array('html' => TRUE)) . '</option>';
  }

  foreach (explode("\n", $variables['tree']) as $leaf) {
    substr($leaf, 0, 2) === '<l' ? $links .= $leaf . "\n" : $options .= $leaf;
  }

  if (!empty($options)) {
    // TODO: Refactor this with theme_select()!
    $change = 'onchange="location = this.options[this.selectedIndex].value;"';
    $select = '<select name="user-menu" id="user-menu" tabindex="0" class="custom-select-user" ' . $change . '>' . $options . '</select>';
    $select_span = '<span class="custom-select-user-wrapper">' . $select . '</span>';
    $label = '<label for="user-menu" class="visuallyhidden">' . t('User menu') . "</label>\n";
    $legend = '<legend class="visuallyhidden">' . 'Menu utilisateur (naviguer avec les flêches hauts et bas)' . "</legend>\n";
    $links .= '<li><fieldset>' . $legend . $label . $select_span . '</fieldset></li>';
  }

  return '<ul class="nav user-access-menu">' . $links . "</ul>\n";
}

/**
 * Returns HTML for 'home' menu link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_link__user_menu(array $variables) {
  global $user;

  $element = $variables['element'];
  $options = $variables['element']['#original_link']['options'];

  // Cas particulier pour le title de la page abonnement Newsletter
  if ($element['#href'] == 'newsletter/subscriptions') {
    $abo = simplenews_subscriber_load_by_uid($user->uid);
    if (isset($abo->tids) && !empty($abo->tids)) {
      $variables['element']['#title'] = t('My newsletter');
    } else {
      $variables['element']['#title'] = t('Subscribe to newsletter');
    }
  }

  // Menu visible que pour utilisateur non connecté
  if (isset($options['anonymous']) && $options['anonymous'] == '1' && $user->uid) {
    return '';
  }
  if (isset($options['position']) && $options['position'] == 'right' && $user->uid) {
    // If no position has been set, or position is 'right', displays the link as
    // an option item, which will have the effect to put it in the drop-down.
    return '<option value="' . url($element['#href']) . '">' . $element['#title'] . "</option>\n";
  }

  // Default to normal menu list item.
  return minorite_menu_link($variables);
}

/**
 * Returns HTML for 'Footer Links' menu link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_tree__menu_footer(array $variables) {
  return '<ul class="nav">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * @param $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @ingroup themeable
 */
function minorite_menu_tree__links(array $variables) {
  return '<select onchange="window.open(this.options[this.selectedIndex].value);"><option>' . t('Select a site...') . '</option>' . $variables['tree'] . '</select>';
}

/**
 * Returns HTML for 'links' menu link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_link__links(array $variables) {
  $element = $variables['element'];
  $options = $variables['element']['#original_link']['options'];
  return '<option value="' . url($element['#href']) . '">' . $element['#title'] . "</option>\n";
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_link(array $variables) {
  $element = $variables['element'];
  $path = $element['#href'];
  $sub_menu = '';

  // Append active class.
  if (($path == $_GET['q'] || ($path == '<front>' && drupal_is_front_page())) &&
      (empty($options['language']) || $options['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] = 'nav-selected';
  }

  if (!empty($element['#below'])) {
    $sub_menu = drupal_render($element['#below']);
    $element['#attributes']['class'][] = 'nav-has-child';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Returns HTML for 'home' menu link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_link__home(array $variables) {
  $element = $variables['element'];

  $output = l('<span>' . $element['#title'] . '</span>', $element['#href'], array('html' => TRUE));
  return '<li>' . $output . "</li>\n";
}

/**
 * Returns HTML for 'home' menu link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function minorite_menu_link__menu_footer(array $variables) {
  $element = $variables['element'];

  return '<li>' . l($element['#title'], $element['#href']) . "</li>\n";
}

/**
 * Theme the "no feedback" option.
 *
 * @return
 *  Themed html feedback.
 *
 * @ingroup themeable
 */
function minorite_quiz_no_feedback() {
  return '<div id="quiz_finish">' . t('Thank you for your participation in the competition!') . '</div>';
}

/**
 * Theme the preview node.
 * Only show the full node version
 */
function minorite_node_preview($variables) {
  $node = $variables['node'];

  $output = '<div class="preview">';

  $preview_trimmed_version = FALSE;

  //$elements = node_view(clone $node, 'teaser');
  //$trimmed = drupal_render($elements);
  $elements = node_view($node, 'full');
  $full = drupal_render($elements);

  // Do we need to preview trimmed version of post as well as full version?
  /*if ($trimmed != $full) {
    drupal_set_message(t('The trimmed version of your post shows what your post looks like when promoted to the main page or when exported for syndication.<span class="no-js"> You can insert the delimiter "&lt;!--break--&gt;" (without the quotes) to fine-tune where your post gets split.</span>'));
    $output .= '<h3>' . t('Preview trimmed version') . '</h3>';
    $output .= $trimmed;
    $output .= '<h3>' . t('Preview full version') . '</h3>';
    $output .= $full;
  }
  else {*/
    $output .= $full;
  //}
  $output .= "</div>\n";

  return $output;
}

/**
 * Template views pre render to set the title with the translate interface
 */
function minorite_views_pre_render(&$view) {
  $view->set_title(t($view->get_title()));
}

/**
 * Render a themed list of links.
 *
 * @param $variables
 *   - elements: A renderable array of links using the following keys:
 *     - #attributes: Optional array of attributes for the list item, processed
 *       via drupal_attributes().
 *     - #title: Title of the link, passed to l().
 *     - #href: Optional path of the link, passed to l(). When omitted, the
 *       element's '#title' is rendered without link.
 *     - #description: Optional alternative text for the link, passed to l().
 *     - #options: Optional alternative text for the link, passed to l().
 *     The array key of each child element itself is passed as path for l().
 */
function minorite_admin_menu_links($variables) {
  $destination = &drupal_static('admin_menu_destination');
  $elements = $variables['elements'];

  if (!isset($destination)) {
    $destination = drupal_get_destination();
    $destination = $destination['destination'];
  }

  // The majority of items in the menu are sorted already, but since modules
  // may add or change arbitrary items anywhere, there is no way around sorting
  // everything again. element_sort() is not sufficient here, as it
  // intentionally retains the order of elements having the same #weight,
  // whereas menu links are supposed to be ordered by #weight and #title.
  uasort($elements, 'admin_menu_element_sort');
  $elements['#sorted'] = TRUE;

  $output = '';
  foreach (element_children($elements) as $path) {
    // Early-return nothing if user does not have access.
    if (isset($elements[$path]['#access']) && !$elements[$path]['#access']) {
      continue;
    }
    $elements[$path] += array(
      '#attributes' => array(),
      '#options' => array(),
    );
    // Render children to determine whether this link is expandable.
    if (isset($elements[$path]['#type']) || isset($elements[$path]['#theme']) || isset($elements[$path]['#pre_render'])) {
      $elements[$path]['#children'] = drupal_render($elements[$path]);
    }
    else {
      $elements[$path]['#children'] = theme('admin_menu_links', array('elements' => $elements[$path]));
      if (!empty($elements[$path]['#children'])) {
        $elements[$path]['#attributes']['class'][] = 'expandable';
      }
      if (isset($elements[$path]['#attributes']['class'])) {
        $elements[$path]['#attributes']['class'] = $elements[$path]['#attributes']['class'];
      }
    }

    // Manual Translate of some admin menu for the content type
    if (!empty($elements[$path]['#href'])) {
      //$new_title = minorite_locale_admin_menu_translate($elements[$path]['#href']);
      if (isset($new_title)) {
        $elements[$path]['#title'] = $new_title;
      }
    }

    $link = '';
    // Handle menu links.
    if (isset($elements[$path]['#href'])) {
      // Strip destination query string from href attribute and apply a CSS class
      // for our JavaScript behavior instead.
      if (isset($elements[$path]['#options']['query']['destination']) && $elements[$path]['#options']['query']['destination'] == $destination) {
        unset($elements[$path]['#options']['query']['destination']);
        $elements[$path]['#options']['attributes']['class'][] = 'admin-menu-destination';
      }

      $link = l($elements[$path]['#title'], $elements[$path]['#href'], $elements[$path]['#options']);
    }
    // Handle plain text items, but do not interfere with menu additions.
    elseif (!isset($elements[$path]['#type']) && isset($elements[$path]['#title'])) {
      if (!empty($elements[$path]['#options']['html'])) {
        $title = $elements[$path]['#title'];
      }
      else {
        $title = check_plain($elements[$path]['#title']);
      }
      $attributes = '';
      if (isset($elements[$path]['#options']['attributes'])) {
        $attributes = drupal_attributes($elements[$path]['#options']['attributes']);
      }
      $link = '<span' . $attributes . '>' . $title . '</span>';
    }

    $output .= '<li' . drupal_attributes($elements[$path]['#attributes']) . '>';
    $output .= $link . $elements[$path]['#children'];
    $output .= '</li>';
  }
  // @todo #attributes probably required for UL, but already used for LI.
  // @todo Use $element['#children'] here instead.
  if ($output) {
    $elements['#wrapper_attributes']['class'][] = 'dropdown';
    $attributes = drupal_attributes($elements['#wrapper_attributes']);
    $output = "\n" . '<ul' . $attributes . '>' . $output . '</ul>';
  }
  return $output;
}
