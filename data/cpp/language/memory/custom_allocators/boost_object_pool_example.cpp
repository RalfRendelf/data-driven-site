#include <iostream>
#include <boost/pool/object_pool.hpp>

// Рекомендация: Используйте для приложений с большим количеством однотипных объектов.
class MyClass {
public:
    MyClass(int x) : value(x) {}
    void print() { std::cout << value << std::endl; }
private:
    int value;
};

int main() {
    boost::object_pool<MyClass> pool;

    // Выделение объекта из пула
    MyClass* obj = pool.malloc();
    new (obj) MyClass(42); // Размещающее new
    obj->print();

    // Освобождение объекта
    obj->~MyClass();
    pool.free(obj);

    return 0;
}
