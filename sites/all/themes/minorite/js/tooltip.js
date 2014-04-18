/**
 * Adds a jQuery tool-tip on following CSS classes.
 */
jQuery(document).ready(function() {
  jQuery('.ico-help, .ico-favorite, .ico-printer').tooltip({
    show: null, // show immediately
    tooltipClass: "tooltip-custom-wrapper",
    position: {
      my: 'left center',
      at: 'right+2 top+9'
    },
    hide: {
      effect: "" // fadeOut
    },
    open: function(event, ui) {
      ui.tooltip.animate({top: ui.tooltip.position().top + 0}, "fast");
    },
    close: function(event, ui) {
      ui.tooltip.hover(
        function () {
          jQuery(this).stop(true).fadeTo(400, 1);
        },
        function () {
          jQuery(this).fadeOut("400", function(){ jQuery(this).remove(); });
        }
      );
    }
  });
});
