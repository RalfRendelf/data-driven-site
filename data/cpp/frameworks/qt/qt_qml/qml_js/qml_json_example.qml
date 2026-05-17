Item {
    Component.onCompleted: {
        var data = { name: "Alice", age: 30 };
        var json = JSON.stringify(data);
        console.log(json);  // {"name":"Alice","age":30}

        var parsed = JSON.parse(json);
        console.log(parsed.name);  // "Alice"
    }
}
