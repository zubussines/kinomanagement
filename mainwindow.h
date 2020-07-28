#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <stdio.h>
#include <windows.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool login(QString user, QString pass );
    QString getHWID();

    DWORD dwVolSerial;
    BOOL bIsRetrieved;

private slots:
    void on_pushButtonLogin_clicked();
    void httpFinished();
    void httpReadyRead();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager netManager;
    QNetworkReply *reply;
};

#endif // MAINWINDOW_H
