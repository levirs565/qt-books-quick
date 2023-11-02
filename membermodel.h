#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class MemberModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        NamaRole,
        TglLahirRole
    };

    explicit MemberModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void add(QString nama, QString tgl_lahir);
    Q_INVOKABLE void edit(QString kode, QString nama, QString tgl_lahir);
    Q_INVOKABLE void remove(QString kode);
    void refresh();
};

#endif // PENERBITMODEL_H