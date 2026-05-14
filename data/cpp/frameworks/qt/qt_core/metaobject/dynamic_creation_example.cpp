QObject *obj = QMetaType::create(QMetaType::fromType<MyClass>().id());
MyClass *myObj = qobject_cast<MyClass*>(obj);
