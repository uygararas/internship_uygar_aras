// gloweffect.cpp
#include "gloweffect.h"
#include <QPainter>

GlowEffect::GlowEffect(QObject *parent) : QGraphicsEffect(parent)
{
}

QRectF GlowEffect::boundingRectFor(const QRectF &sourceRect) const
{
    return sourceRect;
}

void GlowEffect::draw(QPainter *painter)
{
    if (sourceIsPixmap()) {
        QPixmap px = sourcePixmap(Qt::LogicalCoordinates);
        QPixmap copy(px);

        // Create a blurred copy of the pixmap
        QPainter blurPainter(&copy);
        blurPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        blurPainter.fillRect(copy.rect(), QColor(0, 0, 0, 120));
        blurPainter.end();

        // Draw the original pixmap
        painter->drawPixmap(0, 0, px);

        // Draw the blurred pixmap on top of the original pixmap
        painter->drawPixmap(0, 0, copy);
    }
}
