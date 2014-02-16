#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mybot.h"

//struct MSG;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    Ui::Widget *ui;
    MyBot bot;
protected:
    virtual bool nativeEvent(const QByteArray & eventType, void * message, long * result);
};

#endif // WIDGET_H
