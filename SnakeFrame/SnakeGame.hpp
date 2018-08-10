//
//  SnakeGame.hpp
//  SnakeFrame
//
//  Created by Yitong Liu on 8/5/18.
//  Copyright © 2018 Yitong Liu. All rights reserved.
//

#ifndef SnakeGame_hpp
#define SnakeGame_hpp

#include "Window.hpp"

class XY_coordinate{
public:
    typedef int coor;
    XY_coordinate(const coor y, const coor x);
    const coor& getX() const;
    const coor& getY() const;
    void setX(const coor x);
    void setY(const coor y);
    bool operator==(const XY_coordinate xy) const ;
protected:
    coor x_, y_;
};

//class SnakeCoor: public XY_coordinate{
//public:
//
//};

//class Snake{
//protected:
//    typedef unsigned int length;
//public:
//    typedef int direction;
//    typedef const int DIRECTION;
//    static DIRECTION STAY, UP, DOWN, LEFT, RIGHT;
//    Snake(const XY_coordinate head);
//    void move();
//    void change_direction(const direction dir);
//    const XY_coordinate& getHead() const;
//    void set_growth(const length len=1);
//    //Functions for test
//    void show() const;
//protected:
//    bool valid_direction(const direction& dir);
//    std::deque<XY_coordinate> body_;
//    direction direct_;
//    length len_to_grow;
//};

class SnakeMain{
public:
    typedef unsigned int dif;
    static const Wind::winPpt POSX, POSY, WINWID, WIDHEI;
    SnakeMain();
    void play();
    bool successed() const;
    void set_difficulty(const dif d);
protected:
    Wind box_win_;
    Wind win_;
    class Snake{
    protected:
        typedef unsigned int length;
    public:
        typedef int direction;
        typedef const int DIRECTION;
        static DIRECTION STAY, UP, DOWN, LEFT, RIGHT;
        Snake(const XY_coordinate head);
        void move();
        void change_direction(const direction dir);
        const XY_coordinate& getHead() const;
        void set_growth(const length len=1);
        //Functions for test
//        void show() const;//finished by SnakeMain
//    protected://accessed by snakemain
        bool valid_direction(const direction& dir);
        std::deque<XY_coordinate> body_;
        direction direct_;
        length len_to_grow;
    } snake_;
    std::deque<XY_coordinate> food_;
    bool generate_food_();//return false if failed
    const std::deque<XY_coordinate>::const_iterator food_overlap_() const;//if food appears on snake,
    //return 1st food object
    void show_() const;//add display of food
    bool crash_() const;
    bool success_;
    dif difficulty_;//speed of halfdelay
};


class SnakeGame{
protected:
    static const char* grt[];//initialize here??
    static const char* choices[];
    static const char* diffic[];
    static const char* success[];
public:
    void game_start();
    
    
};







#endif /* SnakeGame_hpp */
