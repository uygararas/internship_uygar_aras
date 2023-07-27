#include "ledwidget.h"
#include <QPainter>
#include <QStyleOptionFocusRect> // Include this for handling focus rectangle

LedWidget::LedWidget(const QString& name, QWidget* parent) : QWidget(parent), m_name(name), m_isOn(false)
{
    setFixedSize(20, 20); // Set the fixed size for the LED widget
    setFocusPolicy(Qt::NoFocus); // Set the focus policy to NoFocus to remove the focus rectangle
    setLedState(m_isOn); // Update the LED state and appearance
}

void LedWidget::setLedState(bool isOn)
{
    m_isOn = isOn;
    update(); // Update the widget appearance
}

void LedWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Create a gradient to give the LED a 3D effect
    QRadialGradient gradient(rect().center(), rect().width() / 2, rect().center());
    gradient.setColorAt(0, QColor(0, m_isOn ? 225 : 50, 0)); // Center color (light green when on, dark green when off)
    gradient.setColorAt(1, QColor(0, m_isOn ? 170 : 10, 0));  // Outer color (darker green when on, even darker when off)

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen); // No border
    painter.drawEllipse(rect());

    // You can also add additional visual elements, such as a border or light glow effect.
}
