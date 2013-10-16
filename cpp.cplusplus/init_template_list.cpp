#include <iostream>

using namespace std;

template<class T>
struct node{
    node* next;
    T* val;
}_node;

int main(){
    //get nodes data operations

    node* head = new node;
    node* curr = head;
    while(true){
        node* new_one = new node;
        new_one->val = NULL; 
        curr->next = new_one;
        curr = new_one;
    }
    delete curr;
    return 0;
}
