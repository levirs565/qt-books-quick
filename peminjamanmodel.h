#ifndef PEMINJAMANMODEL_H
#define PEMINJAMANMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PeminjamanModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        NamaMemberRole,
        KodeMemberRole,
        TanggalRole,
        LamaRole,
        TanggalTenggatRole,
        TanggalPengembalianRole,
        SudahDikembalikanRole
    };

    explicit PeminjamanModel (QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE QString add(QString kodeMember, QDate tanggal, int lama);
    Q_INVOKABLE void update(QString kode, QString kodeMember, QDate tanggal, int lama);
    Q_INVOKABLE void remove(QString kode);
    Q_INVOKABLE void tandaiDikembalikan(QString kode, QDate tanggal, int denda);
    Q_INVOKABLE void tandaiBelumDikembalikan(QString kode);
};

#endif // PEMINJAMANMODEL_H
