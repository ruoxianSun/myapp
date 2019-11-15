
window.onload = function () {
    const divRenderer = document.createElement('image');
    document.body.appendChild(divRenderer);

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
    }
    socket.onmessage = function (ev) {
        if (ev.data instanceof Blob) {
            var reader = new FileReader();
            reader.onload = () => {
                divRenderer.src = reader.result;
                //var img = new Image();
                //img.src = reader.result;
                //var ctx = divRenderer.getContext('2d');
                //ctx.drawImage(img, 0, 0);
            };
            reader.readAsDataURL(ev.data);
        }
        else {
            console.log("onmessage: ", ev.data);
            var obj = JSON.parse(ev.data);
            if (obj.format === "png") {
                var imguri = "data:image/png;base64," + obj.data;
                divRenderer.src = imguri;
                //var img = new Image();
                //img.src = imguri;
                //var ctx = divRenderer.getContext('2d');
                //ctx.drawImage(img, 0, 0);
            }
        }
    }
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
    }
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
        //console.log("onmousemove ",content);
        sendJson(content);
    }
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
    }
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
    }

    window.onresize=function(ev) {

        var w = document.documentElement.clientWidth;
        var h = document.documentElement.clientHeight;
        var content = {
            "uri": "app.protocol.resize",
            "width": w,
            "height": h,
        };
        console.log("onmousewheel ", w, h);
        sendJson(content);
    }
    window.oncontextmenu = function (ev) { return false; }
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
    }
    animate();
}