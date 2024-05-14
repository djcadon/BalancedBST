#pragma once
#include"BST.h"
#include <sstream>
#include <string>
#include <algorithm>
class Words {
public:
    std::string word;
    int count{ 1 };
    // Overloading == operator
    bool operator==(const Words& other) const {
        return word == other.word;
    }
    // Overloading < operator
    bool operator<(const Words& other) const {
        return word < other.word;
    }
    // Overloading > operator
    bool operator>(const Words& other) const {
        return word > other.word;
    }
    // Allowing for std::cout
    friend std::ostream& operator<<(std::ostream& os, const Words& other) {
        os << other.word;
        return os;
    }
};
void MakeTree(Tree<Words>& BinaryTree, std::string FileName) {
    std::fstream file(FileName);
    // Can't open file
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << FileName << std::endl;
        return;
    }
    std::string line;
    // Reading through file
    while (std::getline(file, line)) {
        // Getting words from the line
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Lowercase the word
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Remove punctuation characters
            word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
            // Create a Words object for the word
            Words currentWord;
            currentWord.word = word;
            // Insert or update count in the tree
            Node<Words>* searchNode = BinaryTree.Find(currentWord, BinaryTree.root);
            //Adding word to tree if not found
            if (searchNode == nullptr) {
                BinaryTree.Insert(currentWord, BinaryTree.root);
            }
            else {
                searchNode->data.count++;
            }
        }
    }
}
