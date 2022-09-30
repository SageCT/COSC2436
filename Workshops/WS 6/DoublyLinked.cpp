#include <iostream>

struct node
{
    int val;
    node* next;
    node* prev;
};


class doublyLinked{
    private:
        node* head;
        node* tail;
        int size;
    public:
        doublyLinked();
        ~doublyLinked();
        void addToHead(int);
        void addToPos(int, int);
        void reverse();
        void print();
        void printFromTail();
};

doublyLinked::doublyLinked(){
    head=tail=nullptr;
    size=0;
}

doublyLinked::~doublyLinked(){
    node* cur=nullptr;
    while(head!=nullptr){
        cur=head;
        head=head->next;
        delete cur;
    }
}

void doublyLinked::addToHead(int value){

}

void doublyLinked::addToPos(int value, int pos){
    //assume add to be at that index, so 0 is before head and 1 is after head
    //assume that if pos is out of bounds, it is not added
}

void doublyLinked::reverse(){
    //good luck lmao.
    //Its just to get you to think cuz imo the exams may have some werid questions
    //prob not this hard but still
}

void doublyLinked::print(){
    if(head==nullptr){
        std::cout<<"its empty\n";
        return;
    }
    std::cout<<"Printing from head:\n";
    node* cur=head;
    while(cur!=nullptr){
        std::cout<<cur->val<<'\t';
        cur=cur->next;
    }
    std::cout<<'\n';
}

void doublyLinked::printFromTail(){
    if(tail==nullptr){
        std::cout<<"its empty\n";
        return;
    }
    std::cout<<"Printing from tail:\n";
    node* cur=tail;
    while(cur!=nullptr){
        std::cout<<cur->val<<'\t';
        cur=cur->prev;
    }
    std::cout<<'\n';
}

int main(){
    doublyLinked link;
    link.addToHead(4);
    link.addToHead(3);
    link.addToHead(2);
    link.addToHead(1);
    link.print();
    link.printFromTail();
    std::cout<<"now reversing :D\n";
    link.reverse();
    link.print();
    link.printFromTail();
    link.reverse();
    link.addToPos(-1, 0);
    link.addToPos(7,3);
    link.print();
    return 0;
}