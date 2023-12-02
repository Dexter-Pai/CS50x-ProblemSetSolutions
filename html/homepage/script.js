let i = 0;
let test = document.getElementById("test");
let vertical_line = document.getElementById("vertical");
const mediaQuery = window.matchMedia('(min-width: 768px)');
let cindy = document.getElementById("picture");
vertical_line.style.height = cindy.clientWidth +"px";
let sideBarr = document.getElementsByClassName("sideBar_a");
let address = document.location.href;
let imgsrc = cindy.getAttribute("src");

document.addEventListener('DOMContentLoaded', function () {
    if (imgsrc == "cindy.jpg") {
        cindy.style = "border-radius: 50%";
    } else if (imgsrc == "treats.png") {
        cindy.style = "border-radius : 50px";
    } else if (imgsrc == "none.jpg") {
        cindy.remove();
        vertical_line.remove();
        document.getElementById("imageBlock").remove();
        document.getElementById("spacer1").style. width = 0;
        document.getElementById("spacer2").style. width = "100%";
    } else {
        cindy.style = "border-radius : 50px";
    }
})
test.innerHTML = address;
test.style.visibility = "visible";

if (!mediaQuery.matches) {
    document.querySelector("#text p").style = "font-size: 14px;";
}

function sideBarOC() {
    if (i % 2 == 0) {
        openSideBar();
        i++;
    }
    else
        closeSideBar();
}

function openSideBar() {

    if (mediaQuery.matches) {
        document.getElementById("sideBar").style.width = "250px";
        document.getElementById("main").style.marginLeft = "250px";
        document.getElementById("open_sideBar").style = "transition: 0.5s; margin-left: 250px;";
    }
    else {
        document.getElementById("sideBar").style.width = "150px";
        document.getElementById("main").style.marginLeft = "150px";
        document.getElementById("open_sideBar").style = "transition: 0.5s; margin-left: 150px;";
        document.getElementById("picture").style = "transition: 0.5s; padding: 20px 20px  1px;";
        for (let i = 0; i < sideBarr.length; i++) {
            sideBarr[i].style.fontSize = "13px";
        }
    }
}

function closeSideBar() {
    document.getElementById("sideBar").style.width = "0";
    document.getElementById("main").style.marginLeft = "0";
    document.getElementById("open_sideBar").style = "transition: 0.5s; margin-left: 0;";
    document.getElementById("picture").style = "transition: 0.5s; padding: 20px;";
    i = 0;
}