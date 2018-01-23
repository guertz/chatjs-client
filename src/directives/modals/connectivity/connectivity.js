const ConnectivityModalFactory = function() {
    const domRef = "connectivity-modal";

    // z-index
    // error format (color red)
    var node = document.createElement("div");
        node.innerHTML = 
            '<div id="'+ domRef + '" class="w3-modal">' +
                    '<div class="w3-modal-content">' +
                        '<div class="w3-container">' +
                            '<h2>Problemi di connessione</h2>' +
                        '</div>' +
                    '</div>' +
                '</div>';

    
    

    this.destroy = function () {
        // remove dom reference
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);
    }();
 
    window.modals['ConnectivityModal'] = this;
    
};