window.onload = function () {
    document.body.style.padding = '0';
    document.body.style.margin = '0';
    const divRenderer = document.createElement('canvas');
    document.body.appendChild(divRenderer);

    divRenderer.style.position = 'relative';
    divRenderer.style.width = "100%";
    divRenderer.style.height = "100%";
    divRenderer.style.overflow = 'hidden';

    var baseUrl = "ws://localhost:8888";
    console.log("Connecting to WebSocket server at " + baseUrl + ".");
    var socket = new WebSocket(baseUrl);
    socket.onclose = function () {
        console.error("web channel closed");
    };
    socket.onerror = function (error) {
        console.error("web channel error: " + error);
    };
    socket.onopen = function () {
        console.log("WebSocket connected, setting up QWebChannel.");
    }
    socket.onmessage = function (ev) {
        //var obj = JSON.parse(ev.data);
        console.log("onmessage: ", ev.data);
        var obj = JSON.parse(ev.data);
        if (obj.format === "png") {
            var imguri = "data:image/png;base64," + obj.data;
            var img = new Image();
            img.src = imguri;
            var ctx = divRenderer.getContext('2d');
            ctx.drawImage(img, 0, 0);
        }
    }
    function sendJson(obj) {
        var content = JSON.stringify(obj);
        socket.send(content);
    };
    window.onmousedown = function (ev) {

        var content = {
            "uri": "app.protocol.mouseevent",
            "type": "mousedown",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        console.log("onmousedown ", content);
        sendJson(content);
    }
    window.onmousemove = function (ev) {
        var content = {
            "uri": "app.protocol.mouseevent",
            "type": "mousemove",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        //console.log("onmousemove ",content);
        //sendJson(content);
    }
    window.onmouseup = function (ev) {
        var content = {
            "uri": "app.protocol.mouseevent",
            "type": "mouseup",
            "button": ev.button,
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "modifys": ev.modifys,
        };
        //console.log("onmouseup ",content);
        sendJson(content);
    }
    window.onwheel = function (ev) {

        var content = {
            "uri": "app.protocol.mouseevent",
            "type": "mousewheel",
            "buttons": ev.buttons,
            "x": ev.x,
            "y": ev.y,
            "delat": ev.deltaY,
            "modifys": ev.modifys,
        };
        console.log("onmousewheel ", ev);
        sendJson(content);
    }
    window.onresize = function (ev) {
        var content = {
            "uri": "app.protocol.resizeevent",
            "width": window.innerWidth,
            "height": window.innerHeight,
        };
        console.log("onmousewheel ", window.innerWidth, window.innerHeight);
        sendJson(content);
    }
}