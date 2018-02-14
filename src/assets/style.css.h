/**
 * @brief Stile CSS Personalizzato
 * @file style.css.h
 */

/** Stile CSS Personalizzato */
const std::string _src_assets_style_css = R"(
.dropdown {
    position: relative;
    display: inline-block;
}

.dropdown-content {
    display: none;
    position: absolute;
    background-color: #f9f9f9;
    min-width: 160px;
    box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
    padding: 12px 16px;
    z-index: 1;
}

.dropdown:hover .dropdown-content {
    display: block;
}
.w3-grey.custom{
    background-color:  #ededee !important;
}

.hide{
    display: none;
}

.w3-right-align-content {
    float: right;
}
.form-wrap {
    position: fixed;
    width: 100%;
    left: 0px;
    bottom: 0px;
}

/* Chat containers */
.msg-bubble {
    border: 2px solid #dedede;
    background-color: #f1f1f1;
    border-radius: 5px;
    padding: 10px;
    margin: 10px 0;
}

/* Darker chat container */
.opponent {
    border-color: #ccc;
    background-color: #ddd;
}

/* Clear floats */
.msg-bubble::after {
    content: '';
    clear: both;
    display: table;
}

/* Style images */
.msg-bubble img {
    float: left;
    max-width: 60px;
    width: 100%;
    margin-right: 20px;
    border-radius: 50%;
}

.msg-bubble.opponent img {
    float: right;
    margin-left: 20px;
    margin-right:0;
}

/* Style time text */
.msg-bubble .time {
    float: right;
    color: #aaa;
}

/* Style time text */
.msg-bubble.opponent .time {
    float: left;
    color: #999;
}
#snackbar {
    visibility: hidden; 
    min-width: 250px;
    margin-left: -125px;
    background-color: #333; 
    color: #fff;
    text-align: center; 
    border-radius: 2px; 
    padding: 16px;
    position: fixed; 
    z-index: 1; 
    left: 50%; 
    bottom: 30px; 
}

#snackbar.show {
    visibility: visible; 
    -webkit-animation: fadein 0.5s, fadeout 0.5s 2.5s;
    animation: fadein 0.5s, fadeout 0.5s 2.5s;
}

@-webkit-keyframes fadein {
    from {bottom: 0; opacity: 0;} 
    to {bottom: 30px; opacity: 1;}
}

@keyframes fadein {
    from {bottom: 0; opacity: 0;}
    to {bottom: 30px; opacity: 1;}
}

@-webkit-keyframes fadeout {
    from {bottom: 30px; opacity: 1;} 
    to {bottom: 0; opacity: 0;}
}

@keyframes fadeout {
    from {bottom: 30px; opacity: 1;}
    to {bottom: 0; opacity: 0;}
}
)";
