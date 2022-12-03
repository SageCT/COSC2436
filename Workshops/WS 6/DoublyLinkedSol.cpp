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
    node* temp= new node;
    temp->val=value;
    temp->next=temp->prev=nullptr;
    if(head==nullptr)
        head=tail=temp;
    else{
        head->prev=temp;
        temp->next=head;
        head=temp;
    }
    size++;
}

void doublyLinked::addToPos(int value, int pos){
    node* temp = new node;
    temp-> val = value;
    temp->next=temp->prev = nullptr;
    if(pos > size)
        return;
    else if(pos!=0){
    node* cur=head;
    for(int i=1;i<pos;i++){
        cur=cur->next;
    }
    temp->next=cur->next;
    temp->prev=cur->prev;
    cur->next->prev=temp; //links the node after temp to temp
    cur->next=temp; //links the node before temp to temp
    }
    else{
        head->prev=temp;
        temp->next=head;
        head=temp;
    }
    size++;
}

void doublyLinked::reverse(){
    node* cur=head;
    node* prev=nullptr;
    while(cur!=nullptr){
        prev=cur->prev;
        if(prev==nullptr)//at current head
            tail=cur;
        cur->prev=cur->next;
        cur->next=prev;
        head=cur; //updates head as moving
        cur=cur->prev;
    }
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