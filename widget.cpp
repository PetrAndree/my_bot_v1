#include "widget.h"
#include "ui_widget.h"

#include <windows.h>
#include <iostream>


int inx=0;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    RegisterHotKey((HWND)Widget::winId(), 101, MOD_ALT, VK_F1);
    RegisterHotKey((HWND)Widget::winId(), 102, MOD_ALT, VK_F2);
    RegisterHotKey((HWND)Widget::winId(), 103, MOD_ALT, VK_F3);
    RegisterHotKey((HWND)Widget::winId(), 104, MOD_ALT, VK_F4);
    RegisterHotKey((HWND)Widget::winId(), 105, MOD_ALT, VK_F5);

}

Widget::~Widget()
{
    delete ui;
}

//POINT pt;

bool Widget::nativeEvent(const QByteArray & eventType, void * message, long * result){
    Q_UNUSED(result);
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    if(msg->message!=WM_HOTKEY)return false;

    switch(msg->wParam){
    case 101: // Alt-F1 - запуск бота
        bot.run();
        return true;
    case 102: // Alt-F2 - inx++
        if(inx<points_cnt-1)inx++;
        return true;
    case 103: // Alt-F3 - Проверить точку inx
        bot.move_to(inx);
        return true;
    case 104: // Alt-F4 - Запомнить точку inx
        GetCursorPos(&bot.point[inx]);
        return true;
    case 105: // Alt-F5 - Вывести в консоль массив координат
        for(int i=0;i<points_cnt;i++){
            std::cout << "{" << bot.point[i].x << "," << bot.point[i].y << "}, //" << i << std::endl;
        }
        return true;
    }

    return false;
}
