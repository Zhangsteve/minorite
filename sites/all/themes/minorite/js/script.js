// GROUPE LP - vers 1.21 Mar-May-June2013
//
// Pseudo radio buttons modfied
//


//Testing orientation
function orientation_change() {
    if (window.orientation == 0 || window.orientation == 180)
        document.getElementById("viewport").setAttribute("content", "width=device-width, maximum-scale=1.0, initial-scale=1.0, user-scalable=no");
    else if (window.orientation == -90 || window.orientation == 90)
        document.getElementById("viewport").setAttribute("content", "width=device-height, maximum-scale=1.0, initial-scale=1.0, user-scalable=no");
}

$ = jQuery;

$(document).ready(function() {

//init SHORTCUTS
$("#access-shortcuts-wrapper>ul").initShortcuts();


//init Navigation --> see window resize
$("#nav-primary, #nav-favorite").initNav();


//Syze: set sizes and size names //lt890 triggers event
//syze.sizes(768, 890).from('browser');

//Nav Secondary
syze.sizes(768, 890, 891).callback(
	function(currentSize) {
		//
		//console.log(currentSize);
	if(currentSize<890){
		$('#content .contentcol.col-retractable > .w-1').addClass('menu-mobile-retracted');
		//
	}
	if(currentSize==891){
		$('#content .contentcol.col-retractable > .w-1').removeClass('menu-mobile-slidefx');
		//console.log('sup a 891');
		//
	}
	//
	}
);
//Nav secondary extra
/*
$('.menu-mobile-retracted .navlist-wrapper h2').bind('click focus',function() {
	$('.w-1.menu-mobile-retracted').toggleClass("menu-mobile-slidefx");
	//console.log('h2 clique');
});
*/
$('.contentcol').on('click', '.menu-mobile-retracted .navlist-wrapper h2',function() {
	$('.w-1.menu-mobile-retracted').toggleClass("menu-mobile-slidefx");
	//console.log('h2 clique');
});

//Nav secondary extra -> draggable
if ($(".menu-mobile-retracted .navlist-wrapper").length) {
	$(".menu-mobile-retracted .navlist-wrapper").draggable({axis: "y"});
}

//Has Custom Select (cs-)
//See: http://jamielottering.github.com/DropKick/
// $('.custom-select-ds').dropkick();
// $('.custom-select-user').dropkick({theme:'dsuser'});
//CUSTOM Select
//https://github.com/rayui/flyweight-jquery-custom-select
//$("select").flyweightCustomSelect();


//CUSTOM Buttons
//see: http://damirfoy.com/iCheck/
$('.form-custom-radio, .form-custom-checkbox, form#quiz-question-answering-form .form-checkbox, form#quiz-question-answering-form .form-custom-radio').iCheck({
	checkboxClass: 'icheckbox_square-blue',
	radioClass: 'iradio_square-blue',
	increaseArea: '20%' // optional
});

//Datepicker
$( ".is-datepicker" ).datepicker({
  showOtherMonths:true,
  selectOtherMonths:true,
  dateFormat:"mm/dd/yy", //Date.parse need this format
  onSelect: function(dateText) {
    var dateRange = {};
    dateRange.from = dateRange.upto = Date.parse(dateText) / 1000;
    // We send date via session to events page
    // not to interfer with filter process workflow
    $.post(
      "/ajax_session.php",
      { event_overview_filter: dateRange}
    ).done(function(data){
      window.location.href = Drupal.settings.basePath + Drupal.settings.disney_event.language + '/headlines/events';
    });
  }
});

//Has DatePicker
$(function() {
  $(".has-datepicker").datepicker({
    //changeMonth: true,
    //changeYear: true,
    //dateFormat: 'dd-mm-yy',
    //numberOfMonths: 2,
    //showButtonPanel: true
    //showOn: "button",
    //buttonImage: "img/ico_calendar.gif",
    //buttonImageOnly: true/
  });
});

//Collapsable Boxes
//see: http://css-tricks.com/snippets/jquery/animate-heightwidth-to-auto/
$(".collapsable-box-body").addClass('visuallyhidden');
$('.collapsable-box-trigger a').bind('click',function() {
		$(this).parent().toggleClass('ico-arrow-n','ico-arrow-s');
		$(this).parent().parent().find('.collapsable-box-body').toggleClass('visuallyhidden');
		return false;
});
// For Quiz
$(".competition-past-game .collapsable-box-body").first().removeClass('visuallyhidden');
$('button.collapsable-box-trigger').bind('click',function() {
		$(this).toggleClass('ico-arrow-n','ico-arrow-s');
		$(this).parent().find('.collapsable-box-body').toggleClass('visuallyhidden');
		return false;
});

//My HUB block picker: link fx
$(".myhub-item-row .myhub-item-list a").bind('click',function() {
		$(this).parent('li').addClass('myhub-item-selected');
});

$('#homebox-editor').bind('click', function() {
  $('.portlet-header').toggleClass('element-invisible');
  Drupal.homebox.equalizeColumnsHeights();
});

// Asset, fix view 'v_media_gallery' links
$(".views-field-field-asset-video-file a.videobox").bind('click',function(event) {
  $(this).attr('target', '_self');
});
// In search, title and description fields (hidden) must be equal to tags field
$("#edit-submit-v-media-albums").bind('click',function(event) {
    tags_value = $("input#edit-tags").val();
    $("input#edit-title").val(tags_value);
    $("input#edit-description").val(tags_value);
    $("input#edit-gallery-description").val(tags_value);
});
// On selected option of a media sub-gallery, go there
$('.album-subalbum select').change(function() {
  if ($(this).val()) {
    window.location = $(this).val();
  }
});

//TABLE sorter
//see: Jquery - see: http://tablesorter.com/
//see: http://jsfiddle.net/Mottie/abkNM/325/
//$.tablesorter.defaults.sortList = [[0,0]];
//$(".event-data-table.data-table-sortable-wrapper").tablesorter({
//	showProcessing: true,
//	cssHeader: 'data-table-sort',
//	cssAsc: 'data-table-sortup',
//	cssDesc: 'data-table-sortdown',
//  headers: { //Disabling sorting arrows ; we start counting zero
//   1: {sorter: false}
//  }
//});
////tool-data-table
//$(".tool-data-table.data-table-sortable-wrapper").tablesorter({
//	showProcessing: true,
//	cssHeader: 'data-table-sort',
//	cssAsc: 'data-table-sortup',
//	cssDesc: 'data-table-sortdown',
//  headers: { //Disabling sorting arrows ; we start counting zero
//   1: {sorter: false}
//  }
//});


//FAQ Toggle
//see: http://www.designchemical.com/blog/index.php/jquery/jquery-simple-vertical-accordion-menu/
$('.faq-wrapper .faq-content').addClass('visuallyhidden');
$('.faq-toggle, .faq-toggle button').bind("click",function(e) {
  e.stopPropagation();
  var toggleElt = $(this);

  if ($(this).is('button')) {
    toggleElt = $(this).parent('.faq-toggle');
  }
  toggleElt.next().toggleClass('visuallyhidden faq-active').parents('.faq-node').toggleClass('faq-active'); //slideToggle
});
$('.section.faq-section>h2+p').bind("click",function() {
  var section = $(this).parent('.faq-section');
  var numberQuestion = section.find('.faq-node').length;
  var questionOpened = section.find('.faq-node.faq-active').length;
  if( questionOpened >= 0 && questionOpened != numberQuestion){
    section.find('.faq-content:not(.faq-active)').removeClass('visuallyhidden').addClass('faq-active').parents('.faq-node').addClass('faq-active');
  }
  else {
    section.find('.faq-content.faq-active').addClass('visuallyhidden').removeClass('faq-active').parents('.faq-node').removeClass('faq-active');
  }
  return false;
});
$('.faq-wrapper .form-search-wrapper select').change(function(event) {
  $(document).scrollTop($('.section-' + $(this).val()).offset().top );
});

//TABS
	//http://www.jacklmoore.com/notes/jquery-tabs
$('.ui-tabs-wrapper>ul.ui-tabs-nav').each(function(){
    // For each set of tabs, we want to keep track of
    // which tab is active and it's associated content
    var $active, $content, $links = $(this).find('a');

    // Use the first link as the initial active tab
    $active = $links.first().addClass('ui-tabs-active');
    $content = $($active.attr('name'));

    // Hide the remaining content
    $links.not(':first').each(function () {
        $($(this).attr('name')).hide();
    });

    // Bind the click event handler
    $(this).on('click', 'a', function(e){
        // Make the old tab inactive.
        $active.removeClass('ui-tabs-active');
        $content.hide();

        // Update the variables with the new link and content
        $active = $(this);
        $content = $($(this).attr('name'));

        // Make the tab active.
        $active.addClass('ui-tabs-active');
        $content.show();

        // Prevent the anchor's default click action
        e.preventDefault();
    });
});


//Smooth scroll - Top Page FX
//See: http://css-tricks.com/snippets/jquery/smooth-scrolling/
  function filterPath(string) {
  return string
    .replace(/^\//,'')
    .replace(/(index|default).[a-zA-Z]{3,4}$/,'')
    .replace(/\/$/,'');
  }
  var locationPath = filterPath(location.pathname);
  var scrollElem = scrollableElement('html', 'body');

  $('a[href*=#]').each(function() {
    var thisPath = filterPath(this.pathname) || locationPath;
    if (  locationPath == thisPath
    && (location.hostname == this.hostname || !this.hostname)
    && this.hash.replace(/#/,'') ) {
      var $target = $(this.hash), target = this.hash;
      if (undefined !== $target.offset()) {
        if ($target.offset()) {  //RSO+
          var targetOffset = $target.offset().top;
          $(this).click(function(event) {
            event.preventDefault();
            $(scrollElem).animate({scrollTop: targetOffset}, 400, function() {
              location.hash = target;
            });
          });
        }
      }
    }
  });

  // use the first element that is "scrollable"
  function scrollableElement(els) {
    for (var i = 0, argLength = arguments.length; i <argLength; i++) {
      var el = arguments[i],
          $scrollElement = $(el);
      if ($scrollElement.scrollTop()> 0) {
        return el;
      } else {
        $scrollElement.scrollTop(1);
        var isScrollable = $scrollElement.scrollTop()> 0;
        $scrollElement.scrollTop(0);
        if (isScrollable) {
          return el;
        }
      }
    }
    return [];
  }
//


//ALBUM
$(".album-dataitem-hidden ul li a").fancybox({
  //custom_counterText: '{#index#}/{#count#}',
  //titleFormat: fancyTitle,
  'titlePosition' 	: 'inside',
  'overlayOpacity'	: '0.75',
  'overlayColor'	: '#000',
  //'autoScale'		: true,
  'cyclic'          : true,
  'scrolling'       : 'yes',
  'padding'			:	21,
  'margin'			:	21,
  'onComplete'		:	function() {popinIsOpen(this);},
  'onClosed'		:	function() {popinIsClose(this);}
});

//PopinIsOpen
function popinIsOpen(a) {
	//
	$('#fancybox-wrap').addClass(' gallery-popin ');
	$('#fancybox-wrap a#fancybox-close').attr('href', 'javascript:void(0);');
	$('#fancybox-wrap a#fancybox-close').append('<span class="visuallyhidden">Close/Fermer</span>');
	$('#fancybox-wrap a#fancybox-close').focus();
	return  false;
	//
}
//popinIsClose
function popinIsClose(a) {
	//
	$('#fancybox-wrap').removeClass('gallery-popin');
	$('#fancybox-wrap a#fancybox-close').find('span.visuallyhidden').remove();
	a.orig.focus();
	//
}
//fancyTitle - http://www.davole.com/2011/jquery-fancybox-custom-title/
function fancyTitle(title, currentArray, currentIndex, currentOpts){
    if(title != ''){
        var counterText = currentOpts.custom_counterText;
        var $container = $('<div id="fancybox-custom-title-container"></div>');
        var $title = $('<span id="fancybox-custom-title"></span>');
        $container.append($title);
				if(currentArray.length > 1){
            var $counter = $('&nbsp;<span id="fancybox-custom-counter"></span>&nbsp;');
            $counter.text(
                counterText
                .replace('{#index#}', (currentIndex+1)) //+1
                .replace('{#count#}', currentArray.length));
            $container.append($counter);
        }
				$title.text(title);
//				var fbtnl = $("#fancybox-left").clone(true);
//				$container.append(fbtnl);
//				var fbtnr = $("#fancybox-right").clone(true);
//				$container.append(fbtnr);

				var zip = this.href.replace('/sites/', '/media/download?image=sites/');
				$container.append($('<span id="fancybox-custom-buttonholder"><a href="'+zip+'" class="ico-download">Télécharger</a></span>'));
        return $container;
    }
}

//Validate login form when it is submitted
//See: http://jqueryvalidation.org/documentation/
//var validate = $('#castmemberloginform').validate({
////no longer using error area at top of fields
////errorLabelContainer: $("#castmemberloginform div.error.error-wrapper"),
//rules: {
//			checkinput: {
//				required: true,
//        minlength: 1,
//        maxlength: 100
//			},
//			checkdatebirthyear: {
//				required: true,
//        digits: true,
//				range: [1900, 2013],
//        maxlength: 4
//			},
//			checkdatebirth:{
//        required: true,
//				digits: true,
//        maxlength: 2
//    	}
//},
//message: {
//			checkdatebirth:{
//        required: "",
//				minlength: jQuery.format("Entrer au moins {0} caractères"),
//    	},
//			checkdatebirthyear:{
//        required: "Attention",
//				range: jQuery.format("Compris entre {0} et {1}"),
//    	}
//}
////
//});
/*
$('.form-login-cancel').on('click', function (e) {
        e.preventDefault();
        validate.resetForm();
        $('form').get(0).reset();
});
*/

//ICO FAV: turn on ico-favorite
/*$('.ico-favorite').bind('click',function() {
	$(this).toggleClass("ico-favorite-selected");
	//console.log('ico-favorite ON');
});*/


//PRINTER FRIENDLY
$('.ico-printer').click(function() {
	window.print();
	return false;
});


//NICE SCROLL
//See : http://areaaperta.com/nicescroll/demo.html
//Only load on legal-terms page where it is use
//
//$("ul.album-datalist li .inner-pad").niceScroll({cursorcolor:"#C9C9C9",cursorwidth:"5", background:""});
//$("ul.album-datalist li .inner-pad").getNiceScroll().resize();
//
if ($('.term-wrapper .term-scrollable').length) {
  $('.term-wrapper .term-scrollable').niceScroll({cursorcolor:"#C9C9C9",cursorwidth:"5", background:""});
  $('.term-wrapper .term-scrollable').getNiceScroll().resize();
}


//END ready
});


//initShortcuts
$.fn.initShortcuts = function(options) {

	var obj = $(this);
	obj.find('a').focus(function(e) {obj.css('height', 'auto'); });
	obj.find('a').blur(function(e) {obj.css('height', '0px'); });

	return this;
};


//initNav
(function($) {
	//positionNav
	$.fn.positionNav = function(){
		var obj = $(this);
		var sections = obj.find(' > li');
		var subnavs = sections.find('> ul');
		var documentW = $('.navbar-wrapper').width();
		sections.each(function(){
			var section = $(this);
			var subMenuContainer = section.find('> .meganav-wrapper');
			if(subMenuContainer.length > 0){
				if(section.width() + section.position().left < subMenuContainer.outerWidth()){
					subMenuContainer.css('left', -section.position().left);
				}else {
					//console.log(section.width() + section.position().left + subMenuContainer.outerWidth());
					//console.log(subMenuContainer.outerWidth());
					var tmp = documentW - ( section.position().left + subMenuContainer.outerWidth());

					subMenuContainer.css('left',tmp);
				}
			}
			/*
			var subMenuContainerW = subMenuContainer.outerWidth();
			//console.log(section.offset().left + subMenuContainerW + " > " + documentW);
			if ((section.offset().left + subMenuContainerW) > documentW ){
				subMenuContainer.css('left', documentW - (section.offset().left + subMenuContainerW) - 10 );
			}*/
		});

	};
	//initNav
	$.fn.initNav = function(options) {
		var defaults = {
			offClass : "visuallyhidden",
			activeClass : "nav-opened", //nav-selected
			timeOut : 200
		};

		var options = $.extend(defaults, options);
		var obj = $(this);
		var sections = obj.find(' > li');
		var subnavs = sections.find('> ul');
		var a = 0;

		var deviceAgent = navigator.userAgent.toLowerCase();
		//var agentID = deviceAgent.match(/(iphone|ipod|ipad|android)/);
		var pattern = /iphone|ipod|ipad|android/;
		var agentID = pattern.test(deviceAgent);

		subnavs.addClass(options.offClass);
		obj.parent().parent().css('position','relative');
		obj.positionNav();

		//Gestion ouverture sous-menu
		sections.each(function(){
			var section = $(this);
			var subMenu = section.find('> ul');
			var liens = section.find("a, span");

			//POSITION SUBMENU
			/*
			var subMenuContainer = section.find('> .meganav-wrapper');
			var subMenuContainerW = subMenuContainer.outerWidth()
			if ((section.offset().left + subMenuContainerW) > documentW ){
				subMenuContainer.css('left', documentW - (section.offset().left + subMenuContainerW) - 10 );
			}*/

			if(!agentID){
				liens.bind("focus", function() {
					sections.not(section).removeClass(options.activeClass);
					subnavs.not(subMenu).addClass(options.offClass);
					section.addClass(options.activeClass);
					subMenu.removeClass(options.offClass);
					window.clearTimeout(a);
					$(this).removeClass("click");
					//b.not(g).hide();
					//g.show()
				});
				liens.bind("blur", function() {
						a = window.setTimeout(function() {
							section.removeClass(options.activeClass);
							subMenu.addClass(options.offClass);
						}, options.timeOut);
						$(this).removeClass("click");
				});
				section.bind("mouseover", function() {
					sections.not(section).removeClass(options.activeClass);
					subnavs.not(subMenu).addClass(options.offClass);
					section.addClass(options.activeClass);
					subMenu.removeClass(options.offClass);
					window.clearTimeout(a);
					$(this).find('> a').removeClass("click");
					//b.not(g).hide();
					//g.show()
				});
				section.bind("mouseleave", function() {
						a = window.setTimeout(function() {
							section.removeClass(options.activeClass);
							subMenu.addClass(options.offClass);
						}, options.timeOut);
						$(this).find('> a').removeClass("click");
				});
			}
			else {
				section.delegate(">a","click", function(e) {
					if( !$(this).is('span') ) {
						e.preventDefault();
						var href = $(this).attr("href");
						var target = $(this).attr("target");
						var toClick = false;

						if( $(this).next("ul").size()>0) {
							if(!$(this).hasClass("click")){
								$(this).addClass("click");
							} else {
								toClick = true;
							}
						} else {
							toClick = true;
						}
						if(toClick) {
							if(target=="_blank") {
								window.open(href);
							} else {
								document.location = href;
							}
						}
					}
				});
			}

		});

		return this;
	};

})(jQuery);


// window load
$(window).load(function(){

	//BX Slider
	//News Ticker List
	//See: http://bxslider.com/examples/custom-next-prev-selectors
	if ($('.news-ticker-wrapper .slider-list').length) {
		$('.news-ticker-wrapper .slider-list').bxSlider({
			auto: true,
			pause: 5000,
			pager:false,
			nextSelector: '.news-ticker-wrapper .slider-button-next',
			prevSelector: '.news-ticker-wrapper .slider-button-prev',
			nextText: 'Info suivante',
			prevText: 'Info précédente'
		});
	}
	//News Slider
	if ($('.news-slider-wrapper .slider-list').length) {
		if(typeof Drupal.settings.disney_carrousel !== "undefined") {
			var carrousel_auto = Drupal.settings.disney_carrousel.auto;
		} else {
			var carrousel_auto = true;
		}
		$('.news-slider-wrapper .slider-list').bxSlider({
			auto: carrousel_auto,
			pause: 5000,
			nextSelector: '.news-slider-wrapper .slider-button-next',
			prevSelector: '.news-slider-wrapper .slider-button-prev',
			pagerSelector: '.news-slider-wrapper .slider-pager',
			nextText: 'Actualité suivante',
			prevText: 'Actualité précédente'
		});
	}

	// animating image loading from slider thumbnails
	$('.classified-ad-current-display .inner-pad .nav a').bind("click", function(event) {
				event.preventDefault();
				var imagette = $(this).attr("href");
				$('.classified-ad-current-display .figure>img').fadeTo('slow', 0.1, function() {
					$(this).attr('src', imagette ).fadeTo('slow', 1);
				}).removeAttr('height');
	});

	// The slider being synced must be initialized first
  //$('.rtf-slider-wrapper .thumb-pager').flexslider({
//    animation: "slide",
//    controlNav: false,
//    animationLoop: false,
//    slideshow: false,
//    itemWidth: 118,
//    itemMargin: 5,
//    asNavFor: '.rtf-slider-wrapper .rtf-slider-wrapper'
//  });
//
//  $('.rtf-slider-wrapper .slider-list ul').flexslider({
//    animation: "slide",
//    controlNav: false,
//    animationLoop: false,
//    slideshow: false,
//    sync: ".rtf-slider-wrapper .thumb-pager"
//  });


	//
});

// End window load


// window resize
$(window).resize(function() {
	$("#nav-primary, #nav-favorite").positionNav();
});
// End window resize

// User menu

// Media: action to perform when user clicks on Reset button
function media_reset(event) {
  event.preventDefault();
  location.replace(window.location.pathname);  // reload the url while removing all which comes after ?
  return false;
}
// Media: action to perform when user chooses a different number of items per page
function media_reset_pager(items_per_page) {
  // no query string? it's simple
  if (!window.location.search) {
    location.replace(window.location.pathname + '?items_per_page='+items_per_page);
    return false;
  }
  url=replaceQueryString(window.location.href, 'items_per_page', items_per_page);
  // force to display the first page
  url=replaceQueryString(url, 'page', '0');
  location.replace(url);  // reload the url
  return false;
}
// Helper: replace a parameter in query string
function replaceQueryString(url,param,value) {
    var re = new RegExp("([?|&])" + param + "=.*?(&|$)","i");
    if (url.match(re))
        return url.replace(re,'$1' + param + "=" + value + '$2');
    else
        return url + '&' + param + "=" + value;
}
// Media: Launch Slideshow
function media_slideshow() {
  $(".album-dataitem-hidden .album-dataitem").first().find('li a').click();
  return false;
}

// Create a selector external with jquery to get the external link
$.expr[':'].external = function(obj){
    return !obj.href.match(/^mailto\:/)
           && (obj.hostname != location.hostname)
           && !obj.href.match(/^javascript\:/)
           && !obj.href.match(/^$/)
};

$(document).ready( function() {
  // Add target="_blank" to all the external link
  $('a:external').attr('target', '_blank');

  // Put the placeholder
  $('input, textarea').placeholder();
});
