#include "varglobal.h"
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "QtNetwork"
#include "QJsonObject"
#include "QJsonDocument"
#include "QVBoxLayout"
#include "QDialogButtonBox"
#include "QMessageBox"
#include "QShortcut"
#include "QDateTime"
#include "QFile"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Kode"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Nama"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Stok"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Distributor"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Alamat"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Kordinat"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Deskripsi"));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Harga Beli"));
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("Harga Jual"));
    ui->tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("Satuan Barang"));
    ui->tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("Brand"));
    ui->tableWidget->setHorizontalHeaderItem(11, new QTableWidgetItem("Model"));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);


    ui->tableWidgetTransaksi->setHorizontalHeaderItem(0, new QTableWidgetItem("Product Code"));
    ui->tableWidgetTransaksi->setHorizontalHeaderItem(1, new QTableWidgetItem("Nama Product"));
    ui->tableWidgetTransaksi->setHorizontalHeaderItem(2, new QTableWidgetItem("Jumlah"));
    ui->tableWidgetTransaksi->setHorizontalHeaderItem(3, new QTableWidgetItem("Harga"));
    ui->tableWidgetTransaksi->setHorizontalHeaderItem(4, new QTableWidgetItem("Total"));

    ui->tableWidgetTransaksi->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);


    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_Insert),ui->pushButtonKodeProduk,SLOT(click()));
    shortcut->setAutoRepeat(false);

    QShortcut * shortcutBayar = new QShortcut(QKeySequence(Qt::Key_End),ui->pushButtonBayar,SLOT(click()));
    shortcutBayar->setAutoRepeat(false);
}

MainMenu::~MainMenu()
{
    delete ui;
}


//############# menu ##########################
void MainMenu::on_actionInput_Barang_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainMenu::on_actionDaftar_Barang_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_actionTransaksi_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainMenu::on_actionNota_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainMenu::on_actionLaporan_triggered()
{
    getDataMutasi();
}
//##############################################



//########## Input Barang ###################################
void MainMenu::on_buttonSimpan_clicked()
{
    QString namaBarang = ui->namaBarang->text();
    QString kodeBarang = ui->kodeBarang->text();
    QString stokBarang = ui->stokBarang->text();
    QString distributorBarang = ui->distributorBarang->text();
    QString alamatDistributor = ui->alamatDistributor->text();
    QString kordinatBarang = ui->kordinatBarang->text();
    QString deskripsiBarang = ui->deskripsiBarang->text();
    QString hargaBeliBarang = ui->hargaBeliBarang->text();
    QString hargaJualBarang = ui->hargaJualBarang->text();
    QString satuanBarang = ui->satuanBarang->text();
    QString brandBarang = ui->brand->text();
    QString modelBarang = ui->model->text();

    inputBarang(namaBarang, kodeBarang, stokBarang, distributorBarang, alamatDistributor, kordinatBarang, deskripsiBarang, hargaBeliBarang, hargaJualBarang, satuanBarang, brandBarang, modelBarang);
}

void MainMenu::inputBarang(QString barang, QString kode, QString stok, QString distributor, QString alamatdistrib, QString kordinat, QString deskripsi, QString hargaBeli, QString hargaJual, QString satuan, QString brand, QString model)
{
    const QUrl url = QUrl(NAMASERVER+"inputbarang.php");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", "inputbarang");
    json.insert("barang", barang);
    json.insert("kode", kode);
    json.insert("stok", stok);
    json.insert("distributor", distributor);
    json.insert("alamatdistrib", alamatdistrib);
    json.insert("kordinat", kordinat);
    json.insert("deskripsi", deskripsi);
    json.insert("hargabeli", hargaBeli);
    json.insert("hargajual", hargaJual);
    json.insert("satuan", satuan);
    json.insert("brand", brand);
    json.insert("model", model);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::inputBarangFinished);

}

