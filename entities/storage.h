//
// Created by praty on 8/9/2022.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef unsigned int uint;


class Record{
    public:
    bool isDeleted;
    char tconst[10] = "";
    float avgRating;
    uint numVotes;
    bool operator == (Record rhs);

    Record(string tconst, float averageRating, uint numVotes);
    void print();

};

// super class (IndexBlock )
class Block{

public:
    static int MAXSIZE;
    int getBlkSize();

};



