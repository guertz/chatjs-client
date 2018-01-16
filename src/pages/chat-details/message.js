var Message = function(message){

    var bubbleDom = document.createElement('div');
                    bubbleDom.className = "msg-bubble " + ((!message.isMe)? "opponent" : "");

                    bubbleDom.innerHTML = '<img src="' + message.avatar + '" alt="Avatar">' +
                                              '<p class="text"></p>' +
                                          '<span class="time"></span>';

                    bubbleDom.getElementsByClassName("text")[0].innerText = message.content;
                    bubbleDom.getElementsByClassName("time")[0].innerText = message.time;

    return bubbleDom;
}

module.exports = Message;