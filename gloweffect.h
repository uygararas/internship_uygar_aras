// gloweffect.h
#ifndef GLOWEFFECT_H
#define GLOWEFFECT_H

#include <QGraphicsEffect>

class GlowEffect : public QGraphicsEffect
{
public:
    GlowEffect(QObject *parent = nullptr);

protected:
    QRectF boundingRectFor(const QRectF &sourceRect) const override;
    void draw(QPainter *painter) override;
};

#endif // GLOWEFFECT_H
