/**
 * @brief Componente Javascript sign-modal.h
 * @file sign-modal.js.h
 */

/** Componente Javascript sign-modal.h */
const std::string _src_components_modal_sign_modal_sign_modal_js = R"(
const SignModalFactory = function() {
    const domRef = "sign-modal";

    var node = document.createElement("div");
        node.innerHTML = 
            '<div id="'+ domRef + '" class="w3-modal">' +
                    '<div class="w3-modal-content">' +
                        '<div class="w3-container frame-wrap">' +
                            '<span class="w3-button w3-display-topright close-modal">&times</span>' +
                        '</div>' +
                    '</div>' +
                '</div>';

    
    

    var hideEvent = function() {
        window.hideModal(domRef);
    }
    
    this.destroy = function () {
        // remove dom reference
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);

        // iframe ok ma faccio prima a fare input e post con libcurl
        var iframe = document.createElement("iframe");
            iframe.src = "http://" + window.getAppUrl() + "/users/form";
            iframe.style.width = "100%";
            iframe.style.height = (parseInt(window.innerHeight) - 200) + 'px';
            iframe.style.border = "0px";

        window.getFirst(node, "div.frame-wrap").appendChild(iframe);
        window.subscribeTo(window.getFirst(node, ".close-modal"), "click", hideEvent);
    }();
 
    window.modals['SignModal'] = this;
    
}();
)";