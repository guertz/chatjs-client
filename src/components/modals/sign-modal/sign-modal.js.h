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
                        '<div class="w3-container frame-wrap"></div>' +
                    '</div>' +
                '</div>';

    
    

    this.destroy = function () {
        // remove dom reference
    }

    this.create = function() {
        // if dom not exist
        console.log("PROVA LOG#############");
        document.body.appendChild(node);
        window.getFirst(node, "div.frame-wrap").innerHTML 
            = "<iframe src='" + "http://" + window.getAppUrl() + "/users/form" + "'/></iframe>";
    }();
 
    window.modals['SignModal'] = this;
    
}();
)";