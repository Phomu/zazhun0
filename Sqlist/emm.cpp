#include <iostream>
typedef struct list{
    int _data;
    list *_next;
    list(int dt):_data(dt){
        _next = nullptr;
    };
    list(){};
} list;
int main(){
    list *head=new list;
    //list *tail=new list;
    //delete head;
    //head = new list;
    //delete head;
    //std::cout << head << std::endl;
    //head = new list;
    //delete head;
    //std::cout << head << std::endl;
    //head = new list;
    //delete head;
    //std::cout << head << std::endl;
    //head = new list;
    //delete head;
    //std::cout << head << std::endl;
    //head = new list;
    //tail = new list;
    //delete tail;
    delete head;
    //std::cout << tail << std::endl;
    std::cout << head << std::endl;
    return 0;
}
