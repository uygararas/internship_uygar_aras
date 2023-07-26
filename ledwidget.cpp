// ledwidget.cpp
#include "ledwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

LedWidget::LedWidget(const QString& name, QWidget *parent) : QWidget(parent), m_isOn(false)
{
    setFixedSize(80,80); // Increase the size of the LED widget to allow more space for the name label

    m_nameLabel = new QLabel(name); // Create the name label
    m_nameLabel->setAlignment(Qt::AlignCenter); // Center-align the name label

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_nameLabel);
    setLayout(layout); // Set the layout with the name label

    setLedState(m_isOn); // Update the LED state and appearance
}

void LedWidget::setLedState(bool isOn)
{
    m_isOn = isOn;
    update(); // Update the widget appearance
}

void LedWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_isOn)
        painter.setBrush(QColor(0, 255, 0)); // Set the LED color to green when on
    else
        painter.setBrush(QColor(255, 0, 0)); // Set the LED color to red when off

    // Adjust the ellipse position to leave space for the name label
    painter.drawEllipse(rect().adjusted(2, 20, -2, -2));
}
