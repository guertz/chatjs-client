const ChatModalFactory = function() {
    const domRef = "chat-modal";
    var currentEvents = [];

    var node = document.createElement("div");
        node.innerHTML = 
            '<div id="'+ domRef + '" class="w3-modal">' +
                    '<div class="w3-modal-content">' +
                        '<div class="w3-container">' +
                            '<span class="w3-button w3-display-topright close-modal">&times</span>' +
                            '<br/>' +
                            '<div class="content w3-row users-list-available">' +
                            '</div>' +
                        '</div>' +
                    '</div>' +
                '</div>';

    var hideEvent = function() {
        window.external.invoke_(JSON.stringify(
            {
                fn: 'Modal::ChatModal::Close', 
                params: { }
            }
        ));
    }

    // This is a really good trick
    var handleClick = function(userId) {
        return function(){
            window.external.invoke_(JSON.stringify(
                {
                    fn: 'Modal::ChatModal::NewChatOpen', 
                    params: { 
                        user: userId
                    }
                }
            ));
        }
    }
    
    this.populate = function(data) {

        var currentIndex = 0;

        window.forAll(node, "#"+domRef+" .uses-selector", function(item){
            if(currentIndex < currentEvents.length){
                window.unsubscribeTo(item, "click", currentEvents[currentIndex])
                currentIndex++;
            }
        });

        currentEvents = [];
        var wrapper = window.getFirst(node, ".users-list-available")
            wrapper.innerHTML = "";
        
        /** Formato del tipo:
         *  @include sockets/users-stream/refresh-users.json
         */
        var users = JSON.parse(data);

        for(var index = 0; index < users.length; index++) {

            //XSS
            var el = document.createElement('div');
                el.className += " users-selector w3-col s4 m3 l2";
                el.innerHTML = 
                    "<img src='" + users[index].image + "'  class='w3-bar-item w3-circle' style='width:55px'>" +
                    "<p class='descriptor'>" + users[index].name + "</p>"

            // its return
            wrapper.appendChild(el);
            // get last?
            var handleMethod = handleClick(users[index]._id),
                domEl = window.getnth(node, "#"+domRef+" .uses-selector", index);

                window.subscribeTo(domEl, "click", handleMethod);
                currentEvents.push(handleMethod);

        }


    }

    this.destroy = function () {
        // remove events + close event
        // remove dom reference
        // close socket stream
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);
        window.subscribeTo(window.getFirst(node, ".close-modal"), "click", hideEvent);
    }(); // calling itself
 
    window.modals['ChatModal'] = this;
    
}(); // calling itself