#include "mybot.h"
#include <unistd.h>
#include <math.h>

MyBot::MyBot() :
    // Массив координат оргонов управления (по которым мы будем кликать мышкой)
    point({
      {100,100}, // 0 - menu
      {130,130}, // 1 - elm_1
    })
{
}

void MyBot::run(){
    rclick_to(menu);  // кликнем правой кнопкой для вызова контекстного меню
    lclick_to(elm_1); // кликнем левой кнопкой по строке меню
}

#define width 1920
#define height 1080

void MyBot::move_to(int inx){
    int x=point[inx].x;
    int y=point[inx].y;
    POINT pt;
    GetCursorPos(&pt);

    int from_x=pt.x;
    int from_y=pt.y;

    int to_x=x;
    int to_y=y;

    int dx=to_x-from_x;
    int dy=to_y-from_y;

    float fdx;
    float fdy;
    int move_cnt;

    if(abs(dx)>abs(dy) && dx!=0){
        fdx=dx<0? -1.0 :1.0;
        fdy=(float)dy/abs(dx);
        move_cnt=abs(dx);
    }
    else if(dy!=0){
        fdy=dy<0? -1.0 :1.0;
        fdx=(float)dx/abs(dy);
        move_cnt=abs(dy);
    }
    else return;

    // двинуть за 1 секунду
    int time=1000000/move_cnt;
    float fx=from_x;
    float fy=from_y;
    for(int i=0;i<move_cnt;i++){
        fy+=fdy;
        fx+=fdx;
        int nx=(fx)*(65536 / width);
        int ny=(fy)*(65536 / height);
        mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,nx,ny,0,0);
        usleep(time);
    }
    usleep(50000);
}

void MyBot::lclick_to(int inx){
    move_to(inx);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    usleep(50000);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    usleep(100000);
}

void MyBot::rclick_to(int inx){
    move_to(inx);
    mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
    usleep(50000);
    mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
    usleep(100000);
}

void MyBot::drag(int from_inx, int to_inx){
    move_to(from_inx);
    usleep(50000);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    usleep(70000);
    move_to(to_inx);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    usleep(30000);
}
