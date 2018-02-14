/**
 * @brief Componente Javascript chat-details.h
 * @file chat-details.js.h
 */

/** Componente Javascript chat-details.h */
const std::string _src_components_chat_details_chat_details_js = R"(
const BubbleDom = function(message){

    var bubbleDom = document.createElement('div');
                    bubbleDom.className = "msg-bubble " + ((!message.isMe)? "opponent" : "");

                    bubbleDom.innerHTML = '<img src="' + message.avatar.image + '" alt="Avatar">' +
                                          '<p class="text"></p>' +
                                          '<span class="time"></span>';

                    window.getFirst(bubbleDom, "p.text").innerText = message.text;
                    window.getFirst(bubbleDom, "span.time").innerText = message.time;

    return bubbleDom;
}

const ChatDetailsFactory = function(){

    const btnSendText          = "Invia";
    const inputPlaceholderText = [ "Seleziona una chat", "Scrivi qua il messaggio" ];
    
    var node = document.createElement("div");
        node.innerHTML = 
            '<chat-messages>'+
            '</chat-messages>'+
            '<chat-form>' +
                '<form id="chat-form" disabled=true>' +
                    '<div class="form-wrap w3-row">'+
                        '<div class="w3-col m4" style="visibility: hidden;"><p></p></div>' +
                        '<div class="w3-col w3-right" style="width: 100px">' +
                            '<button class="w3-col w3-button w3-teal" type="submit">' + btnSendText + '</button>' +
                        '</div>' +
                        '<div class="w3-rest" >' +
                            '<input class="w3-input" type="text" placeholder="' + inputPlaceholderText[0] + '" value="" />' +  
                        '</div>' +
                    '</div>' +
                '</form>' + 
            '</chat-form>';

    const chatTreeRef = window.getFirst(node, "chat-messages");
    const formRef     = window.getFirst(node, "form#chat-form");

    var handleSubmit = function(event) {
        event.preventDefault();

        window.external.invoke(JSON.stringify(
            {
                fn: 'ChatDetails::Submit', 
                params: { 
                    text: window.getFirst(formRef, ".w3-input").value
                }
            }
        ));
    }

    this.populateChatDetails = function(_chat) {

        chatTreeRef.innerHTML = "";
        var   chat        = JSON.parse(_chat);

        for(var i=0; i<chat.messages.length; i++){
           var domItem  = new BubbleDom(chat.messages[i]);
               chatTreeRef.appendChild(domItem);
        }
    }

    this.enable = function(){
        formRef.disabled = false;
        window.getFirst(formRef, ".w3-input")
            .setAttribute("placeholder", inputPlaceholderText[1]);
    }

    this.disable = function(){
        formRef.disable = true;
        window.getFirst(formRef, ".w3-input")
            .setAttribute("placeholder", inputPlaceholderText[0]);
    }

    this.destroy = function () {
        // remove event + dom
    }

    this.create = function() {
        // if dom not exist
        window.getFirst(document, "chat-details")
              .appendChild(node);

        window.subscribeTo(formRef, "submit", handleSubmit);
    }(); // calling itself
 
    window.components['ChatDetails'] = this;

}();
)";