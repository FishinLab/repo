#include <iostream>

using namespace std;

struct node{
    node* next;
    int val;
}_node;

int main(int argc, const char* argv[]){
    int length = argc - 1;    
    node* head = new node;
    node* curr = head;
    for(int i = 0; i < length; ++i){
        node* new_one = new node;
        new_one->val = atoi(argv[i + 1]);
        curr->next = new_one;
        curr = new_one;
    }
    //operations on list
    delete head;
    delete curr;
    return 0;
}
