#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
//#include <chrono>
template <typename T>
class SkipList {
private:
float probability;
    struct SkipNode {
        T value;
        std::vector<SkipNode*> next; // Pointers to next elements at different levels
        SkipNode(T val, int levels) : value(val), next(levels, nullptr) {}
    };

    std::vector<SkipNode*> head; // Pointers to the first elements of each level

    // Helper function to generate random levels for new nodes
    int randomLevel() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dist(0.0, 1.0);
        //It starts with a single level and increases the number of levels with a certain probability.
        //The probability determines the likelihood of a node having additional levels. In this implementation, the probability is set to 0.5, meaning there's a 50% chance of a node having an additional level.
        int levels = 1;
        while (dist(gen) < probability && levels < head.size())
            levels++;

        return levels;
    }

public:
    SkipList(float probability_in) {
        // Initialize the head with one level
        probability = probability_in;
        head.push_back(new SkipNode(T(), 1));
    }

   // Insert a value into the skip list
    void insert(T val) {
        int levels = randomLevel();
        SkipNode* newNode = new SkipNode(val, levels);

        // Find the insertion point at each level
        std::vector<SkipNode*> update(head.size(), nullptr);
        SkipNode* curr = head[head.size() - 1];
        for (int i = head.size() - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->value < val)
                curr = curr->next[i];
            update[i] = curr;
        }

        // Update pointers at each level
        for (int i = 0; i < levels; ++i) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    // void insert(T val) {
    // int levels = randomLevel();
    // SkipNode* newNode = new SkipNode(val, levels);

    // // Find the insertion point starting from the highest level
    // std::vector<SkipNode*> update(head.size(), nullptr);
    // SkipNode* curr = head[head.size() - 1];
    // for (int i = head.size() - 1; i >= 0; --i) {
    //     while (curr->next[i] && curr->next[i]->value < val)
    //         curr = curr->next[i];
    //     update[i] = curr;
    // }

    // // Update pointers from the highest level downwards
    // for (int i = levels - 1; i >= 0; --i) {
    //     newNode->next[i] = update[i]->next[i];
    //     update[i]->next[i] = newNode;
    // }
    // }

   // Search for a value in the skip list
    // bool search(T val) {
    //     SkipNode* curr = head[head.size() - 1];
    //     for (int i = head.size() - 1; i >= 0; --i) {
    //         while (curr->next[i] && curr->next[i]->value < val)
    //             curr = curr->next[i];
    //     }
    //     curr = curr->next[0]; // Move to the next level
    //     return curr && curr->value == val;
    // }
    // bool search(T val) {
    // SkipNode* curr = head[head.size() - 1];
    // for (int i = head.size() - 1; i >= 0; --i) {
    //     while (curr->next[i] && curr->next[i]->value < val)
    //         curr = curr->next[i];
    // }
    // curr = curr->next[0]; // Move to the next level

    // // Check if the value is found at the lowest level
    // if (curr && curr->value == val)
    //     return true;

    // return false;
    // }
