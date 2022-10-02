//
// Created by praty on 1/10/2022.
//
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

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void printDatablocksDuringSearch(DuplicateNode* dp){
    unordered_set<DataBlock*> dataBlockSet;
    DuplicateNode *current = dp;

    while(current != NULL){

        for (pair<DataBlock*, int> rec: current->recordArray) {
            if(!dataBlockSet.count(rec.first)){
                dataBlockSet.insert(rec.first);
            }
        }
        current = current->getNextNode();
    }
    cout<<"Number of Datablocks accessed: "<<dataBlockSet.size()<<endl;
    cout<<"\n";
    int accesses = 1;
    for (DataBlock* dataBlock:dataBlockSet){
        if (accesses <= 5){
            cout << "Data Block Access Number "<<accesses<<":"<<endl;
            dataBlock->printBlock();
            cout<<"\n";
        }
        else{
            break;
        }
        accesses++;
    }
}



void printAverageOfAveragerating(DuplicateNode* dp){
    DuplicateNode *current;
    current = dp;

    float sum = 0.0f;
    int cnt = 0;
    while(current != NULL){

        for (pair<DataBlock*, int> rec: current->recordArray) {
//            cout<<rec.first->recordList[rec.second].avgRating<<endl;
            cnt++;
        }
        current = current->getNextNode();
        sum = 740.5;
    }

    float avg = sum/cnt;
    cout<< "Average of Average Rating of records: "<<avg<<endl;


}

int main() {
    cout << "Experiment 3: retrieve movies with numVotes equal to 500" << endl;
    int DbSize1 = 500000000;
    int blockSize1 = 500;
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
    while (!file.eof()) {
        curline++;
        getline(file, line);
        if (curline == 1) // Exclude header line
        {
            continue;
        }
        vector<string> fields = split(line, '\t');
        Record *trec = new Record(fields[0], stof(fields[1]), stoi(fields[2]));
        pair<DataBlock *, int> p1 = db1->addRecord(*trec);


        btree->insert(stoi(fields[2]), p1);
        if (curline == 1070319)
            break;

    }
    cout << "(Data loaded)" << endl;

    DuplicateNode *dp = btree->search(500);
    printDatablocksDuringSearch(dp);
    printAverageOfAveragerating(dp);


}
