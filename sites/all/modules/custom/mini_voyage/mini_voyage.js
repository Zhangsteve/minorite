(function ($) {

Drupal.behaviors.articleFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.node-form-associated-blocks', context).drupalSetSummary(function (context) {
      var articlesCheckbox = $('.form-item-articles-und input', context);
      var vals = [];

      if (articlesCheckbox.is(':checked')) {
        vals.push(Drupal.t($('label', articlesCheckbox.parent()).text()));
      }

      return vals.length ? vals.join(', ') : Drupal.t('Not associated');
    });
  }
};

})(jQuery);
