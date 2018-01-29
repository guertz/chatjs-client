const ChatListNode = function (avatarChat) {

    var node = document.createElement("li");
        node.className = "w3-bar"

        // XSS
        node.innerHTML = 
            '<img src="' + avatarChat.user.image + '" class="w3-bar-item w3-circle" style="width:85px">'+
            '<div class="w3-bar-item">'+
                '<span class="w3-large">' + avatarChat.user.name + '</span><br>'+
                '<span>' + "..." + '</span>'+
            '</div>';

    // callback

    return node;
}

const ChatList = function(){

    var node = document.createElement("div");
        node.innerHTML = 
            '<chat-helper>' +
                '<ul class="w3-ul">' +
                    '<div id="templ-chat-new">' +
                        '<li class="w3-bar w3-teal" id="chat-helper-ref-new">' +
                            '<div class="w3-bar-item w3-padding-small">' +
                                '<span class="w3-xlarge w3-text-sand">' +
                                    '<i class="fa fa-plus-circle" aria-hidden="true"></i>' +
                                    ' Inizia una chat' +
                                '</span>' +
                            '</div>' + 
                        '</li>' +
                    '</div>' +
                '</ul>' +
            '</chat-helper>' +
            '<chats-wrapper>' +
                '<ul class="w3-ul">' +
                '</ul>' +
            '</chats-wrapper>';

    // Dom reference ok?
    // 
    // TODO: handle click + destroy
    const chatHelper = { 
        ref:  window.getFirst(node, "chat-helper"),
        newChat: {
            ref: window.getFirst(node, "chat-helper #chat-helper-ref-new"),
            handleClick: function() {
                window.external.invoke_(JSON.stringify(
                    {
                        fn: 'ChatList::NewChat', 
                        params: { }
                    }
                ));
            }
        }
    };

    const chatsWrapper = {
        ref: window.getFirst(node, "chats-wrapper"),
        list: window.getFirst(node, "chats-wrapper ul"),
        currentEvents: [],
        populateChat: function(_chats) {

            var currentIndex = 0;

            window.forAll(chatsWrapper.list, "li", function(item){
                if(currentIndex < chatsWrapper.currentEvents.length){
                    window.unsubscribeTo(item, "click", chatsWrapper.currentEvents[currentIndex])
                    currentIndex++;
                }
            });
    
            chatsWrapper.currentEvents = [];
            chatsWrapper.list.innerHTML = "";

            var chats = JSON.parse(_chats);

            for(var index=0; index<chats.length; index++){
                var chatListNode = new ChatListNode( { user: chats[index].from, reference: chats[index].reference } );

                    chatsWrapper.list.appendChild(chatListNode);
                
                var handleMethod = chatsWrapper.handleClick(chats[index].reference),
                    domEl = window.getnth(chatsWrapper.list, "li", index);

                    window.subscribeTo(domEl, "click", handleMethod);
                    chatsWrapper.currentEvents.push(handleMethod);
            }
        },
        handleClick: function(chatId) {

            return function() {
                window.external.invoke_(JSON.stringify(
                    {
                        fn: 'ChatList::UserSelected', 
                        params: { 
                            ref: chatId
                        }
                    }
                ));
            }

        }
    };
    
    this.populateChatList = chatsWrapper.populateChat;

    this.destroy = function () {
        // remove events + dom
    }

    this.create = function() {
        // if dom not exist
        window.getFirst(document, "chat-list")
              .appendChild(node);

        window.subscribeTo(chatHelper.newChat.ref, "click", chatHelper.newChat.handleClick);
    }(); // calling itself
 
    window.components['ChatList'] = this;
}();