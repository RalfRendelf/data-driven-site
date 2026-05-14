class MyClass : public QObject {
    Q_OBJECT
    // Объявление свойства: имя "value", тип int.
    // Указываем функции для чтения, записи и сигнал об изменении.
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    int value() const { return m_value; } // Геттер
    void setValue(int value) {            // Сеттер
        if (m_value == value) return;     // Проверка на изменение
        m_value = value;
        emit valueChanged(m_value);       // Уведомляем систему об изменении
    }

signals:
    void valueChanged(int newValue);      // Сигнал уведомления

private:
    int m_value;
};

/* 
  ЧТО ЭТО И ЗАЧЕМ НУЖНО:

  1. Взаимодействие с QML: 
     Только поля, объявленные через Q_PROPERTY, можно напрямую читать 
     и менять из интерфейса на QML.

  2. Механизм уведомлений (Binding): 
     Благодаря NOTIFY другие объекты могут автоматически "узнавать", 
     что значение изменилось, и обновлять свою логику или графику.

  3. Универсальный доступ: 
     Вы можете менять это значение через `obj.setProperty("value", 10)`, 
     даже не зная типа объекта на этапе компиляции.

  4. Порядок в коде: 
     Это стандарт проектирования в Qt. Проверка `if (m_value == value)` 
     внутри сеттера предотвращает бесконечные циклы обновлений.
*/
