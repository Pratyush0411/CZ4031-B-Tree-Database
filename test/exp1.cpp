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
    cout << "Experiment 1: Store data on the disk and report the following statistics:" << endl;
    int DbSize1 = 500000000;
    int blockSize1 = 500;
    cout << "Allocated database size: " << DbSize1/1000000 <<"MB" << endl;
    cout << "Block size: " << blockSize1 << endl;
    Database *db1 = new Database(DbSize1, blockSize1);
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
        if(curline == 1070319) break;
    }
    cout << "(Data loaded)" << endl;
    DataBlock *dbptr = db1->getFirstBlock();
    cout << "Number of blocks in db: " << db1->getNumBlocks() << endl;

    cout << "Size of database: " << db1->getSize() << " bytes / 1000000 = "<< (db1->getSize())/1000000.0 << "MB" <<endl;
}
