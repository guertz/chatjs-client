var createNewChatHelper = function(global, reference){
    var _templ = 
        '<div id="templ-chat-new">' +
            '<li class="w3-bar w3-teal" id="chat-helper-ref-new">' +
                '<div class="w3-bar-item w3-padding-small">' +
                    '<span class="w3-xlarge w3-text-sand">' +
                        '<i class="fa fa-plus-circle" aria-hidden="true"></i>' +
                        ' Inizia una chat' +
                    '</span>' +
                '</div>' + 
            '</li>' +
        '</div>';
    
    var _virtual = document.createElement('div');
        _virtual.innerHTML = _templ;

    reference.appendChild(_virtual);

    var node = document.getElementById("chat-helper-ref-new");
        node.addEventListener('click',function() {
            
            // call in chat list => then => modal
            // questo binfing non è piu presente

            window.external.invoke_(JSON.stringify({fn: 'ChatList::NewChat', params: ''}));
        });

    return node;
}

var destroyNewChatHelper = function(){

    // if !node throw err
    var node = document.getElementById("chat-helper-ref-new");
        node.removeEventListener('click');

    return node.parentNode.removeChild(node);
}

module.exports.createNode = createNewChatHelper;
module.exports.destroyNode = destroyNewChatHelper;