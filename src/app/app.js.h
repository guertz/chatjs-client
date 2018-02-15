/**
 * @brief Componente Javascript app.h
 * @file app.js.h
 */

/** Componente Javascript app.h */
const std::string _src_app_app_js = R"(
// Basic inatializatios & Methods
window.components = {};

window.getAll = function(node, query) {
    return node.querySelectorAll(query);
}

window.getnth = function(node, query, nth){
    return window.getAll(node, query)[nth];
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
)";