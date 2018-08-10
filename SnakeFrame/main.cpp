//
//  main.cpp
//  SnakeFrame
//
//  Created by Yitong Liu on 8/2/18.
//  Copyright © 2018 Yitong Liu. All rights reserved.
//
//int argc, const char * argv[]
//#include <iostream>

#include "SnakeGame.hpp"

void test();

int main() {
    //basic config for curses terminal, no color
    initscr();curs_set(0);cbreak();noecho();keypad(stdscr, TRUE);
    wrefresh(stdscr);//invoked to enable customized window to be shown?
    
    SnakeGame snkg;
    snkg.game_start();
    

    endwin();
    return 0;
}
//    test();
//    SnakeMain *ptr=new SnakeMain;
//    SnakeMain& snk=*ptr;
//    snk.play();
//    delete ptr;
void test(){
//    Wind win(0, 0, 10, 10, 1, "Test Window");
//    Info_win win(0, 0, 10, 10, 1, "Test Window");
    Menu_win win(0, 0, LINES/2, COLS/2, 1, "Test Window");
    const char* list[]={"Hello!",\
        "This is a Info Board",\
        "For displaying information"};
    win.add_content(list, 3);
    win.set_pad(3,3,2,1);//(left, right, top, bottom)
    win.show(1,1);
    win.handle();
    clear();
    mvprintw(LINES-1, 0, "You have selected the '%d' choice", win.get_selected());
    refresh();
    getch();
}

////Test Snake
//XY_coordinate head(0,0);
//SnakeMain::Snake snake(head);
//
//bool break_loop(false), valid_input(true);
//while (true){
//    halfdelay(1);
//    //        nodelay(stdscr, TRUE);
//    switch (getch()) {
//        case KEY_UP:
//            snake.change_direction(SnakeMain::Snake::UP);
//            break;
//        case KEY_DOWN:
//            snake.change_direction(SnakeMain::Snake::DOWN);
//            break;
//        case KEY_LEFT:
//            snake.change_direction(SnakeMain::Snake::LEFT);
//            break;
//        case KEY_RIGHT:
//            snake.change_direction(SnakeMain::Snake::RIGHT);
//            break;
//        case '\n':
//            snake.set_growth();
//            break;
//        case ERR:
//            break;
//        case KEY_ENTER:
//            break_loop=true;
//        default:
//            valid_input=false;
//    }
//    flushinp();
//    if (valid_input)
//        snake.move();
//        valid_input=true;
//        snake.show();
//        if (break_loop)
//            break;
//}
////Snake test end


//Another test code
//Menu_win* win1=new Menu_win(0, 0, LINES/2, COLS/2, 1, "Window1");
//Menu_win* win2=new Menu_win(1, 1, LINES/2, COLS/2, 1, "Window2");
//win1->show();
//win2->show();
//getch();
//delete win2;//deleting a window will also remove the pattern on terminal
//win1->show(1,1);
//getch();
//delete win1;


//    win.show_win();
//    win.show_box();
//    win.show_title();
//    Wind* vPtr=&win;
//    vPtr->show(1,1);

//    vPtr->clr();
//    getch();


//void test(){
//    initscr();
//    curs_set(0);
//    cbreak();
//    noecho();
//    start_color();
//    color_config();
//    refresh();
//    Wind win(0,0,COLS/2,LINES/2);
//    Wind win2(0,0,COLS,LINES/3);
//    win2.show();
//    win.show();
//
//    getch();
//    endwin();
//}
//ungetch('q');
//printf("%c\n", getch());
