#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork"
#include "QJsonObject"
#include "QJsonDocument"
#include "mainmenu.h"
#include "varglobal.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString nama = ui->lineEditUsername->text();

    QString pass = getHWID();

    this->login(nama, pass);
}

bool MainWindow::login( QString user, QString pass )
{
    const QUrl url = QUrl(NAMASERVER+"login.php");

    QNetworkRequest request(url);

    QJsonObject json;

    json.insert("action", "login");
    json.insert("username", user);
    json.insert("hwid", pass);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = netManager.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);

    return true;
}

void MainWindow::httpReadyRead()
{
    ui->labelStatusReply->setText("Loading...");
}

void MainWindow::httpFinished()
{
    QByteArray data = reply->readAll();

    QString hasil = QString::fromStdString(data.toStdString());

    QString hwid = this->getHWID();

    ui->labelStatusReply->setText(hasil);
    ui->labelValueDeviceID->setText(hwid);

    if( hasil == "success" )
    {
        MainMenu *menu = new MainMenu();

        menu->show();
        this->hide();
    }
}

QString MainWindow::getHWID()
{
    this->bIsRetrieved = GetVolumeInformation(TEXT("C:\\"), nullptr, NULL, &dwVolSerial, nullptr, nullptr, nullptr, NULL);

    QString hwdata = QString().sprintf("%04X-%04X", HIWORD(dwVolSerial), LOWORD(dwVolSerial));

    return hwdata;

}
