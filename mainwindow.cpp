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
    ui->pushButton->setToolTip("вольфрам-рениевая термопара");
    ui->pushButton_2->setToolTip("платнородий-платинородиевая термопара");
    ui->pushButton_3->setToolTip("железо-константановая термопара");
    ui->pushButton_4->setToolTip("хромель-алюмелевая термопара");
    ui->pushButton_6->setToolTip("нихросил-нисиловая термопара");
    ui->pushButton_7->setToolTip("платнородий-платиновая термопара");
    ui->pushButton_5->setToolTip("платнородий-платиновая термопара");
    ui->pushButton_8->setToolTip("медь-константановая термопара");

    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    //read avaible comports
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    ui->comboBox->addItem(info.portName());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_9_clicked()
{
    //select name for our serial port from combobox
    if (serial.portName() != ui->comboBox->currentText())
    {
        serial.close();
        serial.setPortName(ui->comboBox->currentText());
    }
    serial.open(QSerialPort::ReadWrite);
    //setup COM port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    //connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);

}

void MainWindow::on_pushButton_10_clicked()
{
    //close
    serial.close();
}


void MainWindow::readSerial()
{
    QByteArray data;
   /*
    while (serial.bytesAvailable()<=8)
    {
        //qint64 QIODevice::bytesAvailable() const
        //{
         //   return buffer.size() + QIODevice::bytesAvailable();
        //}
        QApplication::processEvents();

    }
    */
    QApplication::processEvents();
    //data= serial.readAll();
    data.append(serial.readAll());
    writeData(data);
}

void MainWindow::on_pushButton_clicked()
{
    serial.write("TEST");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->setText("1test-test");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->append("2test-test");
}


void MainWindow::writeData(QByteArray data)
{
    QTextCursor cur = ui->textBrowser->textCursor();
    cur.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cur);
    ui->textBrowser->insertPlainText(data);
}

void MainWindow::on_pushButton_4_clicked()
{
    serial.write("TEST1")
}

void MainWindow::on_pushButton_8_clicked()
{

}
