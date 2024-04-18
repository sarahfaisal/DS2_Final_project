// // #include "avl.hpp"
// // #include <iostream>
// // #include <algorithm>
// // #include <vector> // Include vector for handling the array

// // int main() {
// //     // Define the type for Key and Index
// //     typedef int KeyType;
// //     typedef int IndexType;

// //     // Create an array of 1000 integers from 1 to 1000
// //     std::vector<KeyType> data(10);
// //     for (int i = 0; i < 10; ++i) {
// //         data[i] = i + 1;
// //     }

// //     // Create an instance of AVLIndex
// //     AVLIndex<KeyType, IndexType> avl;

// //     // Insert each element of the array into the AVL tree
// //     for (IndexType i = 0; i < data.size(); ++i) {
// //         avl.Add(i, data[i]);
// //     }

// //     // Print the AVL tree
// //     avl.PrintTree();

// //     return 0;
// // }

#if 0
 #include "AVLIndex.hpp"
 #include <iostream>
 #include <algorithm>
 #include <vector> // Include vector for handling the array
 #include <string> // Include string for handling strings

 int main() {
     // Define the type for Key and Index
     typedef std::string KeyType;
     typedef int IndexType;

     // Create an array of random strings
     std::vector<KeyType> data = {"apple", "banana", "orange", "grape", "watermelon", "sarah", "sabahat"};

     // Create an instance of AVLIndex
     AVLIndex<KeyType, IndexType> avl;

     // Insert each element of the array into the AVL tree
     for (IndexType i = 0; i < data.size(); ++i) {
         avl.Add(i, data[i]);
     }

     // Print the AVL tree
     avl.PrintTree();
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
     return 0;
 }
#endif