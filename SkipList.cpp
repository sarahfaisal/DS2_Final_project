#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

template <typename T>
class SkipList {
private:
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
        while (dist(gen) < 0.5 && levels < head.size())
            levels++;

        return levels;
    }

public:
    SkipList() {
        // Initialize the head with one level
        head.push_back(new SkipNode(T{}, 1));
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

   // Search for a value in the skip list
    bool search(T val) {
        SkipNode* curr = head[head.size() - 1];
        for (int i = head.size() - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->value < val)
                curr = curr->next[i];
        }
        curr = curr->next[0]; // Move to the next level
        return curr && curr->value == val;
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

int main() {
    const int arraySize = 10000; // Size of the array
    std::vector<int> unorderedArray(arraySize);

    // Fill the array with numbers from 0 to 999999
    for (int i = 0; i < arraySize; ++i) {
        unorderedArray[i] = i;
    }

    // Shuffle the array to make it unordered
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(unorderedArray.begin(), unorderedArray.end(), g);

    // Print some numbers from the array as a sample
   // std::cout << "Unordered array sample: ";
    for (int i = 0; i < arraySize; ++i) {
    }
    SkipList<int> skipList;
    for (int i = 0; i < arraySize; ++i) {
        skipList.insert(unorderedArray[i]);
        //std::cout << unorderedArray[i] << " ";
    }
    std::cout << "Search 500: " << (skipList.search(500) ? "Found" : "Not found") << std::endl;
    skipList.remove(500);
    std::cout << "Search 500: " << (skipList.search(500) ? "Found" : "Not found") << std::endl;

    return 0;
}