void MainMenu::inputBarangFinished()
{
    QByteArray data = reply->readAll();

    QString hasil = QString::fromStdString(data.toStdString());

    QString namaBarang = ui->namaBarang->text();

    ui->labelResponse->setText(hasil);
    if( hasil == "success" )
    {
        QString status = "input barang "+namaBarang+" telah berhasil";
        ui->labelStatus->setText(status);
        ui->kodeBarang->clear();
        ui->namaBarang->clear();
        ui->stokBarang->clear();
        ui->distributorBarang->clear();
        ui->alamatDistributor->clear();
        ui->kordinatBarang->clear();
        ui->deskripsiBarang->clear();
        ui->hargaBeliBarang->clear();
        ui->hargaJualBarang->clear();
        ui->satuanBarang->clear();
        ui->brand->clear();
        ui->model->clear();
     }
    if( hasil == "ready" )
    {
        QString status = "barang "+namaBarang+" sudah ada dalam database";
        ui->labelStatus->setText(status);
    }
    if( hasil == "failed" )
    {
        QString status = "input barang "+namaBarang+" telah gagal";
        ui->labelStatus->setText(status);
    }
}
//#####################################################################################


//################# Tampil Barang ####################################################
void MainMenu::tampilBarang(QString action, QString kode)
{
    const QUrl url = QUrl(NAMASERVER+"tampilbarang.php");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", action);
    json.insert("kode", kode);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::tampilBarangFinished);
}

void MainMenu::tampilBarangFinished()
{
    QByteArray data = reply->readAll();

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    int responseStatus = statusCode.toInt();

    ui->responseStatus->setNum(responseStatus);

    if( !data.isEmpty() && responseStatus == 200 )
    {
        ui->searchStatus->setText("Success");
    }else{
        ui->searchStatus->setText("Lost");
    }

    auto doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();
    int ukuranArray = jsonArray.size();

    ui->tableWidget->setRowCount(ukuranArray);

    for( int i = 0; i < ukuranArray; i++)
    {
            QList<QVariant> list = doc.toVariant().toList();
            QMap<QString, QVariant> map = list[i].toMap();

            QString dataKode = map["kodebarang"].toString();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(dataKode) );

            QString dataNama = map["namabarang"].toString();
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dataNama));

            QString dataStok = map["stokbarang"].toString();
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(dataStok));

            QString dataDistrib = map["distributorbarang"].toString();
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(dataDistrib));

            QString dataAlamatDistrib = map["alamatdistributor"].toString();
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(dataAlamatDistrib));

            QString dataKordinat = map["kordinatbarang"].toString();
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(dataKordinat));

            QString dataDeskripsi = map["deskripsibarang"].toString();
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(dataDeskripsi));

            QString dataHargaBeli = map["hargabelibarang"].toString();
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(dataHargaBeli));

            QString dataHargaJual = map["hargajualbarang"].toString();
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(dataHargaJual));

            QString dataSatuan = map["satuanbarang"].toString();
            ui->tableWidget->setItem(i, 9, new QTableWidgetItem(dataSatuan));

            QString dataBrand = map["brandbarang"].toString();
            ui->tableWidget->setItem(i, 10, new QTableWidgetItem(dataBrand));

            QString dataModel = map["modelbarang"].toString();
            ui->tableWidget->setItem(i, 11, new QTableWidgetItem(dataModel));
    }
}

void MainMenu::on_buttonFindByKode_clicked()
{
    QString kode = ui->searchByKode->text();

    QString action = "tampilbarangbykode";

    tampilBarang(action, kode);
}

void MainMenu::on_buttonFindByBrand_clicked()
{
    QString kode = ui->searchByBrand->text();

    QString action = "tampilbarangbybrand";

    tampilBarang(action, kode);
}

void MainMenu::on_buttonFindByModel_clicked()
{
    QString kode = ui->searchByModel->text();

    QString action = "tampilbarangbymodel";

    tampilBarang(action, kode);
}

void MainMenu::on_buttonEmergencyStok_clicked()
{
    QString kode = "1";
    QString action = "tampilbarangemergency";

    tampilBarang(action, kode);
}
//######################################################################################################


//########################################################################################################
//################## blok add product
//#########################################################################################################
void MainMenu::on_pushButtonKodeProduk_clicked()
{
    QString productCode = ui->lineEditKodeProduk->text();

    getDataProduct(productCode);
}

void MainMenu::getDataProduct(QString kode)
{
    const QUrl url = QUrl(NAMASERVER+"getdatabarang.php");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", "getdatabarang");
    json.insert("kode", kode);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::getDataBarangFinished);
}

