#include <iostream>
template <typename T>
class Sqlist{
public:
    typedef int sqint;
protected:
    typedef struct list{
        T _data;
        list *_next;
        list(T dt):_data(dt),_next(nullptr){};
        list():_next(nullptr){};
    } list;
    list *head, *last;
    sqint size;
    typename Sqlist<T>::list *_get_index(sqint index){
        if (index<0||index>=size)
            return nullptr;
        list *temp=head;
        while (index--)
            temp=temp->_next;
        return temp->_next;
    }
    typename Sqlist<T>::list *_get_former(sqint index){
        if (index<0||index>=size)
            return nullptr;
        list *temp=head;
        while (index--)
            temp=temp->_next;
        return temp;
    }
public:
    Sqlist():size(0), head(nullptr){
        head = new list;
        last = head;
    }
    void append(T data){
        last->_next = new list(data);
        last = last->_next;
        size++;
    }
    void add(T data){
        if (size==0){
            append(data);
            return;
        }
        list *temp = new list(data);
        temp->_next = head->_next;
        head->_next = temp;
        size++;
    }

    void print_list() const{
        for (auto iter = head; iter->_next!=nullptr; iter = iter->_next){
            std::cout << iter->_next->_data << std::endl;
        }
    }
    void pop(){
        if (size==0)
            return;
        list *newlast=head;
        while (newlast->_next->_next!=nullptr)
            newlast=newlast->_next;
        delete last;
        last=newlast;
        last->_next=nullptr;
        size--;
    }
    void pop_front(){
        if (size==0)
            return;
        list *newhead=head->_next->_next;
        delete head->_next;
        head->_next=newhead;
        size--;
        if (size==0)
            last=head;
    }
    void insert(sqint index, T data){
        if (index<0||index>size)
            return;
        list *in_point=\
            index?_get_index(index-1):head;
        list *new_in=new list(data);
        new_in->_next=in_point->_next;
        in_point->_next=new_in;
        if (index==size)
            last=new_in;
        size++;
    }
    T *get(sqint index){
        if (index<0||index>=size)
            return nullptr;
        return &(_get_index(index)->_data);
    }
    T *get_head() const{
        return size?&(head->_next)->_data:nullptr;
    }
    T *get_last() const{
        return size?&(last->_data):nullptr;
    }
    void reverse(){
        if (size<=1)
            return;
        list *temp1=head->_next, *temp2=temp1->_next, *temp=nullptr;
        temp1->_next=nullptr;
        while (temp2!=nullptr){
            temp=temp2->_next;
            temp2->_next=temp1;
            temp1=temp2;
            temp2=temp;
        }
        temp=head->_next;
        head->_next=last;
        last=temp;
    }
    void remove(sqint index){
        if (index<0||index>=size)
            return;
        list *former = index?_get_index(index-1):head,\
        *next = former->_next->_next;
        delete former->_next;
        former->_next = next;
        size--;
        if (index==size)
            last = former;
    }
    void swap(sqint fst, sqint snd){
        if (fst<0||fst>=size||snd<0||snd>=size||fst==snd)
            return;
        if (fst>snd){
            sqint temp=fst;fst=snd;snd=temp;
        }
        list *fst_former=_get_former(fst),\
        *snd_former=_get_former(snd),*temp;
        temp=fst_former->_next;
        fst_former->_next=snd_former->_next;
        snd_former->_next=temp;
        temp=fst_former->_next->_next;
        fst_former->_next->_next=snd_former->_next->_next;
        snd_former->_next->_next=temp;
        if (snd==size-1)
            last=snd_former->_next;
    }
    void clear(){
        for (list *del=head->_next,*temp=del;\
            del!=nullptr;del=temp,size--){
            temp=del->_next;
            delete del;
        }
        last = head;
    }
    sqint get_size() const{
        return size;
    }
    ~Sqlist(){
        list *iter = head, *itd = head;
        while (iter!=nullptr){
            itd=iter->_next;
            delete iter;
            iter=itd;
        };
    }
};

template <typename T>
class SortList:public Sqlist<T>{
protected:
    typedef typename Sqlist<T>::list list;
    static list *_get_middle(list *first){
        if (first==nullptr)
            return nullptr;
        list *middle=first,*last=first;
        for (;last->_next!=nullptr&&last->_next->_next!=nullptr;\
            last=last->_next->_next){
            middle=middle->_next;
        }
        return middle;
    }
    static list *_merge_sort(list *hd){
        if (hd==nullptr||hd->_next==nullptr)
            return hd;
        list *middle=_get_middle(hd)->_next;
        _get_middle(hd)->_next=nullptr;
        list *head1=_merge_sort(hd);
        list *head2=_merge_sort(middle);
        return merge_list(head1,head2);
    }
public:
    static list *merge_list(list *head1,list *head2){
        if (head1==nullptr) return head2;
        if (head2==nullptr) return head1;
        list *head,*traverse;
        if (head1->_data<=head2->_data){
            head=head1;head1=head1->_next;
        } else {
            head=head2;head2=head2->_next;
        }
        traverse=head;
        while (true){
            if (head1==nullptr){
                traverse->_next=head2;break;
            }
            if (head2==nullptr){
                traverse->_next=head1;break;
            }
            if (head1->_data<=head2->_data){
                traverse->_next=head1;traverse=traverse->_next;head1=head1->_next;
            } else {
                traverse->_next=head2;traverse=traverse->_next;head2=head2->_next;
            }
        }
        return head;
    }
    void merge_sort(){
        if (Sqlist<T>::size<=1) return;
        _merge_sort(Sqlist<T>::head->_next);
        Sqlist<T>::head->_next=_merge_sort(Sqlist<T>::head->_next);
        Sqlist<T>::last=Sqlist<T>::_get_index(Sqlist<T>::size-1);
    }
};
