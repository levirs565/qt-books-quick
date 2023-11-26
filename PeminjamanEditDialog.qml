import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    id: dialog
    property PeminjamanEditViewModel viewModel: PeminjamanEditViewModel {}
    required property MemberModel memberModel

    parent: Overlay.overlay
    anchors.centerIn: parent

    modal: true
    title: "Peminjaman Baru"
    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 400
    contentHeight: editPeminjamanDialogLayout.height

    onAccepted: {
        viewModel.submit()
    }

    BukuPilihDialog {
        id: tambahPeminjamanBukuDialog
        title: "Tambah Buku ke Peminjaman"

        onAccepted: {
            dialog.viewModel.appendBuku(viewModel.selectedKode)
        }
    }

    MemberPilihDialog {
        id: memberPilihDialog
        listModel: memberModel

        onAccepted: {
            dialog.viewModel.kodeMember = currentItemData.kode
            dialog.viewModel.namaMember = currentItemData.name
        }
    }

    Flickable {
        id: editPeminjamanDialogFlickable
        anchors.fill: parent
        contentHeight: editPeminjamanDialogLayout.height

        ColumnLayout {
            id: editPeminjamanDialogLayout
            width: parent.width

            Label {
                text: "Member"
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    text: viewModel.namaMember
                    readOnly: true
                    Layout.fillWidth: true
                }

                Button {
                    onClicked: memberPilihDialog.open()
                    text: "Ganti"
                }
            }

            Label {
                text: "Tanggal Peminjaman"
            }
            DateField {
                currentDate: viewModel.tanggalPeminjaman
                id: tanggalPeminjamanTextField
                Layout.fillWidth: true
                onCurrentDateChanged: viewModel.tanggalPeminjaman = currentDate
            }

            Label {
                text: "Lama Peminjaman"
            }
            SpinBox {
                editable: true
                from: 0
                to: 1000
                value: viewModel.lamaPeminjaman
                Layout.fillWidth:true
                onValueChanged: viewModel.lamaPeminjaman = value
            }

            Label {
                text: "Buku"
            }
            Repeater {
                model: viewModel.bukuList

                delegate: Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        spacing: 8
                        anchors.fill: parent

                        Label {
                            text: modelData.judul
                        }

                        Button {
                            text: "Hapus"
                            Layout.fillWidth: true
                            onClicked: viewModel.removeBuku(index)
                        }
                    }
                }
            }

            Button {
                visible: viewModel.isBukuAvailable
                text: "Tambah Buku"
                Layout.fillWidth: true
                onClicked: {
                    tambahPeminjamanBukuDialog.viewModel.ignoredKode = viewModel.kodeBukuList
                    tambahPeminjamanBukuDialog.open()
                }
            }
        }
    }
}
