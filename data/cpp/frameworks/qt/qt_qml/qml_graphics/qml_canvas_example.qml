Canvas {
    id: canvas
    width: 200
    height: 200

    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "blue";
        ctx.fillRect(0, 0, width, height);
        ctx.fillStyle = "white";
        ctx.font = "20px Arial";
        ctx.fillText("Hello, Canvas!", 50, 100);
    }
}
