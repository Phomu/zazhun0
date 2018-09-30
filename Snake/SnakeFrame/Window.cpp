//
//  Window.cpp
//  SnakeFrame
//
//  Created by Yitong Liu on 8/2/18.
//  Copyright © 2018 Yitong Liu. All rights reserved.
//

#include <math.h>
#include <cstring>
#include "Window.hpp"
/*Firstly No Color*/


Wind::Wind(const winPpt y, const winPpt x,\
           const winPpt height, const winPpt width,\
           const winPpt visibility, winTtl title_):\
y_(y), x_(x), height_(height), width_(width),\
visibility_(visibility), title(title_){
    if (title==nullptr)//make the nullptr title an empty string
        title="";
    win_=newwin(height_, width_, y_, x_);
}
Wind::~Wind(){
    if (win_!=nullptr){
        mvwprintw(win_, 0, 0, "~Wind");
        wclear(win_);
        wrefresh(win_);
        delwin(win_);
    }
}
void Wind::show_win() const{
//    wclear(win_);//frustration
    wrefresh(win_);
}
void Wind::show_box() const{
    box(win_, 0, 0);
    wrefresh(win_);
}
void Wind::show_title() const{
//    if (strlen(title)>=width_)//not printing strings overflow the width
//        return;
    mvwprintw(win_, 0, (width_-(winPpt)strlen(title))/2, "%s", title);
    wrefresh(win_);
}
void Wind::show(const Wind::winPpt bo, const Wind::winPpt ti) const{
    show_win();
    if (bo)
        show_box();
    if (ti)
        show_title();
}
void Wind::set_has_border(const winPpt border){
    has_border_= border;
}
Wind::winPpt Wind::has_border() const{
    return has_border_;
}
void Wind::set_visible(const winPpt visible){
    visibility_=visible;
}
Wind::winPpt Wind::is_visible() const{
    return visibility_;
}
void Wind::get_coordinate(winPpt& y, winPpt& x) const{
    y=y_;
    x=x_;
}
void Wind::get_size(winPpt& height, winPpt& width) const{
    height=height_;
    width=width_;
}
void Wind::clr() const{
    wclear(win_);
    wrefresh(win_);
}
WINDOW* const Wind::inner() const{
    return win_;
}

//Window for information display
Info_win::Info_win(const winPpt y, const winPpt x,\
         const winPpt height, const winPpt width,\
                   const winPpt visibility, winTtl title_):\
Wind(y, x, height<3?3:height, width<3?3:width, visibility, title_),win_wrap_(nullptr)
//height, width can hold a subwindow
//content not added
{
    winPpt wid(width-2), hei(height-2), xx(x+1), yy(y+1);//conent wrap
    if (wid<width&&hei<height)//absolute coor, should be test for the change of init list
         //unsigned not negative, inspect subwindow size
         win_wrap_=new Wind(yy, xx, hei, wid, visibility, "");//visibility follow the parent Wind
}
Info_win::~Info_win(){
    if (win_wrap_!=nullptr)
        delete win_wrap_;
}
void Info_win::set_visible(const winPpt visible){
    visibility_=visible;
    if (win_wrap_!=nullptr)
        win_wrap_->set_visible(visible);
}
void Info_win::show_content() const{
    if (win_wrap_!=nullptr){
        wmove(win_wrap_->inner(), 0, 0);
        for (auto iter=info_list.begin();/*std::deque<winString>::const_iterator*/\
             iter!=info_list.end();iter=std::next(iter)){
            wprintw(win_wrap_->inner(), "%s", *iter);
            if (iter+1!=info_list.end())
                wprintw(win_wrap_->inner(), "\n\r");//\r can be removed
        }
        wrefresh(win_wrap_->inner());
    }
//    wprintw(win_wrap_->inner(), "const char *, ...");
}
//overflow handle
//        winPpt tempW, tempH;
//            win_wrap_->get_size(tempH, tempW);
//            if (getcury(win_wrap_->inner())<tempH)
//                break;
void Info_win::show(const winPpt bo, const winPpt ti) const{
    Wind::show(bo, ti);
    show_content();
}
void Info_win::add_content(winString* content_list, const winPpt count){
    for (int i=0; i<count; i++)
        info_list.push_back(content_list[i]);
}
void Info_win::set_pad(const winPpt le, const winPpt ri,\
                       const winPpt tp, const winPpt bt){
    if (tp<1||bt<1||le<1||ri<1||\
        le+ri>width_-2||le>width_-2||ri>width_-2||\
        tp+bt>=height_-2||tp>height_-2||bt>height_-2)//not considered carefully
        return;
    winPpt wid(width_-le-ri), hei(height_-tp-bt), xx(x_+le), yy(y_+tp);//conent wrap
    Wind* newWindow=new Wind(yy, xx, hei, wid, visibility_, "");//
    delete win_wrap_;
    win_wrap_=newWindow;
}

