//
// Created by praty on 1/10/2022.
//

//#include "../entities/datablock.h"
//#include "../entities/datablock.cpp"
//#include "../entities/storage.cpp"
//#include "../entities/storage.h"
//#include "../entities/database.h"
//#include "../entities/database.cpp"
#include "../entities/BTree.cpp"
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


void printAverageOfAveragerating(DuplicateNode* dp){
    // DuplicateNode *current = dp;
    // int sum = 0;
    // int cnt = 0;
    // while(current != NULL){

    //     for (pair<DataBlock*, int> rec: current->recordArray) {
    //         // rec.first.get;
    //         cnt++;
    //     }
    //     current = current->getNextNode();
    // }
    float sum = 6411.7000000000035;
    // cout << "Average of averageRatings: " << sum/
}


int main()
{
    cout << "Experiment 4: Retrieve those movies with the attribute numVotes from 30,000 to 40,000 both inclusively" << endl;
    int DbSize1 = 500000000;
    int blockSize1 = 500;
    int lowerBound = 30000;
    int upperBound = 40000;
    cout << "Allocated database size: " << DbSize1 / 1000000 << "MB" << endl;
    cout << "Block size: " << blockSize1 << endl;
    Database *db1 = new Database(DbSize1, blockSize1);
    BPTree *btree = new BPTree();
    ifstream file;
    file.open("../Data/data.tsv");
    int curline = 0;
    string line;
    string substr;

    cout << "(Data loading)" << endl;
    while (!file.eof())
    {
        curline++;
        getline(file, line);
        if (curline == 1) // Exclude header line
        {
            continue;
        }
        vector<string> fields = split(line, '\t');
        Record *trec = new Record(fields[0], stof(fields[1]), stoi(fields[2]));
        pair<DataBlock *, int> p1 = db1->addRecord(*trec);
        if(curline%150 == 2){
            //cout << curline <<endl;
        }
        btree->insert(stoi(fields[2]), p1);
        if (curline == 1070319)
            break;
    }

     // ptr[size+1] is the ptr to the next leaf node
    // keep on iterating until the key[i] is more than the upper bound 
    cout << "(Data loaded)" << endl;
    btree->display();
    cout << btree->searchLowerBound(30000,40000) << endl;
    
}
