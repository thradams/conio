var el = document.createElement("pre");
el.style.backgroundColor = "black";
el.style.color = "rgb(192,192,192)";
el.style.marginTop = "0px";
el.style.fontFamily = "'Lucida Console', Monaco, monospace";
var s_x = 0;
var s_y = 0;
/* Pull request test 2 */
function clrscr() {
    var temp = el.textContent.split("");
    var count = 0;
    var rows = 40;
    var cols = 80;
    for (var i = 0; i < rows; i++) {
        for (var k = 0; k < cols; k++) {
            temp[count] = " ";
            count++;
        }
        temp[count] = "\n";
        count++;
    }
    el.textContent = temp.join("");
}
function gotoxy(x, y) {
    s_x = x;
    s_y = y;
}
function cputs(text) {
    var temp = el.textContent.split("");
    for (var i = 0; i < text.length; i++) {
        if (text.charAt(i) == "\n") {
            s_y++;
            s_x = 0;
        }
        else {
            temp[81 * s_y + s_x] = text.charAt(i);
            s_x++;
        }
    }
    el.textContent = temp.join("");
}
window.onload = function () {
    document.body.appendChild(el);
    main();
};
//# sourceMappingURL=conio.js.map