void Info_win::clr() const{
    wclear(win_wrap_->inner());
    wrefresh(win_wrap_->inner());
    Wind::clr();
}
//test virtual function
//wprintw(win_wrap_->inner(), "const char *, ...");
//wrefresh(win_wrap_->inner());


//Advanced Menu_win derived from Info_win
Menu_win::Menu_win(const winPpt y, const winPpt x,\
                   const winPpt height, const winPpt width,\
                   const winPpt visibility, winTtl title_):\
Wind(y, x, height, width, visibility, title_),\
Info_win(0, 0, 0, 0, 0, nullptr), selected_(winPpt(-1)), highlight_(winPpt(-1))
//set highlight, selected to abnormal value
//Info_win constructor skips the construction of Wind
{
    ;
}

void Menu_win::show_content() const{
    if (win_wrap_!=nullptr){
        wmove(win_wrap_->inner(), 0, 0);
        auto iter=info_list.begin();
        winPpt it(0);//used for highlight
        for (;/*std::deque<winString>::const_iterator*/\
             iter!=info_list.end();(iter=std::next(iter)),it++){
            if (highlight_==it)
                wattron(win_wrap_->inner(), A_REVERSE);
            wprintw(win_wrap_->inner(), "%s", *iter);
            if (highlight_==it)
                wattroff(win_wrap_->inner(), A_REVERSE);//Too much redundant code
            if (iter+1!=info_list.end())
                wprintw(win_wrap_->inner(), "\n\r");//\r can be removed
        }
        wrefresh(win_wrap_->inner());
    }
}

void Menu_win::handle(){
    keypad(win_wrap_->inner(), TRUE);
    bool flag(true);
    while (flag){
        flushinp();//throw away any former input
        switch (getch()) {
            case KEY_DOWN:
                highlight_=(highlight_+1)%info_list.size();
                break;
            case KEY_UP:
                highlight_=(highlight_-1+(winPpt)info_list.size())%(winPpt)info_list.size();
                break;
            case '\n':
            case KEY_ENTER:
                if (highlight_==winPpt(-1))
                    break;
                selected_=highlight_;
//                highlight_=0;//not necessary
//                wclear(win_wrap_->inner());//not necessary
                flag=false;
            default:;
        }
//        if (flag)
        this->show_content();//the virtual show function of self
    }
    keypad(win_wrap_->inner(), FALSE);
}

Menu_win::winPpt Menu_win::get_selected() const{
    return selected_;
}






//void color_config(){
////    init_color(COLOR_RED, 00,0,0);
//    init_pair(1, COLOR_BLACK, COLOR_WHITE);
//}




//
//Wind::Wind(const windPpt a,const windPpt b,\
//           const windPpt c,const windPpt d, const windPpt v):\
//x_(b), y_(a), w_(c), h_(d), visible_(v){
//    win=newwin(h_, w_, y_, x_);
//    wbkgd(win, COLOR_PAIR(1));
//    nodelay(win, TRUE);
//};
//void Wind::show() const{
//    if (visible_){
//        wclear(win);//???
//        box(win, 0, 0);
//        wrefresh(win);
//    }
//
//}
//Wind::~Wind(){
//    if (win!=nullptr)
//        delwin(win);
//}
//
////    windPpt x_, y_, w_, h_;
