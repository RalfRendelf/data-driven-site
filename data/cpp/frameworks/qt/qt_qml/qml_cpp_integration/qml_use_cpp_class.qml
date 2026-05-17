import com.example 1.0

MyClass {
    id: myClass
    Component.onCompleted: {
        console.log(myClass.compute(10, 20));  // 30
    }
}
