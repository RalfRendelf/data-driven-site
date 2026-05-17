#include <QAbstractListModel>

class MyModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles { NameRole = Qt::UserRole + 1 };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return m_data.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == NameRole) {
            return m_data[index.row()];
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        return { {NameRole, "name"} };
    }

private:
    QList<QString> m_data;
};
