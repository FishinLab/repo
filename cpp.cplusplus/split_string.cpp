#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(string data, const char* pivot, vector<string>* res){
    int length = data.size();
    if(0 == length) return;
    int c = 0;
    while(c < length){
        if(data[c] == *pivot){
            res->push_back(data.substr(0, c));
            split(data.substr(c + 1, length), pivot, res);
        }
        c++;
    }
    res->push_back(data);
}

int main(int argc, const char* argv[]){
    string data(argv[1]);
    vector<string >* res = new vector<string >;
    split(data, argv[2], res);
    int sum = 0, c = 0;
    while(c < data.size()){
        if(data[c] == *(argv[2])) sum++;
        c++;
    }
    for(vector<string>::iterator iv = res->begin(); iv != res->begin() + sum + 1; ++iv){
        cout << *iv << " ";
    }
    cout << endl;
    return 0;
}
