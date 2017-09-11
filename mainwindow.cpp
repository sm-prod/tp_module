#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QByteArray>
#include <QIODevice>
#include <QFile>// <QTextDocumentWriter>
#include <QTextStream>
#include <QDir>
#include <QDateTime>
#include <QDesktopServices>

QSerialPort serial;

uint8_t adc_i,t_i,t_u_i,adc_u_i;

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
    ui->label->setToolTip("Установлен тип A(def)");
    ui->lineEdit->setPlaceholderText("Команда");

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

    //setup COM port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    //connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    if (!serial.open(QSerialPort::ReadWrite))
    {
        writeData("Порт не удалось открыть");
    }
    else
    {
        writeData("Порт открыт");
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    //close
    serial.close();
    writeData("Порт закрыт");
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
    serial.write("*set_t_A$");
    ui->label->setToolTip("Установлен тип A");
}

void MainWindow::on_pushButton_2_clicked()
{
    serial.write("*set_t_B$");
    ui->label->setToolTip("Установлен тип B");
}

void MainWindow::on_pushButton_3_clicked()
{
    serial.write("*set_t_J$");
    ui->label->setToolTip("Установлен тип J");
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
    serial.write("*set_t_K$");
    ui->label->setToolTip("Установлен тип K");
}

void MainWindow::on_pushButton_8_clicked()
{
    serial.write("*set_t_T$");
    ui->label->setToolTip("Установлен тип T");
}

void MainWindow::on_pushButton_6_clicked()
{
    serial.write("*set_t_N$");
    ui->label->setToolTip("Установлен тип N");
}

void MainWindow::on_pushButton_7_clicked()
{
    serial.write("*set_t_R");
    ui->label->setToolTip("Установлен тип R");
}

void MainWindow::on_pushButton_5_clicked()
{
    serial.write("*set_t_S$");
    ui->label->setToolTip("Установлен тип S");
}

void MainWindow::on_pushButton_11_clicked()
{
    switch (adc_i)
    {
    case 0:
    {
        serial.write("*ADC_ON$");
        adc_i=1;
        ui->pushButton_11->setText("Отображение ADCW\nВключено");
        break;
    }
    case 1:
    {
        serial.write("*ADC_OFF$");
        adc_i=0;
        ui->pushButton_11->setText("Отображение ADCW\nВыключено");
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    switch (t_i)
    {
    case 0:
    {
        serial.write("*t_i_ON$");
        t_i=1;
        ui->pushButton_12->setText("Отображение t°C ХС\nВключено");
        break;
    }
    case 1:
    {
        serial.write("*t_i_OFF$");
        t_i=0;
        ui->pushButton_12->setText("Отображение t°C ХС\nВыключено");
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    switch (t_u_i)
    {
    case 0:
    {
        serial.write("*t_u_i_ON$");
        t_u_i=1;
        ui->pushButton_13->setText("Отображение U(t°C) ХС\nВключено");
        break;
    }
    case 1:
    {
        serial.write("*t_u_i_OFF$");
        t_u_i=0;
        ui->pushButton_13->setText("Отображение U(t°C) ХС\nВыключено");
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    switch (adc_u_i)
    {
    case 0:
    {
        serial.write("*u_i_ON$");
        adc_u_i=1;
        ui->pushButton_14->setText("Отображение U\nВключено");
        break;
    }
    case 1:
    {
        serial.write("*u_i_OFF$");
        adc_u_i=0;
        ui->pushButton_14->setText("Отображение U\nВыключено");
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    QString input = ui->lineEdit->text();
    //char send[16];
    serial.write(qPrintable(input));
}

void MainWindow::on_pushButton_16_clicked()
{
    //QString filePath =

    QDir dir(QDir::homePath() + "/Documents");
    dir.mkdir("Термопара");
    QString fname = QDir::homePath() + "/Documents/Термопара/Температура"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        writeData("Ошибка");
        return;
    }
    QTextStream out(&file);//поток для записи текста
    out << ui->textBrowser->toPlainText();
    QDesktopServices::openUrl (QUrl::fromLocalFile(QDir::homePath() + "/Documents/Термопара"));
}
