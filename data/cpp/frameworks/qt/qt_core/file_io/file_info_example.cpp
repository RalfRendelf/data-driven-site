QFileInfo fileInfo("example.txt");
qDebug() << "Имя файла:" << fileInfo.fileName();
qDebug() << "Размер:" << fileInfo.size();
qDebug() << "Дата модификации:" << fileInfo.lastModified();