void MainMenu::getDataBarangFinished()
{
    QByteArray data = reply->readAll();

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    QString hasil = QString::fromStdString(data.toStdString());


    if( hasil != "[]" )
    {
        auto doc = QJsonDocument::fromJson(data);

        QList<QVariant> list = doc.toVariant().toList();
        QMap<QString, QVariant> map = list[0].toMap();

        if( !map["namabarang"].toString().isEmpty() )
        {
            namaBarang = map["namabarang"].toString();

            hargaBarang = map["hargajualbarang"].toInt();
            hargaBeliProduct = map["hargabelibarang"].toInt();
            kodeProduct = map["kodebarang"].toString();


            dialog = new QDialog();
            dialog->setWindowTitle("Jumlah Barang");

            mySpinBox = new QSpinBox();
            mySpinBox->setValue(1);

            QLabel *jumLabel = new QLabel();
            jumLabel->setText("Jumlah "+namaBarang);

            QDialogButtonBox *butonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

            QVBoxLayout *myLayout = new QVBoxLayout;
            myLayout->addWidget(jumLabel);
            myLayout->addWidget(mySpinBox);
            myLayout->addWidget(butonBox);

            dialog->setLayout(myLayout);

            dialog->show();

            connect( butonBox, SIGNAL(accepted()), this, SLOT(jumblahBarang_accept()) );
        }
    }else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Tidak Ditemukan");
        msgBox.setText("Produk Tidak Ditemukan.");
        msgBox.exec();
    }
}

void MainMenu::jumblahBarang_accept()
{

    int rw = ui->tableWidgetTransaksi->rowCount() + 1;

    ui->tableWidgetTransaksi->setRowCount(rw);

    int setitem = rw - 1;
    int totalHarga = mySpinBox->value() * hargaBarang;
    totalBayar = totalBayar + totalHarga;

    int untungProduct = hargaBarang - hargaBeliProduct;
    int totalUntungProduk = mySpinBox->value() * untungProduct;
    totalUntung = totalUntung + totalUntungProduk;

    QString untung = QString::number(totalUntung);

    QString bayar = QString::number(totalBayar);

    QString qty = QString::number( mySpinBox->value() );
    QString tblHarga = QString::number(hargaBarang);
    QString tblTotalHarga = QString::number(totalHarga);

    ui->tableWidgetTransaksi->setItem(setitem, 0, new QTableWidgetItem(kodeProduct));
    ui->tableWidgetTransaksi->setItem(setitem, 1, new QTableWidgetItem(namaBarang));
    ui->tableWidgetTransaksi->setItem(setitem, 2, new QTableWidgetItem(qty));
    ui->tableWidgetTransaksi->setItem(setitem, 3, new QTableWidgetItem(tblHarga));
    ui->tableWidgetTransaksi->setItem(setitem, 4, new QTableWidgetItem(tblTotalHarga));



    ui->labelTotalBayar->setText("<html><head/><body><p><span style=' font-size:16pt;'>"+bayar+"</span></p></body></html>");
    ui->labelUntung->setText("<html><head/><body><p><span style=' font-size:16pt;'>"+untung+"</span></p></body></html>");
    dialog->close();
    mySpinBox->clear();

    ui->lineEditKodeProduk->clear();


}
//###########################################################################################################


//########################################################################################################
//############          blok mutasi
//########################################################################################################
void MainMenu::on_pushButtonBayar_clicked()
{
    const QUrl url = QUrl(NAMASERVER+"updatestok.php");

    QNetworkRequest request(url);

    // fungsi update stok barang
    //dapatkan data dari table
    int rowTbale = ui->tableWidgetTransaksi->rowCount();

    QJsonObject updateObject;
    updateObject.insert("action", "updatestok");
    updateObject.insert("size", rowTbale);

    for( int n = 0; n < rowTbale; n++ )
        {
            QJsonArray tableArray;

            for( int i = 0; i < 3; i++ )
            {
                tableArray.append(ui->tableWidgetTransaksi->takeItem(n, i)->text());

                i = i+1;
            }

            updateObject.insert("data"+QString::number(n), tableArray );
        }

    QJsonDocument jsonDoc(updateObject);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::updateStokFinished);
}

