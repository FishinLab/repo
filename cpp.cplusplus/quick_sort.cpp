#include <iostream>

using namespace std;

int partition(int* data, int start, int end){
    int index = start;
    int pivot = data[index];
    swap(data[index], data[end]);
    for(int i = start; i < end; ++i){
        if(pivot >= data[i]) swap(data[index++], data[i]);
    } 
    swap(data[end], data[index]);
    return index;
}
void quick_sort(int* data, int start, int end){
    if(start >= end) return;
    int index = partition(data, start, end);
    quick_sort(data, start, index);
    quick_sort(data, index + 1, end);
}

int main(int argc, const char* argv[]){
    int length = argc - 1;
    int* data = new int[length];
    for(int i = 0; i < length; ++i) data[i] = atoi(argv[i + 1]);

    quick_sort(data, 0, length - 1);
    
    for(int i = 0; i < length; ++i) printf("%d ", data[i]);
    printf("\n");
    return 0;
}
