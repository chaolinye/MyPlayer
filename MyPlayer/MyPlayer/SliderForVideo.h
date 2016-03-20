#ifndef SLIDERFORVIDEO_H
#define SLIDERFORVIDEO_H
#include <QtGui>
#include <QSlider>

class SliderForVideo : public QSlider {
    Q_OBJECT
public:
    explicit SliderForVideo(Qt::Orientation, QWidget *parent = 0);


signals:

protected:
    void mousePressEvent(QMouseEvent * ev);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

};
#endif // SLIDERFORVIDEO_H
