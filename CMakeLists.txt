cmake_minimum_required(VERSION 3.16)

project(qt-books-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql QuickControls2)
find_path(BOTAN_INCLUDE_DIRS "botan/build.h")
find_library(BOTAN_LIBRARY "botan-3")

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqt-books-qml
    main.cpp
)

qt_add_qml_module(appqt-books-qml
    URI qt-books-qml
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    QML_FILES kategori/KategoriScreen.qml
    SOURCES
    QML_FILES buku/BukuScreen.qml
    QML_FILES penerbit/PenerbitScreen.qml
    SOURCES
    SOURCES
    QML_FILES pengadaan/PengadaanScreen.qml
    SOURCES
    SOURCES
    SOURCES
    SOURCES
    QML_FILES member/MemberScreen.qml
    SOURCES
    QML_FILES peminjaman/PeminjamanList.qml
    QML_FILES FloatingActionButton.qml
    QML_FILES penerbit/PenerbitEditDialog.qml
    QML_FILES penerbit/PenerbitDetailFrame.qml
    QML_FILES penerbit/PenerbitList.qml
    QML_FILES kategori/KategoriEditDialog.qml
    QML_FILES kategori/KategoriDetailFrame.qml
    QML_FILES kategori/KategoriList.qml
    QML_FILES member/MemberEditDialog.qml
    QML_FILES member/MemberDetailFrame.qml
    QML_FILES member/MemberList.qml
    QML_FILES DateField.qml
    QML_FILES buku/BukuEditDialog.qml
    QML_FILES buku/BukuDetailFrame.qml
    QML_FILES buku/BukuList.qml
    QML_FILES pengadaan/PengadaanEditDialog.qml
    QML_FILES buku/BukuPilihDialog.qml
    QML_FILES pengadaan/PengadaanDetailFrame.qml
    QML_FILES pengadaan/PengadaanList.qml
    QML_FILES buku/BukuListView.qml
    QML_FILES peminjaman/PeminjamanScreen.qml
    QML_FILES peminjaman/PeminjamanEditDialog.qml
    QML_FILES peminjaman/PeminjamanDetailFrame.qml
    SOURCES repository/sqlhelper.h
    SOURCES repository/sqlhelper.cpp
    SOURCES
    SOURCES
    SOURCES
    SOURCES
    SOURCES
    RESOURCES resources.qrc
    QML_FILES SearchField.qml
    QML_FILES CardDelegate.qml
    QML_FILES AppGridView.qml
    QML_FILES BaseDetailFrame.qml
    QML_FILES ConnectionScreen.qml
    SOURCES connectionmanager.h connectionmanager.cpp
    SOURCES connectionmanager.h connectionmanager.cpp
    QML_FILES DashboardScreen.qml
    SOURCES
    QML_FILES SettingsScreen.qml
    SOURCES settingviewmodel.h settingviewmodel.cpp
    QML_FILES user/UserBuatAdminScreen.qml
    SOURCES usermanager.h usermanager.cpp
    QML_FILES user/UserLoginScreen.qml
    SOURCES
    SOURCES
    QML_FILES user/UserScreen.qml
    QML_FILES user/UserList.qml
    QML_FILES user/UserEditDialog.qml
    QML_FILES user/UserDetailFrame.qml
    QML_FILES member/MemberPilihDialog.qml
    QML_FILES peminjaman/PengembalianAddDialog.qml
    SOURCES
    SOURCES
    SOURCES
    SOURCES texthighlighter.h texthighlighter.cpp
    QML_FILES CardBackground.qml
    SOURCES peminjaman/peminjamandendacalculator.h peminjaman/peminjamandendacalculator.cpp
    SOURCES kategori/kategoriviewmodel.h kategori/kategoriviewmodel.cpp
    SOURCES kategori/kategorieditviewmodel.h kategori/kategorieditviewmodel.cpp
    SOURCES repository/kategorirepository.h repository/kategorirepository.cpp
    SOURCES repositorymanager.h repositorymanager.cpp
    SOURCES repository/penerbitrepository.h repository/penerbitrepository.cpp
    SOURCES repository/penerbitrepository.h repository/penerbitrepository.cpp
    SOURCES penerbit/penerbitviewmodel.h penerbit/penerbitviewmodel.cpp
    SOURCES textfielddata.h textfielddata.cpp
    SOURCES penerbit/penerbiteditviewmodel.h penerbit/penerbiteditviewmodel.cpp
    QML_FILES AppTextField.qml
    SOURCES buku/bukuviewmodel.h buku/bukuviewmodel.cpp
    SOURCES repository/bukurepository.h repository/bukurepository.cpp
    SOURCES repository/peminjamanrepository.h repository/peminjamanrepository.cpp
    SOURCES repository/pengadaanrepository.h repository/pengadaanrepository.cpp
    SOURCES buku/bukueditviewmodel.h buku/bukueditviewmodel.cpp
    SOURCES basefielddata.h basefielddata.cpp
    SOURCES combofielddata.h combofielddata.cpp
    QML_FILES AppComboField.qml
    SOURCES pengadaan/pengadaanviewmodel.h pengadaan/pengadaanviewmodel.cpp
    SOURCES pengadaan/pengadaaneditviewmodel.h pengadaan/pengadaaneditviewmodel.cpp
    SOURCES buku/bukupilihviewmodel.h buku/bukupilihviewmodel.cpp
    SOURCES peminjaman/peminjamanviewmodel.h peminjaman/peminjamanviewmodel.cpp
    SOURCES peminjaman/peminjamaneditviewmodel.h peminjaman/peminjamaneditviewmodel.cpp
    SOURCES peminjaman/pengembalianviewmodel.h peminjaman/pengembalianviewmodel.cpp
    SOURCES repository/memberrepository.h repository/memberrepository.cpp
    SOURCES member/memberviewmodel.h member/memberviewmodel.cpp
    SOURCES member/membereditviewmodel.h member/membereditviewmodel.cpp
    SOURCES member/memberpilihviewmodel.h member/memberpilihviewmodel.cpp
    SOURCES repository/userrepository.h repository/userrepository.cpp
    SOURCES usecase/userusecase.h
    SOURCES usecase/userusecase.cpp
    SOURCES user/userbuatadminviewmodel.h user/userbuatadminviewmodel.cpp
    SOURCES user/userloginviewmodel.h user/userloginviewmodel.cpp
    SOURCES user/userpegawaiviewmodel.h user/userpegawaiviewmodel.cpp
    SOURCES user/userbaseeditviewmodel.h user/userbaseeditviewmodel.cpp
    SOURCES user/userpegawaieditviewmodel.h user/userpegawaieditviewmodel.cpp
    SOURCES repository/settingrepository.h repository/settingrepository.cpp
    SOURCES repository/configurationrepository.h repository/configurationrepository.cpp
    SOURCES entity/peminjaman.h
    SOURCES entity/peminjaman.cpp
    SOURCES entity/buku.h
    SOURCES entity/buku.cpp
    SOURCES entity/kategori.h
    SOURCES entity/kategori.cpp
    SOURCES entity/member.h
    SOURCES entity/member.cpp
    SOURCES entity/penerbit.h
    SOURCES entity/penerbit.cpp
    SOURCES entity/pengadaan.h
    SOURCES entity/pengadaan.cpp
    SOURCES entity/user.h
    SOURCES entity/user.cpp
    QML_FILES
    QML_FILES AppSpinField.qml
    SOURCES
    SOURCES scopedobjectlist.h
    QML_FILES SplashScreen.qml
    QML_FILES buku/BukuFilter.qml
    QML_FILES AboutScreen.qml
    QML_FILES AboutItemDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt-books-qml PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt-books-qml
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appqt-books-qml PRIVATE
    ${BOTAN_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/buku"
    "${CMAKE_CURRENT_SOURCE_DIR}/kategori"
    "${CMAKE_CURRENT_SOURCE_DIR}/member"
    "${CMAKE_CURRENT_SOURCE_DIR}/peminjaman"
    "${CMAKE_CURRENT_SOURCE_DIR}/penerbit"
    "${CMAKE_CURRENT_SOURCE_DIR}/pengadaan"
    "${CMAKE_CURRENT_SOURCE_DIR}/user")
target_link_libraries(appqt-books-qml
    PRIVATE Qt6::Quick Qt6::Sql Qt6::QuickControls2 ${BOTAN_LIBRARY}
)

include(GNUInstallDirs)
install(TARGETS appqt-books-qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
