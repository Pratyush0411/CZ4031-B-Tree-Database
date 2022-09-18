//
// Created by praty on 11/9/2022.
//

#pragma once
#include "storage.h"
#include "vector"

using namespace std;

class Database{
private:
    vector<Block> freeBlocks;
    vector<Block> blocksList;

public:

    static int MAXSIZE;
    void addNewBlock(Block blk);

};