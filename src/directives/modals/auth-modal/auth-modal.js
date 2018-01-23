const AuthModalFactory = function(){

    const domRef = "auth-modal";

    var node = document.createElement("div");
      node.innerHTML = 
        '<div id="'+ domRef + '" class="w3-modal">' +
            '<div class="w3-modal-content">' +
                '<div class="w3-container">' +
                    '<br/>' +
                    '<form class="w3-container user-form">' +
                
                        '<label>Identificativo Utente</label>' +
                        '<input class="w3-input can-disable userid" type="text">' +

                        '<br/>' +
                        '<button type="submit" class="w3-button w3-teal can-disable">Entra</button>'+
                    '</form>'+
                '</div>' +
            '</div>' +
        '</div>';

    var setDisabled = function(state) {
        window.forAll(node, ".can-disable", function(node){
            node.disabled = !!state;
        })
    }

    var submitEvent = function(event) {
        event.preventDefault();
        setDisabled(true);

        const val = window.getFirst(node, "input.userid").value;
        window.external.invoke_(JSON.stringify(
            {
                fn: 'Modal::AuthModal::Submit', 
                params: {
                    'type': 'login',
                    'user': val
                }
            }
        ));
    }

    this.reset = function(){
        setDisabled(false);
    }

    this.showErrors = function() {
        alert("Controlla le credenziali inserite");
    }

    this.destroy = function() {
        window.unsubscribeTo(window.getFirst(node, "form"), "submit", submitEvent);  
        // window.getFirst(document, "#"+domRef).parent.innerHTML = "";
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);
        window.subscribeTo(window.getFirst(node, "form"), "submit", submitEvent);
    }(); // calling itself
    

    window.modals["AuthModal"] = this;

}(); // calling itself




