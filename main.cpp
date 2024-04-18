#include <iostream>
#include <fstream>
#include <ctime>
#include "AVL.hpp" // Include your AVL tree implementation header file
#include "SkipList.cpp" // Include your Skip list implementation header file

using namespace std;

// Function to read data from the dataset file
void readDataset(const string& filename, vector<int>& data) {
    ifstream file(filename);
    int num;
    while (file >> num) {
        data.push_back(num);
    }
}

int main() {
    // Load dataset
    vector<int> dataset;
    readDataset("dataset.txt", dataset); // Replace "dataset.txt" with your dataset file name

    // AVL Tree
    AVL avl;

    clock_t start_time_avl = clock(); // Start timer for AVL Tree insertion
    for (int num : dataset) {
        avl.insert(num);
    }
    clock_t end_time_avl = clock(); // End timer for AVL Tree insertion

    double time_taken_avl = double(end_time_avl - start_time_avl) / CLOCKS_PER_SEC;
    cout << "Time taken by AVL Tree: " << time_taken_avl << " seconds" << endl;

    // Skip List
    SkipList skiplist;

    clock_t start_time_skiplist = clock(); // Start timer for Skip List insertion
    for (int num : dataset) {
        skiplist.insert(num);
    }
    clock_t end_time_skiplist = clock(); // End timer for Skip List insertion

    double time_taken_skiplist = double(end_time_skiplist - start_time_skiplist) / CLOCKS_PER_SEC;
    cout << "Time taken by Skip List: " << time_taken_skiplist << " seconds" << endl;

    return 0;
}
