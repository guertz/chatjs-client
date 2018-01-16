//Otherwise function and prototypes
var createChatNode = function(global, chat, reference, _callback){

    var _templ = 
        '<div id="templ-chat-list">'+
            '<li class="w3-bar">'+
                '<img src="img/yuna.jpg" class="w3-bar-item w3-circle" style="width:85px">'+
                '<div class="w3-bar-item">'+
                    '<span class="w3-large"></span><br>'+
                    '<span></span>'+
                '</div>'+
            '</li>'+
        '</div>';

    var _virtual = document.createElement('div');
        _virtual.innerHTML = _templ;

    var templ     = _virtual;
    var spans     = templ.querySelectorAll("span");
    var chatName  = spans[0];
        chatName.textContent = chat.user.name;

    var chatText  = spans[1];
        chatText.textContent = "..."; 

    var chatImage = templ.querySelectorAll("img")[0];
        chatImage.setAttribute("src", chat.user.image);

    var root      = templ.querySelector('li');
        root.setAttribute("id", "chat-list-ref-"+chat.reference);

    
    reference.appendChild(templ);

    var node = document.getElementById("chat-list-ref-"+chat.reference);
        node.addEventListener('click', _callback(chat.reference));

    return node;
}

var destroyChatNode = function(ref){
    // if !node throw err
    var node = document.getElementById("chat-list-ref-"+ref);
        node.removeEventListener('click');

    return node.parentNode.removeChild(node);
}

module.exports.createNode = createChatNode;
module.exports.destroyNode = destroyChatNode;