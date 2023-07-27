#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

class QLabel; // Forward declaration of QLabel class

class LedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LedWidget(const QString& name, QWidget* parent = nullptr);
    void setLedState(bool isOn);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_name;
    bool m_isOn;
    QLabel* m_nameLabel; // Label for displaying the LED name
};

#endif // LEDWIDGET_H