void MainMenu::updateMutasi(QString idMutasi, QString jamMutasi, QString tanggalMutasi, QString bulanMutasi, QString tahunMutasi, int nominalMutasi, QString pelangganMutasi, int kembalianMutasi, QString uangPelangganMutasi, int untungMutasi, int potonganMutasi, QString jenisMutasi, QString judulTransaksiMutasi)
{
    const QUrl url = QUrl(NAMASERVER+"updatemutasi.php");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", "updatemutasi");
    json.insert("id", idMutasi);
    json.insert("jam", jamMutasi);
    json.insert("tanggal", tanggalMutasi);
    json.insert("bulan", bulanMutasi);
    json.insert("tahun", tahunMutasi);
    json.insert("nominal", nominalMutasi);
    json.insert("pelanggan", pelangganMutasi);
    json.insert("kembalian", kembalianMutasi);
    json.insert("uangpelanggan", uangPelangganMutasi);
    json.insert("untung", untungMutasi);
    json.insert("potongan", potonganMutasi);
    json.insert("jenis", jenisMutasi );
    json.insert("judul", judulTransaksiMutasi);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::updateMutasiFinished);
}

void MainMenu::updateMutasiFinished()
{
    QByteArray data = reply->readAll();

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    QString hasil = QString::fromStdString(data.toStdString());


    if( hasil == "success" )
    {
        ui->tableWidgetTransaksi->clearContents();
        ui->tableWidgetTransaksi->setRowCount(0);
        ui->labelTotalBayar->setText("<html><head/><body><p><span style=' font-size:16pt;'>0.00</span></p></body></html>");
        int uangpelanggan = ui->lineEditUangPelanggan->text().toInt();

        QString kembalian = QString::number( uangpelanggan - totalBayar );

        ui->labelUangKembali->setText("<html><head/><body><p><span style=' font-size:18pt;'>"+kembalian+"</span></p></body></html>");
        totalBayar =0;
        totalUntung=0;

        ui->labelUntung->setText("<html><head/><body><p><span style=' font-size:16pt;'>0.00</span></p></body></html>");
        ui->lineEditUangPelanggan->clear();
        ui->labelDiskon->setNum(0);
        ui->labelUpdateMutasi->setText("success");
    }else{
        ui->labelUpdateMutasi->setText("failed");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Update Mutasi");
        msgBox.setText("Update Mutasi Gagal.");
        msgBox.exec();
    }

}

void MainMenu::on_pushButtonClearUangKembali_clicked()
{
    ui->labelUangKembali->setText("<html><head/><body><p><span style=' font-size:18pt;'>0.00</span></p></body></html>");
    ui->labelUpdateStok->setText("none");
    ui->labelUpdateMutasi->setText("none");
}
void MainMenu::on_pushButtonPotongan_clicked()
{
    if(ui->labelDiskon->text().toInt() < 1)
    {
        dialogPotongan = new QDialog();
        dialogPotongan->setWindowTitle("Diskon Harga");

        lineEditDialogDiskon = new QLineEdit();
        lineEditDialogDiskon->setText("10000");

        QLabel *jumLabelDiskon = new QLabel();
        jumLabelDiskon->setText("Nominal Diskon ");

        QDialogButtonBox *butonBoxDiskon = new QDialogButtonBox(QDialogButtonBox::Ok);

        QVBoxLayout *myLayout = new QVBoxLayout;
        myLayout->addWidget(jumLabelDiskon);
        myLayout->addWidget(lineEditDialogDiskon);
        myLayout->addWidget(butonBoxDiskon);

        dialogPotongan->setLayout(myLayout);

        dialogPotongan->show();

        connect( butonBoxDiskon, SIGNAL(accepted()), this, SLOT(nominalDiskonAccept()) );
    }else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Telah Diskon");
        msgBox.setText("Transaksi Sudah Di Diskon.");
        msgBox.exec();
    }
}

void MainMenu::nominalDiskonAccept()
{
    int diskon = lineEditDialogDiskon->text().toInt();

    QString bayar = QString::number( totalBayar - diskon );
    totalBayar = totalBayar - diskon;

    QString untung = QString::number( totalUntung - diskon );
    totalUntung = totalUntung - diskon;

    ui->labelTotalBayar->setText("<html><head/><body><p><span style=' font-size:16pt;'>"+bayar+"</span></p></body></html>");

    ui->labelUntung->setText("<html><head/><body><p><span style=' font-size:16pt;'>"+untung+"</span></p></body></html>");

    ui->labelDiskon->setText(QString::number(diskon));

    dialogPotongan->close();
}

