
window.onload = function () {
    const div = document.createElement('image');
    document.body.appendChild(div);
    document.body.style.padding = 0;
    document.body.style.margin = 0;
    div.style.width = "100 %";
    div.style.height = "100%";
    div.style.position = "fixed";
    div.style.overflowY = "scroll";

    var baseUrl = "ws://localhost:8888";
    console.log("Connecting to WebSocket server at " + baseUrl + ".");
    var socket = new WebSocket(baseUrl);
    socket.binaryType = "blob";
    socket.onclose = function () {
        console.error("web channel closed");
    };
    socket.onerror = function (error) {
        console.error("web channel error: " + error);
    };
    socket.onopen = function () {
        console.log("WebSocket connected, setting up QWebChannel.");
    };
    socket.onmessage = function (ev) {
        if (ev.data instanceof Blob) {
            var reader = new FileReader();
            reader.onload = () => {
                div.src = reader.result;
            };
            reader.readAsDataURL(ev.data);
        }
        else {
            console.log("onmessage: ", ev.data);
            var obj = JSON.parse(ev.data);
            if (obj.format === "png") {
                div.src = "data:image/png;base64," + obj.data;
            }
        }
    
    };
    function sendJson(obj) {
        var content = JSON.stringify(obj);
        socket.send(content);
    };
    window.onmousedown = function (ev) {

        var content = {
            "uri": "app.protocol.mouse",
            "type": "mousedown",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        console.log("onmousedown ", content);
        sendJson(content);
    
    };
    window.onmousemove = function (ev) {
        var content = {
            "uri": "app.protocol.mouse",
            "type": "mousemove",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        sendJson(content);
    
    };
    window.onmouseup = function (ev) {
        var content = {
            "uri": "app.protocol.mouse",
            "type": "mouseup",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        //console.log("onmouseup ",content);
        sendJson(content);
    };
    window.onwheel = function (ev) {

        var content = {
            "uri": "app.protocol.mouse",
            "type": "mousewheel",
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "delat": ev.deltaY,
            "modifys": ev.modifys,
        };
        console.log("onmousewheel ", ev);
        sendJson(content);
    };

    window.onresize = function (ev) {

        var w = document.documentElement.clientWidth;
        var h = document.documentElement.clientHeight;
        var content = {
            "uri": "app.protocol.resize",
            "width": w,
            "height": h,
        };
        console.log("onmousewheel ", w, h);
        sendJson(content);
    };
    window.onkeydown = function (ev) {
        var content = {
            "uri": "app.protocol.key",
            "type": "down",
            "code": ev.keyCode,
            "char": ev.charCode,
            "ctrl": ev.ctrlKey,
            "alt": ev.altKey,
            "shift":ev.shiftKey,
        };
        console.log("onkeydown ", content);
        sendJson(content);
    };
    window.onkeyup = function (ev) {
        var content = {
            "uri": "app.protocol.key",
            "type": "up",
            "code": ev.keyCode,
            "char": ev.charCode,
            "ctrl": ev.ctrlKey,
            "alt": ev.altKey,
            "shift": ev.shiftKey,
        };
        console.log("onkeyup ", content);
        sendJson(content);
    };
    window.oncontextmenu = function (ev) { return false; };
    window.ondragstart = function (ev) { return false; };
    var cnt = 0;
    function animate() {
        requestAnimationFrame(animate);
        if (cnt < 5) {
            cnt++;
            return;
        }
        cnt = 0;
        var content = {
            "uri": "app.protocol.draw",
        };
        sendJson(content);
    };
    animate();
}