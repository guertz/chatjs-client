// crated scop
// or use strict
// (
//    ...
//)authmodal;

window.modals["auth-modal"] = function(){
    var node;
    var h = picodom.h;
    
    function render() {
        return h("h1", { class: "awesome title" }, "Prova");
    }

    // document body ok, but it should not override existing
    picodom.patch(node, (node = render()), document.getElementById("chat-details-ref"));
}

// call from c++
window.modals["auth-modal"]();


