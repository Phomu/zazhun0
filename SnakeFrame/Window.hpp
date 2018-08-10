//
//  Window.hpp
//  SnakeFrame
//
//  Created by Yitong Liu on 8/2/18.
//  Copyright © 2018 Yitong Liu. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <deque>
#include <ncurses.h>

//basic window with coor, size, visib, titl properties
class Wind{
public:
    typedef unsigned int winPpt;
    typedef const char *winTtl, *winString;
    Wind(const winPpt y, const winPpt x,\
         const winPpt height, const winPpt width,\
         const winPpt visibility, winTtl title_);//initialize
    virtual ~Wind();//delete window
    //functions for showing ignore/override visibility, has_border properties
    void show_win() const;
    void show_box() const;//default |-border using box()
    void show_title() const;//appear on second line of window
    virtual void show(const winPpt bo=1, const winPpt ti=0) const;//choose property to show
    winPpt is_visible() const;
    winPpt has_border() const;
    virtual void set_visible(const winPpt visible);
    void set_has_border(const winPpt border);
    void get_coordinate(winPpt& y, winPpt& x) const;//similar to ncurses getxxx()
    void get_size(winPpt& height, winPpt& width) const;//
    virtual void clr() const;
    WINDOW* const inner() const;//not recommended, to be optimized
protected:
    winPpt x_, y_, width_, height_, visibility_, has_border_;
    winTtl title=nullptr;
    WINDOW* win_;
};

//Advaned window for displaying info
class Info_win: virtual public Wind{//IMPORTANT! Menu_win initialize
public:
    //initialize Wind, add content member,
    //content wrapped in a SUBWINDOW, added using add_content method
    Info_win(const winPpt y, const winPpt x,\
         const winPpt height, const winPpt width,\
         const winPpt visibility, winTtl title_);
    virtual ~Info_win();//delete base instance and the subwindow
    void set_visible(const winPpt visible);
    virtual void set_pad(const winPpt le=1, const winPpt ri=1,\
                         const winPpt top=1, const winPpt bottom=1);
    virtual void show_content() const;
    virtual void show(const winPpt bo=1, const winPpt ti=0) const;
    void add_content(winString* content_list, const winPpt count=0);//cnt not specified, add nothing
    virtual void clr() const;
    
protected:
    std::deque<const char*> info_list;
    Wind* win_wrap_;
};

//Advanced window with choices handling ability
//keypad is on to read special keys
//derived from Info_win, may not be appropriate
class Menu_win: public Info_win{
public:
    Menu_win(const winPpt y, const winPpt x,\
                      const winPpt height, const winPpt width,\
                      const winPpt visibility, winTtl title_);
    void handle();
    virtual void show_content() const;
    winPpt get_selected() const;//start from 0
protected:
    winPpt highlight_;
    winPpt selected_;
};









#endif /* Window_hpp */

//void color_config();

//class Wind{
//    typedef unsigned int windPpt;
//public:
//    Wind(const windPpt a=0, const windPpt b=0,\
//         const windPpt c=COLS, const windPpt d=LINES, const windPpt v=1);
//    void show() const;
//    ~Wind();
//    WINDOW* win;
//    windPpt x_, y_, w_, h_, visible_;
//};
