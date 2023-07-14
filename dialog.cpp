#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino = new QSerialPort;
    arduino_is_available = false;
    desired_arduino = true;
    arduino_port_name = "";


    qDebug() << "Number of Ports:" << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            setVendorId(serialPortInfo.vendorIdentifier());
            setProductId(serialPortInfo.productIdentifier());
            qDebug() << serialPortInfo.vendorIdentifier();
            qDebug() << serialPortInfo.productIdentifier();
        }
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
            if(serialPortInfo.productIdentifier() == arduino_uno_productID){
                arduino_port_name = serialPortInfo.portName();
                arduino_is_available = true;
                qDebug() << "Port available";
            }
        }
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Port Name:" << serialPortInfo.portName();
        qDebug() << "Vendor ID:" << serialPortInfo.vendorIdentifier();
        qDebug() << "Product ID:" << serialPortInfo.productIdentifier();
    }

    if(arduino_is_available){
        qDebug() << arduino_port_name;
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        qDebug() << "Error: " << arduino->errorString();
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else{
        QMessageBox::warning(this,"Port error","Couldn't find arduino");

    }
    QByteArray data = arduino->readAll(); // Read the available data from the serial port
    QString receivedData = QString::fromUtf8(data);
    if (receivedData.contains("ARDUINO")) {
        desired_arduino = true;
    }
}

void Dialog::setVendorId(quint16 a){
    this->arduino_uno_vendor_id = a;
}
void Dialog::setProductId(quint16 a){
    this->arduino_uno_productID = a;
}
Dialog::~Dialog()
{
    if(arduino->isOpen()){
        qDebug() << "closing port";
        arduino->close();
    }
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON\n");
        qDebug() << "on";
        QThread::msleep(2000);
        arduino->write("OFF\n");
        qDebug() << "off";
    }
    else{
        qDebug() << "close";
    }

}


void Dialog::on_pushButton_2_clicked()
{
    if(arduino->isWritable() && desired_arduino){
          arduino->write("OFF\n");
        qDebug() << "off";
    }
    else{
        qDebug() << "close";
    }
}

