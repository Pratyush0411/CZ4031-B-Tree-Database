//
// Created by praty on 11/9/2022.
//

#include "database.h"



void Database:: addNewBlock(Block blk){
    this->blocksList.push_back(blk);
}