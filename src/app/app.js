// move to appinit.js?
// Initializing Objects
window.components = {};

window.getAll = function(node, query) {
    return node.querySelectorAll(query);
}

window.getFirst = function(node, query) {
    return window.getAll(node, query)[0];
}

window.subscribeTo = function(node, listener, callback){
    node.addEventListener(listener, callback);
}

window.unsubscribeTo = function(node, listener, callback){
    node.removeEventListener(listener, callback);
}

window.forAll = function(root, query, action){
    var nodes = window.getAll(root, query);

    for(var i = 0; i<nodes.length; i++)
        action(nodes[i]);
}
