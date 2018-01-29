window.modals = {};

window.showModal = function(modalId){
    document.getElementById(modalId).style.display='block';
    window.consolelog("SHOW Modal", modalId);
}

window.hideModal = function(modalId){
    document.getElementById(modalId).style.display='none'
    window.consolelog("HIDE Modal", modalId);
}