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
    QGraphicsView *graphicsView = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene;

    // Set the scene size to accommodate all four LEDs
    scene->setSceneRect(0, 0, 700, 50); // Each LED is 60x60, so total width is 240

    graphicsView->setScene(scene);
    graphicsView->setStyleSheet("background: transparent;");
    GlowEffect *glowEffect = new GlowEffect;

    // Create and add the LED widgets to the scene
    led1 = new LedWidget("LED 1");
    led2 = new LedWidget("LED 2");
    led3 = new LedWidget("LED 3");
    led4 = new LedWidget("LED 4");
    led5 = new LedWidget("LED 5"); // Add the 4th LED widget
    led1->setGraphicsEffect(glowEffect);
    led2->setGraphicsEffect(glowEffect);
    led3->setGraphicsEffect(glowEffect);
    led4->setGraphicsEffect(glowEffect);
    led5->setGraphicsEffect(glowEffect);

    scene->addWidget(led1)->setPos(40, 0);
    scene->addWidget(led2)->setPos(240, 0);
    scene->addWidget(led3)->setPos(445, 0);
    scene->addWidget(led4)->setPos(650, 0);
    scene->addWidget(led5)->setPos(420, 0);

    QHBoxLayout *nameLabelsLayout = new QHBoxLayout; // Create the QHBoxLayout for name labels
    QLabel *nameLabel1 = new QLabel("LED 1");
    QLabel *nameLabel2 = new QLabel("LED 2");
    QLabel *nameLabel3 = new QLabel("LED 3");
    QLabel *nameLabel4 = new QLabel("LED 4");

    nameLabelsLayout->setContentsMargins(0, 0, 0, 0); // Adjust top margin as needed
    nameLabelsLayout->setSpacing(10); // Adjust spacing as needed

    nameLabel1->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nameLabel2->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nameLabel3->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nameLabel4->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // Add the name labels to the layout
    nameLabelsLayout->addWidget(nameLabel1);
    nameLabelsLayout->addWidget(nameLabel2);
    nameLabelsLayout->addWidget(nameLabel3);
    nameLabelsLayout->addWidget(nameLabel4);

    mainLayout->addLayout(nameLabelsLayout); // Add the name labels layout under the LEDs
    mainLayout->addWidget(graphicsView); // Add the LEDs to the main layout

    // The rest of your button creation and connection code...
    QHBoxLayout *rowLayout1 = new QHBoxLayout;
    QPushButton *button1 = new QPushButton("Button 1");
    button1->setFixedSize(300,100);
    QPushButton *button2 = new QPushButton("Button 2");
    button2->setFixedSize(300,100);
    rowLayout1->addWidget(button1);
    rowLayout1->addWidget(button2);

    // Create the second row layout
    QHBoxLayout *rowLayout2 = new QHBoxLayout;
    QPushButton *button3 = new QPushButton("Button 3");
    button3->setFixedSize(300,100);
    QPushButton *button4 = new QPushButton("Button 4");
    button4->setFixedSize(300,100);
    rowLayout2->addWidget(button3);
    rowLayout2->addWidget(button4);
    // Apply button styles
    QString buttonStyle = "QPushButton {"
                          "background-color: #0000ff;"
                          "border: none;"
                          "color: white;"
                          "padding: 8px 16px;"
                          "border-radius: 4px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #ff00008B;"
                          "}";

    button1->setStyleSheet(buttonStyle);
    button2->setStyleSheet(buttonStyle);
    button3->setStyleSheet(buttonStyle);
    button4->setStyleSheet(buttonStyle);

    // Add row layouts to the main layout
    mainLayout->addLayout(rowLayout1);
    mainLayout->addLayout(rowLayout2);
    setLayout(mainLayout);

    // Connect button pressed and released signals to custom slots
    connect(button1, &QPushButton::pressed, this, &Dialog::on_pushButton_pressed);
    connect(button1, &QPushButton::released, this, &Dialog::on_pushButton_released);
    connect(button2, &QPushButton::pressed, this, &Dialog::on_pushButton_2_pressed);
    connect(button2, &QPushButton::released, this, &Dialog::on_pushButton_2_released);
    connect(button3, &QPushButton::pressed, this, &Dialog::on_pushButton_3_pressed);
    connect(button3, &QPushButton::released, this, &Dialog::on_pushButton_3_released);
    connect(button4, &QPushButton::pressed, this, &Dialog::on_pushButton_4_pressed);
    connect(button4, &QPushButton::released, this, &Dialog::on_pushButton_4_released);

    // The rest of your code...


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

    connect(this, &Dialog::changeStatusOfAllSignal, this, &Dialog::changeStatusOfAll);

    // Create a new thread and move the Dialog instance to that thread
    QThread* workerThread = new QThread;
    this->moveToThread(workerThread);

    // Start the worker thread
    workerThread->start();
    setWindowTitle("LED Control Panel");
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
      //  qDebug() << "led 1 is on";
       //  led1->setLedState(true);

    }
}


void Dialog::on_pushButton_released()
{
      //  changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF1\n");
       // qDebug() << "led 1 is off";
        // led1->setLedState(false);
    }

}


void Dialog::on_pushButton_2_pressed()
{
     //   changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON2\n");
       // qDebug() << "led 2 is on";
    }

}


void Dialog::on_pushButton_2_released()
{
       // changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF2\n");
      //  qDebug() << "led 2 is off";
    }

}


void Dialog::on_pushButton_3_pressed()
{
       // changeStatusOfAll();

    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON3\n");
      //  qDebug() << "led 3 is on";
    }
}


void Dialog::on_pushButton_3_released()
{
       // changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF3\n");
      //  qDebug() << "led 3 is off";
    }

}


void Dialog::on_pushButton_4_pressed()
{
        //changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("ON4\n");
      //  qDebug() << "led 4 is on";
    }

}

void Dialog::on_pushButton_4_released()
{
    //changeStatusOfAll();
    if(arduino->isWritable() && desired_arduino){
        arduino->write("OFF4\n");
      //  qDebug() << "led 4 is off";
    }
}

void Dialog::changeStatusOfAll()
{
    QByteArray s = arduino->readAll();

    if (s.contains("HIGH1")) {
        led1->setLedState(true);
    } else if(s.contains("LOW1")) {
        led1->setLedState(false);
    }

    if (s.contains("HIGH2")) {
        led2->setLedState(true);
    } else if(s.contains("LOW2")) {
        led2->setLedState(false);
    }

    if (s.contains("HIGH3")) {
        led3->setLedState(true);
    } else if (s.contains("LOW3")) {
        led3->setLedState(false);
    }

    if (s.contains("HIGH4")) {
        led4->setLedState(true);
    } else if (s.contains("LOW4")) {
        led4->setLedState(false);
    }

}
