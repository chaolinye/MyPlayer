#include "SliderForVideo.h"


SliderForVideo::SliderForVideo(Qt::Orientation type,QWidget *parent) :
        QSlider(type,parent)
{

    setMouseTracking(true);
    setStyleSheet(
                "QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 5px; border-radius: 3px;opacity: 200;}"
                "QSlider::groove:horizontal {                                "
                "     border: 1px   solid #999999;                           "
                "     height: 0px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::groove:hover:horizontal {                          "
                "     border: 1px   solid #999999;                           "
                "     height: 5px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::handle:horizontal {                                "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle05.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:hover:horizontal {                          "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle02.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:pressed:horizontal{                         "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle01.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                "}                                                           "
                "                                                            "
                "QSlider::sub-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(11, 119, 225, 255), stop:0.65 rgba(11,119, 225, 255), stop:1 rgba(92, 184, 254, 255));                      "
                "}                                                           "
                "QSlider::add-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:1, stop:0 rgba(53,53,53, 255));  "
                "}"
                );

}
/*重写鼠标按下事件实现点到哪里播放哪里*/
void SliderForVideo::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()&Qt::LeftButton)
    {
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos*(maximum() - minimum()) + minimum());
    emit sliderMoved(pos * (maximum() - minimum()) + minimum());
    }
    else return;
}
/*重写鼠标进入事件slider的样式*/
void SliderForVideo::enterEvent(QEvent *)
{
    setStyleSheet(
                "QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 5px; border-radius: 3px;opacity: 200;}"
                "QSlider::groove:horizontal {                                "
                "     border: 1px   solid #999999;                           "
                "     height: 0px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::groove:hover:horizontal {                          "
                "     border: 1px   solid #999999;                           "
                "     height: 5px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::handle:horizontal {                                "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle02.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:hover:horizontal {                          "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle02.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:pressed:horizontal{                         "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle01.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                "}                                                           "
                "                                                            "
                "QSlider::sub-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(11, 119, 225, 255), stop:0.65 rgba(11,119, 225, 255), stop:1 rgba(92, 184, 254, 255));                      "
                "}                                                           "
                "QSlider::add-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:1, stop:0 rgba(53,53,53, 255));  "
                "}"
                );
}
/*重写鼠标离开事件的样式*/
void SliderForVideo::leaveEvent(QEvent *)
{
    setStyleSheet(
                "QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 5px; border-radius: 3px;opacity: 200;}"
                "QSlider::groove:horizontal {                                "
                "     border: 1px   solid #999999;                           "
                "     height: 0px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::groove:hover:horizontal {                          "
                "     border: 1px   solid #999999;                           "
                "     height: 5px;                                           "
                "     margin: 0px 0py;                                       "
                "     left: 6px; right: 6px;                                 "
                " }                                                          "
                "QSlider::handle:horizontal {                                "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle05.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:hover:horizontal {                          "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle02.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                " }                                                          "
                "QSlider::handle:pressed:horizontal{                         "
                "     border: 1px solid #5c5c5c;                             "
                " border-image:url(:/images/handle01.png);                         "
                "     width: 20px;                                           "
                "     margin: -8px -8px -8px -8px;                           "
                "}                                                           "
                "                                                            "
                "QSlider::sub-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(11, 119, 225, 255), stop:0.65 rgba(11,119, 225, 255), stop:1 rgba(92, 184, 254, 255));                      "
                "}                                                           "
                "QSlider::add-page:horizontal{                               "
                " background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:1, stop:0 rgba(53,53,53, 255));  "
                "}"
                );
}

