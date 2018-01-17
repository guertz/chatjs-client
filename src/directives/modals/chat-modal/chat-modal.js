// if(!document.getElementById(modalRef))
module.exports = function ChatModal(global){
    
    var modalRef = "chat-modal";

    var _templ = '<div id="'+ modalRef + '" class="w3-modal">' +
                    '<div class="w3-modal-content">' +
                        '<div class="w3-container">' +
                            '<span class="w3-button w3-display-topright close-modal">&times</span>' +
                            '<br/>' +
                            '<div class="content w3-row users-list-available">' +
                            '</div>' +
                        '</div>' +
                    '</div>' +
                '</div>';

    // TODO: distribute this callback structure to safely store parameters
    //       without pushing them to DOM
    var handleClick = function(userId) {
        return function(){
            window.external.invoke_(JSON.stringify(
                {
                    fn: 'Modal::ChatModal::NewChatOpen', 
                    params: { 
                        user: { 
                            _id: userId 
                        }
                    }
                }
            ));
        }
    }
    
    var cleanListen = function(wrapper) {
        var nodes = document.querySelectorAll("#"+modalRef+" .users-selector");

        for(var i = 0; i<nodes.length; i++){
            // nodes[i].removeEventListener('click');
        }

        if(wrapper){
            wrapper.innerHTML = "";
        }
    }

    var populate = function(items) {
        var wrapper = document.querySelectorAll("#"+modalRef+" .users-list-available")[0],
            users   = JSON.parse(items); /**< Formato del tipo:
                                           *  @include sockets/users-stream/refresh-users.json
                                           */
        cleanListen(wrapper);

        for(var index = 0; index < users.length; index++) {

            var nodeId = "user-node-"+index;

            var userNode = document.createElement('div');
                userNode.className += " users-selector w3-col s4 m3 l2";
                userNode.id = nodeId;

                // TODO: Optimize UI/UX
                userNode.innerHTML = '<img src="' + users[index].image + '" class="w3-bar-item w3-circle" style="width:55px">' +
                                     '<p class="descriptor">'+
                                        users[index].name +
                                     '</p>';

            wrapper.appendChild(userNode);

            var copiedNode = document.getElementById(nodeId);
                copiedNode.addEventListener('click', handleClick(users[index]._id));

        }


    }

    // var destroy = function() {
    //     if(modal){
    //         modal.parentNode.removeChild(modalRef);
    //     }
    // }  

 
    var _virtual = document.createElement('div');
        _virtual.innerHTML = _templ;

    document.body.appendChild(_virtual);

    //detach listener on destroy
    document.querySelectorAll("#"+modalRef+" .close-modal")[0].addEventListener('click', function(){
        window.hideModal(modalRef); // TODO: Should bind to c++ event
    });

    window.modals['ChatModal'] = {
        methods: {
            populate: populate
        }
    }
};