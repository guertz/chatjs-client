window.modals = {};

window.showModal = function(modalId){
    document.getElementById(modalId).style.display='block'
}

window.hideModal = function(modalId){
    document.getElementById(modalId).style.display='none'
}