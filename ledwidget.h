// ledwidget.h
#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

class QLabel; // Forward declaration of QLabel class

class LedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LedWidget(const QString& name, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setLedState(bool isOn);

private:
    bool m_isOn;
    QLabel* m_nameLabel; // Label for displaying the LED name
};

#endif // LEDWIDGET_H
