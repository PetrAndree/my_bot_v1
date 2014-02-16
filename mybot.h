#ifndef MYBOT_H
#define MYBOT_H

#include <windows.h>

// Индексы точек

enum {
    menu=0,
    elm_1,
    points_cnt
};

class MyBot
{
public:
    MyBot();
    void run();
    void move_to(int inx);
    void lclick_to(int inx);
    void rclick_to(int inx);
    void drag(int from_inx,int to_inx);
    POINT point[points_cnt];
};

#endif // MYBOT_H
