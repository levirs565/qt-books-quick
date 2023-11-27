#include "peminjamanviewmodel.h"
#include "repositorymanager.h"

ProcessedPeminjamanData::ProcessedPeminjamanData(
    const PeminjamanData* rawData
    )
    : PeminjamanData(
        rawData->kode(),
        rawData->kodeMember(),
        rawData->namaDepanMember(),
        rawData->namaBelakangMember(),
        rawData->tanggalPeminjaman(),
        rawData->lamaPeminjaman(),
        rawData->tanggalPengembalian(),
        rawData->dendaTerlambatPerBuku())
{}


QString ProcessedPeminjamanData::namaMember() const
{
    return namaDepanMember() + " " + namaBelakangMember();
}

QDate ProcessedPeminjamanData::tenggatPengembalian() const
{
    return tanggalPeminjaman().addDays(lamaPeminjaman());
}

bool ProcessedPeminjamanData::sudahDikembalikan() const
{
    return tanggalPengembalian().isValid();
}

PeminjamanViewModel::PeminjamanViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPeminjaman()},
    mSelectedDenda{new PeminjamanDendaCalculator(this)},
    mSelectedData{nullptr}
{
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
    refresh();
}

QList<ProcessedPeminjamanData *> PeminjamanViewModel::list() const
{
    return mList;
}

QString PeminjamanViewModel::textQuery() const
{
    return mTextQuery;
}

void PeminjamanViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

PeminjamanViewModel::StatusFilter PeminjamanViewModel::statusFilter() const
{
    return mStatusFilter;
}

void PeminjamanViewModel::setStatusFilter(StatusFilter newStatusFilter)
{
    if (mStatusFilter == newStatusFilter)
        return;
    mStatusFilter = newStatusFilter;
    emit statusFilterChanged();
    refresh();
}

void PeminjamanViewModel::refresh()
{
    PeminjamanRepository::StatusFilter statusFilter;

    switch (mStatusFilter) {
    case SemuaStatus:
        statusFilter = PeminjamanRepository::SemuaStatus;
        break;
    case BelumDikembalikanStatus:
        statusFilter = PeminjamanRepository::BelumDikembalikanStatus;
        break;
    case MelewatiTenggatStatus:
        statusFilter = PeminjamanRepository::MelewatiTenggatStatus;
        break;
    case SudahDikembalikanStatus:
        statusFilter = PeminjamanRepository::SudahDikembalikanStatus;
        break;
    default:
        qWarning() << "Unrecognized status filter" << mStatusFilter;
        break;
    }

    QList<ProcessedPeminjamanData*> prevList = mList;
    QList<PeminjamanData*> rawList = mRepository->getList(statusFilter);

    mList.clear();

    for (int i = 0; i < rawList.length(); i++) {
        mList.append(new ProcessedPeminjamanData(rawList.at(i)));
    }

    emit listChanged();

    refreshSelectedItem();

    qDeleteAll(rawList.begin(), rawList.end());
    qDeleteAll(prevList);
}

PeminjamanDendaCalculator *PeminjamanViewModel::selectedDenda() const
{
    return mSelectedDenda;
}

void PeminjamanViewModel::tandaiBelumDikembalikanSelected()
{
    mRepository->tandaiBelumDikembalikan(mSelectedData->kode());
    mRepository->resetDendaBuku(mSelectedData->kode());
}

QList<PeminjamanBukuData *> PeminjamanViewModel::selectedBukuList() const
{
    return mSelectedBukuList;
}

ProcessedPeminjamanData *PeminjamanViewModel::selectedData() const
{
    return mSelectedData;
}


void PeminjamanViewModel::refreshSelectedItem()
{
    int kode = -1;
    if (mSelectedIndex >= 0 && mSelectedIndex < mList.length())
        kode = mList.at(mSelectedIndex)->kode();

    ProcessedPeminjamanData* prevData = mSelectedData;

    PeminjamanData* rawData = mRepository->get(kode);
    mSelectedData = new ProcessedPeminjamanData(rawData);
    delete rawData;

    mSelectedDenda->setDendaTerlambatPerBuku(mSelectedData->dendaTerlambatPerBuku());
    mSelectedDenda->setTenggatPengembalian(mSelectedData->tenggatPengembalian());
    mSelectedDenda->setTanggalPengembalian(mSelectedData->tanggalPengembalian());

    QList<PeminjamanBukuData*> prevBukuList = mSelectedBukuList;
    mSelectedBukuList = mRepository->getBukuList(kode);
    mSelectedDenda->setBukuList(mSelectedBukuList);
    qDeleteAll(prevBukuList.begin(), prevBukuList.end());

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
    emit selectedBukuListChanged();

    if (prevData != nullptr)
        delete prevData;
}

bool PeminjamanViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void PeminjamanViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}