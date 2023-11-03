import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import my.id.levirs.books

RowLayout {
    KategoriModel {
        id: kategoriModel
    }

    KategoriList {
        listModel: kategoriModel
        onAddClicked: {
            kategoriEditDialog.kategoriKode = ""
            kategoriEditDialog.kategoriJenis = ""
            kategoriEditDialog.open()
        }

        onCurrentItemDataChanged: {
            if (currentItemData == null) {
                kategoriDetailFrame.kategoriKode = ""
                kategoriDetailFrame.kategoriJenis = ""
            } else {
                kategoriDetailFrame.kategoriKode = currentItemData.kode
                kategoriDetailFrame.kategoriJenis = currentItemData.jenis
            }
        }
    }

    KategoriDetailFrame {
        id: kategoriDetailFrame
        onEditClicked: {
            kategoriEditDialog.kategoriKode = kategoriKode
            kategoriEditDialog.kategoriJenis = kategoriJenis
            kategoriEditDialog.open()
        }
        onDeleteClicked: kategoriModel.remove(kategoriKode)
    }


    KategoriEditDialog{
        id: kategoriEditDialog

        onAccepted: {
            if (kategoriKode == "")
                kategoriModel.addNew(kategoriJenis)
            else kategoriModel.edit(
                     kategoriKode,
                     kategoriJenis
                )
        }
    }
}