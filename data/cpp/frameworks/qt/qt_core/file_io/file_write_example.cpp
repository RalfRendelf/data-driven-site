/* 
 * Метод open() принимает флаги QIODevice::OpenMode.
 * Их можно комбинировать через вертикальную черту (|).
 * 
 * ОСНОВНЫЕ ПАРАМЕТРЫ:
 * QIODevice::ReadOnly      - Открытие только для чтения.
 * QIODevice::WriteOnly     - Открытие только для записи (создаст файл, если его нет).
 * QIODevice::ReadWrite     - Чтение и запись одновременно.
 * QIODevice::Append        - Режим добавления: новые данные пишутся в конец файла.
 * QIODevice::Truncate      - Перед открытием очищает файл (старое содержимое удаляется).
 * QIODevice::Text          - Текстовый режим: преобразует символы переноса строки (CRLF <-> LF) 
 *                            под текущую ОС. Без этого флага файл открывается как бинарный.
 * QIODevice::Unbuffered    - Обход системного буфера (запись сразу на диск, медленнее).
 * QIODevice::NewOnly       - Ошибка, если файл уже существует.
 * QIODevice::ExistingOnly  - Ошибка, если файла нет.
 */

QFile file("example.txt");
if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << "Hello, world!" << Qt::endl;
    file.close();
}
