#include <iostream>
#include <list>
#include <cstring>
#include <vector>
using namespace std;
typedef list<pair<int,string>> list_pair;
class HashTable{
    private:
        int hashGroups; //(default = 10) Bigger group number means faster searching, adding but allocating more memory
        vector<list_pair> table; //a bunch of list<pair<int,string>> structures
public:
    HashTable(int hashGroups);
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};
HashTable::HashTable(int hashGroups) {
    this->hashGroups = hashGroups;
    for(int i=0; i<hashGroups; i++) {
        list<pair<int,string>> ls;
        table.push_back(ls);
    }
}
bool HashTable::isEmpty() const {
    int sum;
    for(int i=0; i< hashGroups;i++){
        sum += table[i].size();
    }
    if(!sum){
        return true;
    }
    return false;
}
int HashTable::hashFunction(int key) {
    return key%hashGroups;
}
void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];//List at the given index
    auto bIter = begin(cell); //iterator of cell <pair>
    bool keyExists = false;
    for(; bIter != end(cell); bIter++ ){
        if(bIter->first == key){ //first: key
            keyExists = true;
            bIter->second = value; //second: value
            cout<<"Key exist. Value replaced." << "/n";
            break;
        }
    }
    if(!keyExists){
        cell.emplace_back(key,value);
    }
    return;
}
void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bIter = begin(cell);
    bool keyExists = false;
    for(; bIter != end(cell); bIter++ ){
        if(bIter->first == key){
            keyExists = true;
            cell.erase(bIter);//second: value
            cout<<"Key deleted" << "/n";
            break;
        }
    }
    if(!keyExists){
        cout<<"Key not found."<< "/n";
    }
    return;
}

void HashTable::printTable() {
    for(int i ; i<hashGroups; i++){
        if(table[i].size() == 0) continue;
        auto bIter = table[i].begin();
        for (; bIter != table[i].end(); bIter++) {
            cout<<"Key: "<<bIter->first<<" Value: "<<bIter->second<<"\n";
        }
    }
    return;
}