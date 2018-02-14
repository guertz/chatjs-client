/**
 * @brief Componente Javascript modals.h
 * @file modals.js.h
 */

/** Componente Javascript modals.h */
const std::string _src_components_modal_modal_js = R"(
window.modals = {};

window.showModal = function(modalId){
    document.getElementById(modalId).style.display='block';
}

window.hideModal = function(modalId){
    document.getElementById(modalId).style.display='none';
}
)";