#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QGraphicsItem>
#include <QPainter>

class ProgressBar : public QGraphicsItem {
public:
    ProgressBar(QGraphicsItem* parent = nullptr);

    void setValue(float value);
    void setMaxValue(float maxValue);
    void setColor(const QColor& color);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    float value;
    float maxValue;
    QColor color;
};

#endif // PROGRESSBAR_H
