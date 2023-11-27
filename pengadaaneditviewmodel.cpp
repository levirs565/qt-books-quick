#include "pengadaaneditviewmodel.h"
#include "repositorymanager.h"
#include "repository/bukurepository.h"

PengadaanEditViewModel::PengadaanEditViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPengadaan()},
    mSumberField{new TextFieldData(this)},
    mKode{-1}
{
    mSumberField->setName("Sumber");
    mSumberField->setMaxLength(25);

    connect(mSumberField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void PengadaanEditViewModel::configure(int kode)
{
    mKode = kode;
    PengadaanData* data = mRepository->get(kode);
    mSumberField->setValue(data->sumber());
    mTanggal = data->tanggalPengadaan();
    if (!mTanggal.isValid()) mTanggal = QDate::currentDate();
    delete data;

    mBukuList = mRepository->getBukuList(kode);

    refreshBukuAvailable();

    emit tanggalChanged();
    emit bukuListChanged();
}

TextFieldData *PengadaanEditViewModel::sumberField() const
{
    return mSumberField;
}

QList<PengadaanBukuData *> PengadaanEditViewModel::bukuList() const
{
    return mBukuList;
}

bool PengadaanEditViewModel::isBukuAvailable() const
{
    return mIsBukuAvailable;
}

void PengadaanEditViewModel::appendBuku(int kode)
{
    if (kode == -1) {
        qWarning() << "Inserting buku with kode -1 is ignored";
        return;
    }

    BukuData* buku = RepositoryManager::getInstance()->getBuku()->getBukuData(kode);
    PengadaanBukuData* data = new PengadaanBukuData(buku->kode(), 0, buku->judul());
    delete buku;

    mBukuList.append(data);

    refreshBukuAvailable();
    emit bukuListChanged();
}

void PengadaanEditViewModel::removeBuku(int index)
{
    delete mBukuList[index];
    mBukuList.remove(index);

    refreshBukuAvailable();
    emit bukuListChanged();
}

QList<int> PengadaanEditViewModel::kodeBukuList() const
{
    return mKodeBukuList;
}

QDate PengadaanEditViewModel::tanggal() const
{
    return mTanggal;
}

void PengadaanEditViewModel::setTanggal(const QDate &newTanggal)
{
    if (mTanggal == newTanggal)
        return;
    mTanggal = newTanggal;
    emit tanggalChanged();
}


void PengadaanEditViewModel::refreshBukuAvailable()
{
    mKodeBukuList.clear();
    for (int i = 0; i < mBukuList.length(); i++) {
        mKodeBukuList.append(mBukuList.at(i)->kodeBuku());
    }
    emit kodeBukuListChanged();


    mIsBukuAvailable =  RepositoryManager::getInstance()->getBuku()->isBookAvailable(mKodeBukuList);
    emit isBukuAvailableChanged();
}

bool PengadaanEditViewModel::isValid() const
{
    return mSumberField->isValid();
}

void PengadaanEditViewModel::submit()
{
    int newKode = mKode;
    if (newKode == -1) newKode = mRepository->add(sumberField()->value(), mTanggal);
    else mRepository->update(newKode, sumberField()->value());

    mRepository->updateAllBuku(newKode, mBukuList);
}