#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QByteArray>
#include <QIODevice>

QSerialPort serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(this, SIGNAL(readyRead()) ,this, SLOT(readSerial()), Qt::AutoConnection);
    //read avaible comports
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    ui->comboBox->addItem(info.portName());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    serial.write("TEST");
}

void MainWindow::on_pushButton_9_clicked()
{
    //select name for our serial port from combobox
    if (serial.portName() != ui->comboBox->currentText())
    {
        serial.close();
        serial.setPortName(ui->comboBox->currentText());
    }

    //setup COM port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QSerialPort::WriteOnly);
}

void MainWindow::on_pushButton_10_clicked()
{
    //close
    serial.close();
}


void MainWindow::readSerial()
{
        QByteArray data;
        //QApplication::processEvents();

        data= serial.readAll();
        //data.append(serial.readAll());

        ui->textBrowser->setText("data");


}



void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->setText("1test-test");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->append("2test-test");
}
