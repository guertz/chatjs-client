window.stylify = function(multiline, css) {
    var style = document.createElement('style');
    var head = document.head || document.getElementsByTagName('head')[0];
    style.setAttribute('type', 'text/css');
    if (style.styleSheet) {
        style.styleSheet.cssText = multiline? atob(css) : css;
    } else {
        style.appendChild(document.createTextNode( multiline? atob(css) : css));
    }
    head.appendChild(style);
}

window.consolelog = function(event, message) {
    // create a type safe method that will always pass a string!!
    window.external.invoke_(JSON.stringify(
        {
            fn: 'WebUI::Log', 
            params: { 
                attr: event,
                log_msg: message
            }
        }
    ));  
}

window.appready = function() {
    window.external.invoke_(JSON.stringify(
        {
            fn: 'App::Ready', 
            params: { 
                framework: true
            }
        }
    ));
}

/* var WebUIEventResize = function(){
    window.external.invoke_(JSON.stringify(
        {
            fn: 'WebUI::Resize', 
            params: {
                width: window.innerWidth,
                height: window.innerHeight
            }
        }
    ));
} */