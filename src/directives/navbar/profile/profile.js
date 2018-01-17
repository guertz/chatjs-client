
module.exports = function ProfileLink(global){

    var _dropdown_ref = "profile-dropdown-helper";

    var _templ = 
        '<div class="w3-dropdown-hover">' +
            '<button class="w3-button" id="profile-dropdown-text">Profilo</button>' +
            '<div class="w3-dropdown-content w3-bar-block w3-card-4" id="' + _dropdown_ref + '">' +
                '<a href="javascript:void(0)" class="w3-bar-item w3-button" id="nav-user-logout">Disconnetti</a>' +
            '</div>' +
        '</div>';
    
    var _virtual = document.createElement('div');
        _virtual.innerHTML = _templ;

    var reference = document.getElementById('nav-helper-ref');
                    reference.appendChild(_virtual);

    var node = document.getElementById("nav-user-logout");

    node.addEventListener('click',function() {
        window.external.invoke_(JSON.stringify({fn: 'Navbar::Profile::Disconnect', params: ''}));
    });

    var setText = function(username){
        document.getElementById("profile-dropdown-text").innerHTML = username;
    }

    window.navbar.profileLink.methods = {
        setText: setText
    }
};
