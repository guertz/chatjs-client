var NewChatHelper = require('./new-chat.js');

module.exports =  function ChatHelper(global){
    
    var __t = document.createElement('ul');
        __t.setAttribute('class','w3-ul');

    var _reference = document.querySelector("#chat-helper-ref");
        _reference.appendChild(__t);

    NewChatHelper.createNode(global, _reference.firstChild);
}
