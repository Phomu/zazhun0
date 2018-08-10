//
//  SnakeGame.cpp
//  SnakeFrame
//
//  Created by Yitong Liu on 8/5/18.
//  Copyright © 2018 Yitong Liu. All rights reserved.
//

#include <math.h>
#include "SnakeGame.hpp"


XY_coordinate::XY_coordinate(const coor y, const coor x):x_(x), y_(y){
    
}
bool XY_coordinate::operator==(const XY_coordinate xy) const{
    return (xy.x_==x_&&xy.y_==y_);
}
const XY_coordinate::coor& XY_coordinate::getX() const{
    return x_;
}
const XY_coordinate::coor& XY_coordinate::getY() const{
    return y_;
}
void XY_coordinate::setX(const coor x){
    x_=x;
}
void XY_coordinate::setY(const coor y){
    y_=y;
}
const Wind::winPpt SnakeMain::WINWID=(16);//Size of snake window
const Wind::winPpt SnakeMain::WIDHEI=(8);//???
//set COLS=80, LINES=24
const Wind::winPpt SnakeMain::POSX=(80/2-WINWID/2);//prior to calling initscr!
const Wind::winPpt SnakeMain::POSY=(24/2-WIDHEI/2);


SnakeMain::SnakeMain():box_win_(POSY-1, POSX-1, WIDHEI+2, WINWID+2, 1, ""),/*POSY-1, POSX-1*/\
win_(POSY, POSX, WIDHEI, WINWID, 1, ""), snake_(XY_coordinate(0,0)),\
success_(false),difficulty_(2){//snake based on win_
    box_win_.show_box();
//    show_();
//    mvwprintw(box_win_.inner(), 1,1, "%d", POSX);//test
    win_.show_box();
    wrefresh(box_win_.inner());
}

SnakeMain::Snake::DIRECTION SnakeMain::Snake::STAY(0);
SnakeMain::Snake::DIRECTION SnakeMain::Snake::UP(1);
SnakeMain::Snake::DIRECTION SnakeMain::Snake::DOWN(2);
SnakeMain::Snake::DIRECTION SnakeMain::Snake::LEFT(3);
SnakeMain::Snake::DIRECTION SnakeMain::Snake::RIGHT(4);
SnakeMain::Snake::Snake(const XY_coordinate head):direct_(STAY),len_to_grow(0){
    body_.push_back(head);
}
const XY_coordinate& SnakeMain::Snake::getHead() const{
    return body_.front();
}
void SnakeMain::Snake::move(){
    const XY_coordinate::coor xx(body_.front().getX()), yy(body_.front().getY());
    XY_coordinate new_head(direct_==UP?yy-1:(direct_==DOWN?yy+1:yy),\
                           direct_==LEFT?xx-1:(direct_==RIGHT?xx+1:xx));
    body_.push_front(new_head);
    if (len_to_grow!=0)
        len_to_grow--;
    else body_.pop_back();
}
void SnakeMain::Snake::change_direction(const direction dir){
    if (valid_direction(dir))
        direct_=dir;
}
bool SnakeMain::Snake::valid_direction(const direction& dir){
    if (((direct_==LEFT||direct_==RIGHT)&&(dir==LEFT||dir==RIGHT))\
            ||((direct_==UP||direct_==DOWN)&&(dir==UP||dir==DOWN))\
            ||(dir>RIGHT||dir<=STAY))//RIGHT==4
        return false;
    return true;
}
bool SnakeMain::successed() const{
//    success_=snake_.body_.size()>=10?true:false;
    return success_;//not necessary
}
////Functions for test
//void SnakeMain::Snake::show() const{
//    for (auto iter(body_.begin());iter!=body_.end();iter=std::next(iter))
//        mvwprintw(stdscr, (*iter).getY(), (*iter).getX(), "*");
//    refresh();
//}

void SnakeMain::Snake::set_growth(const length len){
    len_to_grow=len;
}

void SnakeMain::show_() const{
//    box_win_.show(1,1);
    win_.clr();
    //head is shown as '@'
    for (std::deque<XY_coordinate>::const_iterator iter(snake_.body_.begin()),hdd=iter;\
         iter!=snake_.body_.end();iter=std::next(iter))
        mvwprintw(win_.inner(), (*iter).getY(), (*iter).getX(), iter!=hdd?"*":"@");
    if (!food_.empty()){
        for (auto food:food_)
            mvwprintw(win_.inner(), food.getY(), food.getX(), "x");
    }//did not pop the food!!!
//    mvwprintw(win_.inner(), 0, 0, "%d", \
//              snake_.body_.front().getX());//test
//    wrefresh(win_.inner());
//    win_.show_box();
//    box_win_.show(1,1);
    win_.show(0,0);//wrefresh
}

