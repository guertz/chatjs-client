/**
 * @brief Componente Javascript toast.h
 * @file toast.js.h
 */

/** Componente Javascript toast.h */
const std::string _src_components_toast_toast_js = R"(
window.makeAToast = function(str) {

    // Get the snackbar DIV
    var x = document.getElementById("snackbar")
        x.innerText = str;

    // Add the "show" class to DIV
    x.className = "show";
    
    // After 3 seconds, remove the show class from DIV
    setTimeout(function(){ x.className = x.className.replace("show", ""); }, 3000);

}
)";