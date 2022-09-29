//
// Created by praty on 12/9/2022.
//
#include "../entities/datablock.h"
#include "../entities/datablock.cpp"
#include "../entities/storage.cpp"
#include "../entities/database.h"
#include "../entities/database.cpp"
#include <cstring>

int main(){

    //DataBlock* blk1 = new DataBlock(200);
    //blk1->insertRecord(*rec1);
    //blk1->insertRecord(*rec2);
    //blk1->printBlock();
    ////blk1->deleteRecord(*rec1);
    //blk1->printBlock();
    Record* rec1 = new Record("t00000000",9.5,23);
    //Record* rec2 = new Record("t00000001",9.0,20);
    int DbSize = 1000;
    int blockSize = 100;
    Database* db = new Database(DbSize, blockSize);
    pair<DataBlock*, Record*> p1 = db->addRecord(*rec1);
    if(p1.second != NULL)
        cout << p1.second->tconst<<" "<<p1.second->avgRating<<" "<<p1.second->numVotes<<endl;
}