bool SnakeMain::crash_() const{
    const XY_coordinate& hd=snake_.getHead();
    for (auto iter=snake_.body_.begin()+1;iter!=snake_.body_.end();iter++)
        if (*iter==hd)
            return true;
    Wind::winPpt width, height;
    win_.get_size(height, width);//made a mistake
    if (hd.getX()+1>width||hd.getY()+1>height||\
        hd.getX()==(Wind::winPpt)(-1)||hd.getY()==(Wind::winPpt)(-1))
        //winPpt unsigned int
        return true;
    return false;
}
void SnakeMain::set_difficulty(const dif d){
    difficulty_=(d>3?3:(d==0?1:d));//three level, unsigned int dif
    difficulty_*=3;
}
void SnakeMain::play(){
//    bool break_loop(false);
    box_win_.show_box();
    show_();
    while (true){
        halfdelay(difficulty_);//point of setting difficulty
        switch (getch()) {//wgetch
            case KEY_UP:
                snake_.change_direction(SnakeMain::Snake::UP);
                break;
            case KEY_DOWN:
                snake_.change_direction(SnakeMain::Snake::DOWN);
                break;
            case KEY_LEFT:
                snake_.change_direction(SnakeMain::Snake::LEFT);
                break;
            case KEY_RIGHT:
                snake_.change_direction(SnakeMain::Snake::RIGHT);
                break;
//            case '\n':
//                snake_.set_growth();
//                break;
//            case ERR:
//                break;
//            case KEY_ENTER:
//                break_loop=true;
            default:;
        }
        flushinp();
        snake_.move();
        std::deque<XY_coordinate>::const_iterator food=food_overlap_();
        if (!(food==food_.end())){
            snake_.set_growth();//eat a piece of food
            food_.erase(food);
        }
        
        if (food_.empty())//generate food
            generate_food_();//maybe fail to generate any
        show_();
        if (crash_())
            break;
    }
    Wind::winPpt s_x,s_y;
    win_.get_size(s_y,s_x);
    success_=snake_.body_.size()>=s_y*s_x-1?true:false;//-1?
    
}

bool SnakeMain::generate_food_(){
    Wind::winPpt xx,yy;
    win_.get_size(yy, xx);
    XY_coordinate new_food(abs(rand())%yy,abs(rand())%xx);
    if (food_.end()==food_overlap_()){
        food_.push_back(new_food);
        return true;
    }
    return false;
}

const std::deque<XY_coordinate>::const_iterator SnakeMain::food_overlap_() const{
    for (std::deque<XY_coordinate>::const_iterator iter=food_.begin();\
         iter!=food_.end();iter=std::next(iter)){
        for (auto it=snake_.body_.begin();it!=snake_.body_.end();it=std::next(it)){
            if (*it==*iter)
                return iter;
        }
    }
    return food_.end();
}

const char* SnakeGame::grt[]={"Welcome","Press any key"};
const char* SnakeGame::choices[]={"-> Configure","-> Start!"};
const char* SnakeGame::diffic[]={"Set difficulty","1)   hard", "2)   normal", "3)   easy"};
const char* SnakeGame::success[]={"You win","You lose"};

void SnakeGame::game_start(){
    refresh();
    SnakeMain::dif di(1);
    Info_win* ptr_info= new Info_win(0,0,LINES,COLS,1,"Hungry Snake");
    ptr_info->add_content(grt,2);
    ptr_info->set_pad(COLS/2-(Wind::winPpt)strlen(*grt)/2,2,LINES/2-1,1);//
    ptr_info->show(1,1);
    getch();
    delete ptr_info;
    Menu_win* menu=new Menu_win(0,0,LINES,COLS,1,"Hungry Snake");
    menu->Wind::show(1,1);
    menu->set_pad(COLS/2-(Wind::winPpt)strlen(*choices)/2,2,LINES/2-1,1);
    menu->add_content(choices, 2);
    
    Info_win* dif_win=new Info_win(0,0,LINES,COLS,1,"Hungry Snake");
    dif_win->set_pad(COLS/2-(Wind::winPpt)strlen(*diffic)/2,2,LINES/2-3,1);
    dif_win->add_content(diffic,4);
    bool menu_loop(true);
    while (menu_loop)//1==start
    {
        menu->show_content();
        menu->handle();
        menu->clr();
        switch (menu->get_selected()) {
            case 0://config
                menu->show(1,1);
                dif_win->show_content();
                while ((di=getch()-'0')>3||di==0);
                dif_win->clr();
                menu->show(1,1);
                break;
            case 1:
                menu_loop=false;//start
                break;
            default:;
        }
    }
    delete dif_win;
    delete menu;
    
    Wind* wrapp=new Wind(0,0,LINES,COLS,1,"Hungry Snake");
    wrapp->show(1,1);
    SnakeMain* new_game=new SnakeMain;
    new_game->set_difficulty(di);
    
    new_game->play();
    bool successed=new_game->successed();
    delete new_game;
    ptr_info=new Info_win(0,0,LINES,COLS,1,"Hungry Snake");
    ptr_info->add_content(successed?success:success+1,1);
    ptr_info->set_pad(COLS/2-(Wind::winPpt)strlen(success[successed?1:0])/2,1,LINES/2-1);
    ptr_info->Wind::show(1,1);
    ptr_info->show_content();
    nocbreak();
    cbreak();
    getch();
    delete wrapp;
    delete ptr_info;
}



