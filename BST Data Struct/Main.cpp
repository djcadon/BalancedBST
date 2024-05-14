#include "BST.h"
#include "File.h"

int main() {
    //Global Variables
    int choice = 0;
    Tree<Words> BinaryTree{};
    MakeTree(BinaryTree, "MobyDick.txt");
    // BinaryTree.print(BinaryTree.root);
     //Main Loop
    while (choice != 7) {
        std::cout << "----------------------\n";
        std::cout << "1. Find a word\n";
        std::cout << "2. Size\n";
        std::cout << "3. Get all words in ascending order\n";
        std::cout << "4. Get all words in descending order\n";
        std::cout << "5. Empty tree\n";
        std::cout << "6. Remove a word\n";
        std::cout << "7. Exit\n";
        std::cout << "----------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        //In case of invalid input
        std::cin.ignore();
        std::cin.clear();
        switch (choice) {
            //Find option
        case 1: {
            std::string word;
            std::cout << "Enter a word to find: ";
            std::cin >> word;
            //In case of invalid input
            std::cin.ignore();
            std::cin.clear();
            Words Tempword{ word };
            if (BinaryTree.Find(Tempword, BinaryTree.root) == nullptr) {
                std::cout << "Word not found\n";
                break;
            }
            else {
                std::cout << "Word found\n";
                break;
            }
        }
              //Size option
        case 2: {
            std::cout << "Size of the tree is: ";
            std::cout << BinaryTree.Size(BinaryTree.root) << "\n";
            break;
        }
              // Ascending order option
        case 3: {
            Node<Words>** arr = new Node<Words>*[BinaryTree.Size(BinaryTree.root)];
            int index = 0;
            BinaryTree.Depth(BinaryTree.root, nullptr);
            BinaryTree.GetAllAscending(BinaryTree.root, arr, index);
            for (int i = 0; i < index; i++) {
                std::cout << arr[i]->data.word << " |Count: " << arr[i]->data.count << "|";
                std::cout << "|Balance Factor: " << arr[i]->BalanceFactor << "|\n";
            }
            delete[] arr;
            break;
        }
              // Descending order option
        case 4: {
            Node<Words>** arr = new Node<Words>*[BinaryTree.Size(BinaryTree.root)];
            int index = 0;
            BinaryTree.Depth(BinaryTree.root, nullptr);
            BinaryTree.GetAllDescending(BinaryTree.root, arr, index);
            for (int i = 0; i < index; i++) {
                std::cout << arr[i]->data.word << " |Count: " << arr[i]->data.count << "|";
                std::cout << "|Balance Factor: " << arr[i]->BalanceFactor << "|\n";
            }
            delete[] arr;
            break;
        }
              //Empty tree option
        case 5: {
            if (BinaryTree.root != nullptr) {
                BinaryTree.EmptyTree(BinaryTree.root);
                std::cout << "Tree is emptied\n";
            }
            break;
        }
              //Remove a word option
        case 6: {
            if (BinaryTree.root == nullptr) {
                std::cout << "Tree is empty\n";
                break;
            }
            std::string word;
            std::cout << "Enter a word to remove: ";
            std::cin >> word;
            Words Tempword{ word };
            if (BinaryTree.Remove(Tempword, BinaryTree.root) == nullptr) {
                std::cout << "Word not found\n";
            }
            else {
                std::cout << "Word was removed\n";
            }
            break;
        }
              //Exit option
        case 7: {
            std::cout << "    __________\n";
            std::cout << "   /          \\\n";
            std::cout << "  /            \\\n";
            std::cout << " |              |\n";
            std::cout << " |,  .-.  .-.  ,|\n";
            std::cout << " | )(__/  \\__)( |\n";
            std::cout << " |/     /\\     \\|\n";
            std::cout << " (_     ^^     _)\n";
            std::cout << "  \\__|IIIIII|__/\n";
            std::cout << "  |  \\IIIIII/  |\n";
            std::cout << "   \\          /\n";
            std::cout << "    `--------`\n";
            return 0;
        }
        }
    }
}