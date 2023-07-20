#include "dialog.h"
#include "ui_dialog.h"
#include "gloweffect.h"
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    arduino = new QSerialPort;
    arduino_is_available = false;
    desired_arduino = true;
    arduino_port_name = "";

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *ledLayout = new QHBoxLayout;
    QGraphicsView *graphicsView = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene;

    // Set the scene size to accommodate all four LEDs
    scene->setSceneRect(0, 0, 700, 200); // Each LED is 60x60, so total width is 240

    graphicsView->setScene(scene);
    GlowEffect *glowEffect = new GlowEffect;

    // Create and add the LED widgets with names to the scene
    led1 = new LedWidget("LED 1");
    led2 = new LedWidget("LED 2");
    led3 = new LedWidget("LED 3");
    led4 = new LedWidget("LED 4"); // Add the 4th LED widget
    led1->setGraphicsEffect(glowEffect);
    led2->setGraphicsEffect(glowEffect);
    led3->setGraphicsEffect(glowEffect);
    led4->setGraphicsEffect(glowEffect);

    scene->addWidget(led1)->setPos(0, 0);
    scene->addWidget(led2)->setPos(150, 0);
    scene->addWidget(led3)->setPos(300, 0);
    scene->addWidget(led4)->setPos(450, 0); // Add the 4th LED widget to the scene and adjust its position

    ledLayout->addWidget(graphicsView);
    mainLayout->addLayout(ledLayout);

    // The rest of your button creation and connection code...

    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");
    QPushButton *button3 = new QPushButton("Button 3");
    QPushButton *button4 = new QPushButton("Button 4");


    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);
    mainLayout->addWidget(button3);
    mainLayout->addWidget(button4);


    setLayout(mainLayout);

    // Connect button pressed and released signals to custom slots
    connect(button1, &QPushButton::pressed, this, &Dialog::on_pushButton_pressed);
    connect(button1, &QPushButton::released, this, &Dialog::on_pushButton_released);
    connect(button2, &QPushButton::pressed, this, &Dialog::on_pushButton_2_pressed);
    connect(button2, &QPushButton::released, this, &Dialog::on_pushButton_2_released);
    connect(button3, &QPushButton::pressed, this, &Dialog::on_pushButton_3_released);
    connect(button3, &QPushButton::released, this, &Dialog::on_pushButton_3_released);
    connect(button4, &QPushButton::pressed, this, &Dialog::on_pushButton_4_pressed);
    connect(button4, &QPushButton::released, this, &Dialog::on_pushButton_4_released);



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

void Dialog::on_pushButton_pressed()
{
      //  changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON1\n");
        qDebug() << "led 1 is on";
       //  led1->setLedState(true);
    }
}


void Dialog::on_pushButton_released()
{
      //  changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF1\n");
        qDebug() << "led 1 is off";
        // led1->setLedState(false);
    }

}


void Dialog::on_pushButton_2_pressed()
{
     //   changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON2\n");
        qDebug() << "led 2 is on";
    }

}


void Dialog::on_pushButton_2_released()
{
       // changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF2\n");
        qDebug() << "led 2 is off";
    }

}


void Dialog::on_pushButton_3_pressed()
{
       // changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON3\n");
        qDebug() << "led 3 is on";
    }
}


void Dialog::on_pushButton_3_released()
{
       // changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF3\n");
        qDebug() << "led 3 is off";
    }

}


void Dialog::on_pushButton_4_pressed()
{
        //changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON4\n");
        qDebug() << "led 4 is on";
    }

}

void Dialog::on_pushButton_4_released()
{
    //changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF4\n");
        qDebug() << "led 4 is off";
    }
}

void Dialog::changeStatusOfAll(){
    qDebug() << "here";
    QByteArray s = arduino->readAll();
    qDebug() << s;
    if(s.contains("HIGH1")){
        led1->setLedState(true);
    }
    else if(s.contains("LOW1")){
        led1->setLedState(false);
    }
    else if(s.contains("HIGH2")){
        led2->setLedState(true);
    }
    else if(s.contains("LOW2")){
        led2->setLedState(false);
    }
    else if(s.contains("HIGH3")){
        led3->setLedState(true);
    }
    else if(s.contains("LOW3")){
        led3->setLedState(false);
    }
    else if(s.contains("HIGH4")){
        led4->setLedState(true);
    }
    else if(s.contains("LOW4")){
        led4->setLedState(false);
    }
}
