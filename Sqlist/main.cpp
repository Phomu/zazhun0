#include "sqlist.hpp"
int *test();
void he();
int main(){
//    int *ptt=test();
//    std::cout << ptt << std::endl;
//    std::cout << *ptt << std::endl;
he();
    return 0;
}
void he(){
    SortList<int> sq;
    for (int i=0;i<2;i++)
        sq.append(2*i);
    sq.append(1);
    sq.print_list();
    std::cout << std::endl;
    sq.merge_sort();
    sq.print_list();
    if (sq.get_last())
        std::cout << *sq.get_last() << std::endl;
    else std::cout << "nullptr" << std::endl;
}

//int *test(){
//    Sqlist<int> sq;
//    sq.clear();
//    sq.insert(0,1);
//    sq.insert(0,0);
//    sq.insert(2,2);
//    sq.add(-1);
//    sq.append(3);
//    sq.reverse();
//    sq.reverse();
//    sq.swap(0,sq.get_size()-1);
//    int *p=sq.get_last();
//    sq.remove(sq.get_size()-1);
//    sq.print_list();
//    if (p)
//        std::cout << "last one is " << *p << std::endl;
//    else printf("nullptr\n");
//    std::cout << sq.get_size() << std::endl;
//    return p;
//}
