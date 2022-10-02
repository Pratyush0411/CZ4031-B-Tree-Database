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

int main()
{
    cout << "Experiment 5: delete those movies with the attribute numVotes equal to 1,000" << endl;
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
    cout << "(Data loaded)" << endl;
    btree->display();
    cout<< "\n\nRemoving key 1000"<<endl;
    int foo = btree->remove(1000);
    btree->display();
    cout<< "Nodes deleted: "<<foo<<endl;

}
