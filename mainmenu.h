#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include "QDialog"
#include "QSpinBox"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void inputBarang( QString barang, QString kode, QString stok, QString distributor, QString alamatdistrib, QString kordinat, QString deskripsi, QString hargaBeli, QString hargaJual, QString satuan, QString brand, QString model);
    void tampilBarang(QString action, QString kode);
    void getDataProduct(QString kode);
    void updateMutasi(QString idMutasi, QString jamMutasi, QString tanggalMutasi, QString bulanMutasi, QString tahunMutasi, int nominalMutasi, QString pelangganMutasi, int kembalianMutasi, QString uangPelangganMutasi, int untungMutasi, int potonganMutasi, QString jenisMutasi, QString judulTransaksiMutasi);
    void hitungLaporan();
    void getDataMutasi();

private slots:
    void on_actionInput_Barang_triggered();

    void on_actionDaftar_Barang_triggered();

    void on_buttonSimpan_clicked();

    void inputBarangFinished();

    void getDataBarangFinished();

    void tampilBarangFinished();

    void on_buttonFindByKode_clicked();

    void on_buttonFindByBrand_clicked();

    void on_buttonFindByModel_clicked();

    void on_buttonEmergencyStok_clicked();

    void on_actionTransaksi_triggered();

    void on_pushButtonKodeProduk_clicked();

    void jumblahBarang_accept();

    void on_pushButtonBayar_clicked();

    void on_pushButtonClearUangKembali_clicked();

    void on_pushButtonPotongan_clicked();

    void nominalDiskonAccept();

    void updateMutasiFinished();

    void updateStokFinished();

    void on_actionNota_triggered();

    void on_actionLaporan_triggered();

    void getDataMutasiFinished();

private:
    Ui::MainMenu *ui;

    QNetworkAccessManager netManager;
    QNetworkReply *reply;
    QDialog *dialog;
    QSpinBox *mySpinBox;
    QDialog *dialogPotongan;
    QLineEdit *lineEditDialogDiskon;
    QString namaBarang;
    int hargaBarang;
    int totalBayar=0;
    QString kodeProduct;
    int hargaBeliProduct;
    int totalUntung=0;
};

#endif // MAINMENU_H
