// TODO remember
var ChatHelper  = require('./chat-helper/chat-helper.js')(window);

var Chat = require('./chat-node.js');

var ChatList = function(global){

    var __t = document.createElement('ul');
        __t.setAttribute('class','w3-ul');

    var _reference = document.querySelector("#chat-list-ref");
        _reference.appendChild(__t);

    var selectAUser = function(chatID){
        return function(e){
            window.external.invoke_(JSON.stringify({fn: 'ChatList::UserSelected', params: { ref: chatID}}));
        }
    };

    // public methods
    // check in c++ not duplicated chat
    this.updateText = function(data){

        // check json ok
        var item = JSON.parse(data);

        _reference.firstChild.innerHTML = "";

        // every refetch remember to destroy all
        for(var i=0; i<item.length; i++){
            Chat.createNode(global, { user: item[i].from, reference: item[i].reference }, _reference.firstChild, selectAUser);
        }
    };



    // registering component globally
    //      and exposing child methods
    window.components.ChatList = {
        updateText: this.updateText
    };

};

module.exports = ChatList;