//     bool search(T val) {
//     SkipNode* curr = head[head.size() - 1];
//     for (int i = head.size() - 1; i >= 0; --i) {
//         while (curr->next[i] && curr->next[i]->value < val)
//             curr = curr->next[i];
//         // If the current node's next node has the value, return true
//         if (curr->next[i] && curr->next[i]->value == val)
//             return true;
//     }
//     // The value wasn't found in the skip list
//     return false;
// }
// bool search(T val) {
//     SkipNode* curr = head[head.size() - 1];
//     for (int i = head.size() - 1; i >= 0; --i) {
//         while (curr->next[i] && curr->next[i]->value < val)
//             curr = curr->next[i];
//         // If the next node exists and its value matches the target, return true
//         if (curr->next[i] && curr->next[i]->value == val)
//             return true;
//         // If the next node doesn't exist or its value is greater than the target,
//         // move down one level
//         if (!curr->next[i] || curr->next[i]->value > val)
//             continue;
//     }
//     // The value wasn't found in the skip list
//     return false;
// }
bool search(T val) {
    SkipNode* current = head[head.size() - 1];

    // Start from the highest level of the skip list
    for (int i = head.size() - 1; i >= 0; i--) {
        // Move the current pointer forward while the key is greater than the key of the node next to current
        while (current->next[i] && current->next[i]->value < val)
            current = current->next[i];
    }

    // Move the current pointer to the right at level 0
    current = current->next[0];

    // If the current node has a value equal to the search value, we have found our target node
    if (current && current->value == val) {
       // std::cout << "Found value: " << val << std::endl;
        return true;
    }

    return false;
}


   // Delete a value from the skip list
    void remove(T val) {
        std::vector<SkipNode*> update(head.size(), nullptr);
        SkipNode* curr = head[head.size() - 1];
        for (int i = head.size() - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->value < val)
                curr = curr->next[i];
            update[i] = curr;
        }
        if (curr->next[0] && curr->next[0]->value == val) {
            SkipNode* toDelete = curr->next[0];
            for (int i = 0; i < head.size(); ++i) {
                if (update[i]->next[i] == toDelete) {
                    update[i]->next[i] = toDelete->next[i];
                }
            }
            delete toDelete;
        }
    }
    // void remove(T val) {
    // SkipNode* current = head[0];
    // SkipNode* prev = nullptr;
    
    // // Traverse the skip list from the bottom level
    // for (int i = 0; i <= head.size() - 1; i++) {
    //     while (current->next[i] && current->next[i]->value < val) {
    //         prev = current;
    //         current = current->next[i];
    //     }
    //     if (current->next[i] && current->next[i]->value == val) {
    //         // Found the node to be removed
    //         if (prev)
    //             prev->next[i] = current->next[i];
    //         else
    //             head[i] = current->next[i];
    //     }
    // }
    
    // // Delete logically removed nodes
    // delete current;
    // }


    ~SkipList() {
        for (SkipNode* node : head) {
            while (node) {
                SkipNode* temp = node;
                node = node->next[0];
                delete temp;
            }
        }
    }
};

// int main() {
//     const int arraySize = 10000; // Size of the array
//     std::vector<int> unorderedArray(arraySize);

//     // Fill the array with numbers from 0 to 999999
//     for (int i = 0; i < arraySize; ++i) {
//         unorderedArray[i] = i;
//     }

//     // Shuffle the array to make it unordered
//     std::random_device rd;
//     std::mt19937 g(rd());
//     std::shuffle(unorderedArray.begin(), unorderedArray.end(), g);

//     // Print some numbers from the array as a sample
//    // std::cout << "Unordered array sample: ";
//     auto start = std::chrono::high_resolution_clock::now();
//     for (int i = 0; i < arraySize; ++i) {
//     }
//     SkipList<int> skipList;
//     for (int i = 0; i < arraySize; ++i) {
//         skipList.insert(unorderedArray[i]);
//         //std::cout << unorderedArray[i] << " ";
//     }
//     auto load_array = std::chrono::high_resolution_clock::now();
//     std::cout << "Search 500: " << (skipList.search(500) ? "Found" : "Not found") << std::endl;
//     auto optimal_find = std::chrono::high_resolution_clock::now();
//     skipList.remove(500);
//     auto optimal_remove = std::chrono::high_resolution_clock::now();
//     std::cout << "Search 500: " << (skipList.search(500) ? "Found" : "Not found") << std::endl;
//     auto worst_find = std::chrono::high_resolution_clock::now();
//     // Calculate duration
//     auto time_to_load_micro = std::chrono::duration_cast<std::chrono::microseconds>(load_array - start);
//     auto time_to_find_bestcase_micro = std::chrono::duration_cast<std::chrono::microseconds>(optimal_find - load_array);
//     auto time_to_remove_micro = std::chrono::duration_cast<std::chrono::microseconds>(optimal_remove - optimal_find);
//     auto time_to_find_worstcase_micro = std::chrono::duration_cast<std::chrono::microseconds>(worst_find - optimal_remove);

//     // Print the duration
//     std::cout << "Time taken to load array: " << time_to_load_micro.count() << " microseconds" << std::endl;
//     std::cout << "Time taken to find(BestCase): " << time_to_find_bestcase_micro.count() << " microseconds" << std::endl;
//     std::cout << "Time taken to remove: " << time_to_remove_micro.count() << " microseconds" << std::endl;
//     std::cout << "Time taken to find(WorstCase): " << time_to_find_worstcase_micro.count() << " microseconds" << std::endl;

//     return 0;
// }