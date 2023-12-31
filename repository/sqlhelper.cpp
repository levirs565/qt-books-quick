#include "sqlhelper.h"
#include <QList>
#include <QHash>
#include <QVariant>
#include <QSqlError>
#include <QAbstractItemModel>

namespace SQLHelper {
    void applyBindMaps(QSqlQuery &query, const QHash<QString, QVariant> &binds)
    {
        QHashIterator<QString, QVariant> iterator(binds);
        while (iterator.hasNext()) {
            iterator.next();
            query.bindValue(iterator.key(), iterator.value());
        }
    }

    bool isSQLite(const QSqlDatabase& db) {
        return db.driverName() == "QSQLITE";
    }

    void initializeDatabase(QSqlDatabase &db)
    {
        QSqlQuery query(db);
        const QString autoIncrement = isSQLite(db)  ? "AUTOINCREMENT" : "AUTO_INCREMENT";
        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Kategori("
                "   kd_kategori INTEGER NOT NULL PRIMARY KEY %1,"
                "   nama_kategori VARCHAR(25) NOT NULL"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Kategori table " << query.lastError().text();
        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Penerbit("
                "   kd_penerbit INTEGER NOT NULL PRIMARY KEY %1,"
                "   nama_penerbit VARCHAR(25) NOT NULL,"
                "   alamat_penerbit VARCHAR(30) NOT NULL"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Penerbit table " << query.lastError().text();

        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Buku("
                "   kd_buku INTEGER NOT NULL PRIMARY KEY %1,"
                "   kd_kategori INTEGER NOT NULL,"
                "   kd_penerbit INTEGER NOT NULL,"
                "   judul VARCHAR(50) NOT NULL,"
                "   jumlah_hilang INTEGER NOT NULL DEFAULT 0,"
                "   penulis VARCHAR(25) NOT NULL,"
                "   tahun_terbit INTEGER NOT NULL,"
                "   FOREIGN KEY (kd_kategori)"
                "       REFERENCES Kategori(kd_kategori), "
                "   FOREIGN KEY (kd_penerbit)"
                "       REFERENCES Penerbit(kd_penerbit)"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Buku table " << query.lastError().text();

        if (!query.exec("CREATE TABLE IF NOT EXISTS User("
                        "   id_user VARCHAR(15) NOT NULL PRIMARY KEY,"
                        "   nama_depan_user VARCHAR(25) NOT NULL,"
                        "   nama_belakang_user VARCHAR(25) NOT NULL,"
                        "   role TINYINT NOT NULL,"
                        "   password_hash VARCHAR(100) NOT NULL"
                        ")"))
            qFatal() << "Cannot create User table " << query.lastError().text();

        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Detail_Pengadaan("
                "   kd_detail_pengadaan INTEGER NOT NULL PRIMARY KEY %1,"
                "   id_user VARCHAR(15) NOT NULL,"
                "   sumber VARCHAR(25) NOT NULL,"
                "   tanggal_pengadaan DATE NOT NULL,"
                "   FOREIGN KEY (id_user) "
                "       REFERENCES User(id_user)"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Detail_Pengadaan table " << query.lastError().text();

        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Pengadaan("
                "   kd_pengadaan INTEGER NOT NULL PRIMARY KEY %1,"
                "   kd_detail_pengadaan INTEGER NOT NULL,"
                "   kd_buku INTEGER NOT NULL,"
                "   jumlah_pengadaan_buku INT NOT NULL,"
                "   UNIQUE(kd_detail_pengadaan, kd_buku),"
                "   FOREIGN KEY (kd_buku)"
                "       REFERENCES Buku(kd_buku),"
                "   FOREIGN KEY (kd_detail_pengadaan)"
                "       REFERENCES Detail_Pengadaan(kd_detail_pengadaan)"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Pengadaan table " << query.lastError().text();
        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Member("
                "   kd_member INTEGER NOT NULL PRIMARY KEY %1,"
                "   nama_depan_member VARCHAR(25) NOT NULL,"
                "   nama_belakang_member VARCHAR(25) NOT NULL,"
                "   tanggal_lahir DATE NOT NULL"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Member table " << query.lastError().text();

        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Detail_Peminjaman("
                "   kd_detail_peminjaman INTEGER NOT NULL PRIMARY KEY %1,"
                "   id_user_peminjaman VARCHAR(15) NOT NULL,"
                "   id_user_pengembalian VARCHAR(15),"
                "   kd_member INTEGER NOT NULL,"
                "   tanggal_peminjaman DATE NOT NULL,"
                "   lama_peminjaman INTEGER NOT NULL,"
                "   tanggal_pengembalian DATE,"
                "   denda_terlambat_perbuku INTEGER,"
                "   FOREIGN KEY (kd_member)"
                "       REFERENCES Member(kd_member),"
                "   FOREIGN KEY (id_user_peminjaman)"
                "       REFERENCES User(id_user),"
                "   FOREIGN KEY (id_user_pengembalian)"
                "       REFERENCES User(id_user)"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Detail_Peminjaman table " << query.lastError().text();

        if (!query.exec(QStringLiteral(
                "CREATE TABLE IF NOT EXISTS Peminjaman("
                "   kd_peminjaman INTEGER NOT NULL PRIMARY KEY %1,"
                "   kd_detail_peminjaman INTEGER NOT NULL,"
                "   kd_buku INTEGER NOT NULL,"
                "   denda_tambahan INTEGER,"
                "   UNIQUE (kd_detail_peminjaman, kd_buku),"
                "   FOREIGN KEY (kd_buku)"
                "       REFERENCES Buku(kd_buku),"
                "   FOREIGN KEY (kd_detail_peminjaman)"
                "       REFERENCES Detail_Peminjaman(kd_detail_peminjaman)"
                ")"
                            ).arg(autoIncrement)))
            qFatal() << "Cannot create Peminjaman table " << query.lastError().text();

        if (!query.exec("CREATE TABLE IF NOT EXISTS Pengaturan("
                        "   pengaturan_key CHAR(20) NOT NULL PRIMARY KEY,"
                        "   pengaturan_value JSON"
                        ")"))
            qFatal() << "Cannot create Pengaturan table " << query.lastError().text();
    }

    void clearDatabase(QSqlDatabase &db)
    {
        QStringList tableList{
            "Pengaturan",
            "Peminjaman",
            "Detail_Peminjaman",
            "Member",
            "Pengadaan",
            "Detail_Pengadaan",
            "User",
            "Buku",
            "Penerbit",
            "Kategori"
        };

        QSqlQuery query;
        for (QStringList::iterator it = tableList.begin(); it != tableList.end(); it++) {
            query.prepare(QStringLiteral("DROP TABLE IF EXISTS %1").arg(*it));
            if (!query.exec()) {
                qFatal() << "Cannot drop table " << *it << " " << query.lastError().text();
            }
        }
    }

    QString createUpsertQuery(const QSqlDatabase &db, const QString &insertQuery, const QString &updateQuery, const QStringList &candidateKey)
    {
        if (isSQLite(db))
            return QStringLiteral("INSERT INTO %1 ON CONFLICT(%2) DO UPDATE SET %3")
                .arg(insertQuery, candidateKey.join(","), updateQuery);

        return QStringLiteral("INSERT INTO %1 ON DUPLICATE KEY UPDATE %2").arg(insertQuery, updateQuery);
    }

    void configureMySqlConnection(QSqlDatabase &db)
    {
        QSqlQuery query(db);

        if (!query.exec("SET sql_mode=(SELECT CONCAT(@@sql_mode,',PIPES_AS_CONCAT'))"))
            qFatal() << "Cannot enable PIPES_AS_CONCAT MySQL mode " << query.lastError().text();
    }

}
