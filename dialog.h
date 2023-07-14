#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setVendorId(quint16 a);
    void setProductId(quint16 a);
    bool isDesiredArduino(quint16 vendor_id, quint16 product_id);;
    bool readSerialData();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    quint16 arduino_uno_vendor_id;
    quint16 arduino_uno_productID;
    QString arduino_port_name;
    bool arduino_is_available;
    bool desired_arduino;

};
#endif // DIALOG_H
