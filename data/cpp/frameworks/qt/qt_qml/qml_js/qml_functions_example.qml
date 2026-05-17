Item {
    function square(x) {
        return x * x;
    }

    function greet(name) {
        return "Hello, " + name;
    }

    Component.onCompleted: {
        console.log(square(5));  // 25
        console.log(greet("QML"));  // "Hello, QML"
    }
}
