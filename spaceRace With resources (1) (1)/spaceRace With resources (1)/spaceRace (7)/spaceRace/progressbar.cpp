#include "ProgressBar.h"

ProgressBar::ProgressBar(QGraphicsItem* parent)
    : QGraphicsItem(parent), value(0), maxValue(100), color(Qt::green) {}

void ProgressBar::setValue(float value) {
    this->value = value;
    update();
}

void ProgressBar::setMaxValue(float maxValue) {
    this->maxValue = maxValue;
}

void ProgressBar::setColor(const QColor& color) {
    this->color = color;
}

QRectF ProgressBar::boundingRect() const {
    return QRectF(0, 0, 100, 10); // Size of the progress bar
}

void ProgressBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());

    painter->setBrush(color);
    painter->drawRect(0, 0, (value / maxValue) * 100, 10);
}