void MainMenu::updateStokFinished()
{
    QByteArray data = reply->readAll();

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    QString hasil = QString::fromStdString(data.toStdString());

    if( hasil == "success" )
    {
        QDateTime tanggal = QDateTime::currentDateTime();

        QString varJam = tanggal.toString("hh");

        QString varTanggal = tanggal.toString("dd");

        QString varBulan = tanggal.toString("MM");

        QString varTahun = tanggal.toString("yyyy");

        QString idMutasi = tanggal.toString("yyMMddhhmmss");

        int varNominal = totalBayar;

        QString namaPelanggan = ui->lineEditNamaPelanggan->text();

        int uangKembali = ui->lineEditUangPelanggan->text().toInt() - totalBayar;

        QString uangPelanggan = ui->lineEditUangPelanggan->text();

        int varUntung = totalUntung;

        int potongan = ui->labelDiskon->text().toInt();

        QString varJudulTransaksi = ui->lineEditJudulTransaksi->text();

        ui->labelUpdateStok->setText(hasil);

        QString jenisMutasi;
        if( ui->radioButtonTransaksiBarang->isChecked() )
        {
            jenisMutasi = "barang";
        }else if( ui->radioButtonTransaksiDigital->isChecked() ){
            jenisMutasi = "digital";
        }else if( ui->radioButtonTransaksiJasa->isChecked() ){
            jenisMutasi = "jasa";
        }


        updateMutasi(idMutasi, varJam, varTanggal, varBulan, varTahun, varNominal, namaPelanggan, uangKembali, uangPelanggan, varUntung, potongan, jenisMutasi, varJudulTransaksi);
    }else{
        ui->labelUpdateStok->setText("failed");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error From Server");
        msgBox.setText(hasil);
        msgBox.exec();
    }
}

void MainMenu::hitungLaporan()
{
}

void MainMenu::getDataMutasi()
{
    const QUrl url = QUrl(NAMASERVER+"getdatamutasi.php");

    QDateTime tanggal = QDateTime::currentDateTime();

    QString varTanggal = tanggal.toString("dd");

    QString varBulan = tanggal.toString("MM");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", "getdatamutasi");
    json.insert("tanggal", varTanggal);
    json.insert("bulan", varBulan);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainMenu::getDataMutasiFinished);
}

void MainMenu::getDataMutasiFinished()
{
    QByteArray data = reply->readAll();

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    QString hasil = QString::fromStdString(data.toStdString());

    QJsonDocument docMutasi = QJsonDocument::fromJson(hasil.toUtf8());

    QJsonObject mutasiObject = docMutasi.object();

    // inisialisasi variable untuk laporan
    QString hasilHarian = mutasiObject.value("hasilharian").toString();
    QString hasilBulanan = mutasiObject.value("hasilbulanan").toString();
    QString untungHarian = mutasiObject.value("untungharian").toString();
    QString untungBulanan = mutasiObject.value("untungbulanan").toString();
    QString pengeluaranHarian = mutasiObject.value("pengeluaranharian").toString();
    QString pengeluaranBulanan = mutasiObject.value("pengeluaranbulanan").toString();
    QString pemasukanHarian = mutasiObject.value("pemasukanharian").toString();
    QString pemasukanBulanan = mutasiObject.value("pemasukanbulanan").toString();
    QString untungBersihHarian = mutasiObject.value("untungbersihharian").toString();
    QString untungBersihBulanan = mutasiObject.value("untungbersihbulanan").toString();

    // laporan harian
    ui->labelHasilHarian->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+hasilHarian+"</span></p></body></html>");
    ui->labelUntungHariIni->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+untungHarian+"</span></p></body></html>");
    ui->labelPengeluaranHarian->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+pengeluaranHarian+"</span></p></body></html>");
    ui->labelPemasukanHarian->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+pemasukanHarian+"</span></p></body></html>");
    ui->labelUntungBersihHarian->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+untungBersihHarian+"</span></p></body></html>");

    // laporan bulanan
    ui->labelHasilBulanan->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+hasilBulanan+"</span></p></body></html>");
    ui->labelUntungBulanan->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+untungBulanan+"</span></p></body></html>");
    ui->labelPengeluaranBulanan->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+pengeluaranBulanan+"</span></p></body></html>");
    ui->labelPemasukanBulanan->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+pemasukanBulanan+"</span></p></body></html>");
    ui->labelUntungBersihBulanan->setText("<html><head/><body><p><span style=' font-size:12pt;'>Rp "+untungBersihBulanan+"</span></p></body></html>");

    ui->stackedWidget->setCurrentIndex(4);
}
