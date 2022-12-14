//
// Created by praty on 12/9/2022.
//
#include "../entities/datablock.h"
#include "../entities/datablock.cpp"
#include "../entities/storage.cpp"
#include "../entities/database.h"
#include "../entities/database.cpp"
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

template <typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main()
{
    int DbSize1 = 500000000;
    int blockSize1 = 200;
    Database *db1 = new Database(DbSize1, blockSize1);
    ifstream file;
    int lineNum = 21;
    file.open("../Data/data.tsv");
    int curline = 0;
    string line;
    string substr;
    while (!file.eof())
    {
        curline++;
        getline(file, line);
        if (curline == 1) // Exclude header line
        {
            continue; 
        }
        vector<string> fields = split(line, '\t');
        //cout << fields[0] << " " << fields[1] << " " << fields[2] << endl;
        Record *trec = new Record(fields[0], stof(fields[1]), stoi(fields[2]));
        pair<DataBlock *, int> p1 = db1->addRecord(*trec);
        if (curline == lineNum)
            break;
    }
    cout << "number of blocks in db: " << db1->getNumBlocks() << endl;
    DataBlock* dbptr = db1->getFirstBlock();
    dbptr->printBlock();
    if(db1->deleteRecordfromBtree(dbptr,2)){
        cout <<"Record deleted" << endl;
        dbptr->printBlock();
    };

    cout << "Size of queue: " << sizeof(queue<int>) << endl;
    cout << "Size of database: " << sizeof(db1) <<endl;
    cout << "Size of recordlist: " << sizeof(dbptr->recordList) << endl; 

    // DataBlock* blk1 = new DataBlock(200);
    // blk1->insertRecord(*rec1);
    // blk1->insertRecord(*rec2);
    // blk1->printBlock();
    ////blk1->deleteRecord(*rec1);
    // blk1->printBlock();
    // Record *rec1 = new Record("t00000000", 9.5, 23);
    // Record* rec2 = new Record("t00000001",9.0,20);
    // int DbSize = 1000;
    // int blockSize = 100;
    // Database *db = new Database(DbSize, blockSize);
    // pair<DataBlock *, int> p1 = db->addRecord(*rec1);
    // if (p1.first != NULL)
    // {
    //     cout << p1.first->recordList[p1.second].tconst << endl;
    //     cout << p1.first->recordList[p1.second].avgRating << endl;
    //     cout << p1.first->recordList[p1.second].numVotes << endl;
    // }

}