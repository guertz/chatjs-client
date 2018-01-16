var Message = require('./message');

var ChatDetails = function(global){

    var activeChat = false;

    var _templ = '<chat-messages>'+
                 '</chat-messages>'+
                 '<chat-form>' +
                    '<form id="chat-form" disabled=true>' +
                        '<div class="form-wrap w3-row">'+
                            '<div class="w3-col m4" style="visibility: hidden;"><p></p></div>' +
                            '<div class="w3-col w3-right" style="width: 100px">' +
                                '<button class="w3-col w3-button w3-teal" type="submit">Invia</button>' +
                            '</div>' +
                            '<div class="w3-rest" >' +
                                '<input class="w3-input" type="text" placeholder="scrivi qua il tuo messaggio" value="" />' +  
                            '</div>' +
                        '</div>' +
                    '</form>' + 
                 '</chat-form>';

    var _virtual = document.createElement('div');
        _virtual.innerHTML = _templ;


    var _reference = document.querySelector("#chat-details-ref");
        _reference.appendChild(_virtual);

    var _msg_list_ref = document.querySelectorAll("#chat-details-ref chat-messages")[0];
    var _msg_form_ref = document.querySelectorAll("#chat-details-ref form#chat-form")[0];

    this.push = function(__message) {

        var message = JSON.parse(__message);

        var domMessage = new Message(message);
        _msg_list_ref.appendChild(domMessage);
    }

    this.refreshAChat = function(__chat) {
        var chat = JSON.parse(__chat);

        _msg_list_ref.innerHTML = "";
        this.activeChat = chat._reference;

        for(var i=0; i<chat.messages.length; i++){
            this.push(JSON.stringify(chat.messages[i]));
        }
    }

    this.enableInput = function(){
        _msg_form_ref.disabled = false;
        _msg_form_ref.getElementsByClassName("w3-input")[0].setAttribute("placeholder", "Scrivi qui il tuo messaggio");
    }

    this.disableInput = function(){
        _msg_form_ref.disabled = true;
        _msg_form_ref.getElementsByClassName("w3-input")[0].setAttribute("placeholder", "Seleziona una chat per poter scrivere");
    }

    this.sendAMessage = function(event){
        event.preventDefault();

        var content = _msg_form_ref.getElementsByClassName("w3-input")[0].value;
        window.external.invoke_(JSON.stringify({fn: 'ChatDetails::Submit', params: { text: content}}));

    }


    _msg_form_ref.addEventListener('submit', this.sendAMessage);
    this.enableInput();

    window.components.ChatDetails = {
        refreshAChat: this.refreshAChat,
        push: this.push,
        enableInput: this.enableInput,
        disableInput: this.disableInput
    };

};

module.exports = ChatDetails;