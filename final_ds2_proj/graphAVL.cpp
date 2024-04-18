#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "AVLIndex.hpp" // Include your AVL implementation header file
#define WITHOUT_NUMPY
#include "matplotlibcpp.h" // Include the library for plotting
 
#include <iostream>
#include <algorithm>
#include <vector> // Include vector for handling the array
#include <string> 

 namespace plt = matplotlibcpp;

 // Function to generate a random dataset of given size
 template<typename Key, typename Data>
 std::vector<std::pair<Key, Data>> generateRandomDataset(int size) {
     std::vector<std::pair<Key, Data>> dataset;
     std::default_random_engine generator;
     std::uniform_int_distribution<Key> keyDistribution(1, size * 10); // Adjust the range as needed
     for (int i = 0; i < size; ++i) {
         Key key = keyDistribution(generator);
         Data data;
         dataset.emplace_back(key, data);
     }
     return dataset;
 }

 // Function to measure the time taken to insert elements into AVL tree
 template<typename Key, typename Data>
 std::chrono::milliseconds measureInsertionTime(const std::vector<std::pair<Key, Data>>& dataset) {
     AVLIndex<Key, Data> tree;
     auto start = std::chrono::steady_clock::now();
     for (const auto& pair : dataset) {
         tree.Add(pair.first, pair.second);
     }
     auto end = std::chrono::steady_clock::now();
     return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
 }
 int main() {
     // Define the type for Key and Index
     typedef std::string KeyType;
     typedef int IndexType;

     // Create an array of 100 integers from 1 to 100
     std::vector<KeyType> data(100);
     for (int i = 0; i < 100; ++i) {
         data[i] = std::to_string(i + 1);
     }

     // Create an instance of AVLIndex
     AVLIndex<KeyType, IndexType> avl1;

     // Insert each element of the array into the AVL tree
     for (IndexType i = 0; i < data.size(); ++i) {
         avl1.Add(data[i], i);
     }

     // Print the AVL tree
     avl1.PrintTree();

     // Graphing
     std::vector<int> datasetSizes = { 100, 500, 1000, 10000 }; // Adjust dataset sizes as needed
     std::vector<std::chrono::milliseconds> insertionTimes;

     for (int size : datasetSizes) {
         auto dataset = generateRandomDataset<int, int>(size); // Change Key and Data types as needed
         auto time = measureInsertionTime<int, int>(dataset); // Change Key and Data types as needed
         insertionTimes.push_back(time);
         std::cout << "Time taken to insert " << size << " elements: " << time.count() << " milliseconds\n";
     }

     // Convert time durations to milliseconds (double) for plotting
     std::vector<double> insertionTimesMillis;
     for (const auto& time : insertionTimes) {
         insertionTimesMillis.push_back(static_cast<double>(time.count()));
     }

     // Plotting
     plt::plot(datasetSizes, insertionTimesMillis);
     plt::title("Insertion Time Complexity of AVL Tree");
     plt::xlabel("Dataset Size");
     plt::ylabel("Time (milliseconds)");
     plt::show();

     return 0;
 }
#if 0
// Function to generate a random dataset of given size
template<typename Key, typename Data>
std::vector<std::pair<Key, Data>> generateRandomDataset(int size) {
    std::vector<std::pair<Key, Data>> dataset;
    std::default_random_engine generator;
    std::uniform_int_distribution<Key> keyDistribution(1, size * 10); // Adjust the range as needed
    // You may also want to adjust the distribution for Data type if needed
    for (int i = 0; i < size; ++i) {
        Key key = keyDistribution(generator);
        Data data; // You may need to modify this based on your AVLNode constructor
        dataset.emplace_back(key, data);
    }
    return dataset;
}

// Function to measure the time taken to insert elements into AVL tree
template<typename Key, typename Data>
std::chrono::milliseconds measureInsertionTime(const std::vector<std::pair<Key, Data>>& dataset) {
    AVLIndex<Key, Data> tree;
    auto start = std::chrono::steady_clock::now();
    for (const auto& pair : dataset) {
        tree.Add(pair.first, pair.second);
    }
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}
#if 1
int main() {
     // Define the type for Key and Index
    typedef std::string KeyType;
    typedef int IndexType;

    // Create an array of 100 integers from 1 to 100
     std::vector<KeyType> data(100);
     for (int i = 0; i < 100; ++i) {
         data[i] = i + 1;
     }

//     // Create an instance of AVLIndex
     AVLIndex<KeyType, IndexType> avl1;

     // Insert each element of the array into the AVL tree
     for (IndexType i = 0; i < data.size(); ++i) {
         avl1.Add( data[i], i);
     }
#if 0
     // Create an array of 100 integers from 1 to 1000
     std::vector<KeyType> data(500);
     for (int i = 0; i < 500; ++i) {
         data[i] = i + 1;
     }

     //     // Create an instance of AVLIndex
     AVLIndex<KeyType, IndexType> avl2;

     // Insert each element of the array into the AVL tree
     for (IndexType i = 0; i < data.size(); ++i) {
         avl2.Add(i, data[i]);
     }

     // Create an array of 1000 integers from 1 to 1000
     std::vector<KeyType> data(1000);
     for (int i = 0; i < 1000; ++i) {
         data[i] = i + 1;
     }

     //     // Create an instance of AVLIndex
     AVLIndex<KeyType, IndexType> avl3;

     // Insert each element of the array into the AVL tree
     for (IndexType i = 0; i < data.size(); ++i) {
         avl3.Add(i, data[i]);
     }
#endif


    // Print the AVL tree
    avl1.PrintTree();
# if 0
    std::string keyToSearch = "sarah";
    AVLIndex<std::string, int>::Node* resultNode = avl.searchKey(keyToSearch);
    if (resultNode) {
    std::cout << "Key found: " << resultNode->key << std::endl;
    } else {
        std::cout << "Key not found: " << keyToSearch << std::endl;
    }
    KeyType keyToAdd = "irfan";
    IndexType indexToAdd = 0;
    avl.Add(indexToAdd, keyToAdd);

    // Print the AVL tree to verify the addition
    std::cout << "AVL Tree after adding element " << keyToAdd << ":" << std::endl;
    avl.PrintTree();
#endif

    //graphing
    std::vector<int> datasetSizes = {100, 500, 1000}; // Adjust dataset sizes as needed
    std::vector<std::chrono::milliseconds> insertionTimes;

    for (int size : datasetSizes) {
        auto dataset = generateRandomDataset<int, int>(size); // Change Key and Data types as needed
        auto time = measureInsertionTime<int, int>(dataset); // Change Key and Data types as needed
        insertionTimes.push_back(time);
        std::cout << "Time taken to insert " << size << " elements: " << time.count() << " milliseconds\n";
    }

    // Convert time durations to milliseconds (double) for plotting
    std::vector<double> insertionTimesMillis;
    for (const auto& time : insertionTimes) {
        insertionTimesMillis.push_back(static_cast<double>(time.count()));
    }

    // Plotting
     plt::plot(datasetSizes, insertionTimesMillis);
     plt::title("Insertion Time Complexity of AVL Tree");
     plt::xlabel("Dataset Size");
     plt::ylabel("Time (milliseconds)");
     plt::show();
   
    //int bar_data[10] = {1,2,3,4,5,6,7,8,9,10};
    // int   bar_data[11] = ...;
    // float x_data[1000] = ...;
    // float y_data[1000] = ...;

     

    return 0;
}
#endif
#endif
