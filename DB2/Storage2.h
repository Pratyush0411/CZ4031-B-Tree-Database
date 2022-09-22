#include <iostream>
#include <vector>
#pragma once
using namespace std;
typedef unsigned int uint;

class Record
{
public:
    bool used;
    string tconst;
    float avgRating;
    uint numVotes;
    Record();
};

class Block
{
public:
    static int BlkSize;
    Block *BlkPtr;
    Block(int BlkSize);
};

class Database
{
public:
    static int MAXSIZE;
    vector<Block *> BlockList;
    Database(int MemSize, int BlkSize);
};