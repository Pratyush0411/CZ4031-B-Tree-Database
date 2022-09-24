//
// Created by praty on 23/9/2022.
//
#include "../entities/BTree.cpp"

void testDetermineN(){
    DuplicateNode *dn = new DuplicateNode();
    dn->print();
}
void testInsert(){
    DuplicateNode *dn = new DuplicateNode();
    for (int i = 0; i<100;i++){
        Record* dummy = new Record("",0.5,1);

        dn->pushRecord(dummy);
    }

    DuplicateNode* cursor = dn;
    while(cursor!=NULL){
        cursor->print();
        cursor= cursor->getNextNode();
    }
}


int main(){
    //testDetermineN();
    testInsert();



}