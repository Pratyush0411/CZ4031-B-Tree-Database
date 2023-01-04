# CZ4031-B-Tree-Database

## Description
As part of the CZ4031 (Database Systems Implementation) course, we were required to develop a simulation of B+ Trees, which are commonly used in modern database applications. Our system allowed users to search, insert, and delete entries in the database. To test the system's capabilities, we used the IMDB movies dataset and created five Python files for experimentation. Our project received special mention from the professor for its overall design and code quality 

## Installation and run guide:
- [ ] Download and extract zip file to intended location

- [ ] Use command prompt, and set your directory to the "test" folder within the extracted file.

- [ ] Each experiment is in a separate cpp file. To compile, run the following code:
-Experiment 1: "g++ -o test exp1.cpp"
-Experiment 2: "g++ -o test exp2.cpp"
-Experiment 3: "g++ -o test exp3.cpp"
-Experiment 4: "g++ -o test exp4.cpp"
-Experiment 5: "g++ -o test exp5.cpp"

- [ ] For each of the experiments, after compiling, run "test" in the code to run the executable file.

- [ ] When downloaded, each of the experiments are run with the block size set to 200. For part (7), to change the blocksize to 500, open the cpp files for each of the experiments and change the integer variable "blockSize1" from 200 to 500. 
Also, change MAXBLOCKSIZE in BTree.cpp to change the main memory block size to 500. Subsequently repeat steps 3 and 4 to compile and run the file
