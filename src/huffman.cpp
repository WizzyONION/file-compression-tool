
#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <string>

using namespace std;

// Node of the Huffman Tree
struct Node {
    unsigned char data;
    int frequency;

    Node* left;
    Node* right;

    Node(unsigned char d, int f) {
        data = d;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    Node(int f, Node* l, Node* r) {
        data = 0;
        frequency = f;
        left = l;
        right = r;
    }

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

// Comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

// Build the Huffman Tree
Node* buildHuffmanTree(const array<int, 256>& frequency) {

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes for bytes that exist
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            pq.push(new Node(static_cast<unsigned char>(i), frequency[i]));
        }
    }

    // Handle empty file
    if (pq.empty()) {
        return nullptr;
    }

    // Combine nodes until only one tree remains
    while (pq.size() > 1) {

        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            left->frequency + right->frequency,
            left,
            right
        );

        pq.push(parent);
    }

    return pq.top();
}

// Generate Huffman codes
void generateCodes(Node* root, string code) {

    if (root == nullptr) {
        return;
    }

    // Leaf node represents an actual byte
    if (root->isLeaf()) {

        cout << "Byte: " << static_cast<int>(root->data)
             << " | Frequency: " << root->frequency
             << " | Code: " << code << '\n';

        return;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

// Free dynamically allocated tree memory
void deleteTree(Node* root) {

    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main() {

    ifstream file("simple.txt", ios::binary);

    if (!file) {
        cout << "Error opening file!\n";
        return 1;
    }

    array<int, 256> frequency{};
    char byte;

    // Count byte frequencies
    while (file.get(byte)) {
        unsigned char value = static_cast<unsigned char>(byte);
        frequency[value]++;
    }

    file.close();

    cout << "Byte Frequency Analysis\n";
    cout << "----------------------\n";

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            cout << "Byte: " << i
                 << " | Frequency: " << frequency[i] << '\n';
        }
    }

    // Build Huffman Tree
    Node* root = buildHuffmanTree(frequency);

    if (root == nullptr) {
        cout << "\nFile is empty.\n";
        return 0;
    }

    cout << "\nHuffman Codes\n";
    cout << "-------------\n";

    // Special handling for a file containing only one unique byte
    if (root->isLeaf()) {
        cout << "Byte: " << static_cast<int>(root->data)
             << " | Frequency: " << root->frequency
             << " | Code: 0\n";
    } else {
        generateCodes(root, "");
    }

    // Free tree memory
    deleteTree(root);

    return 0;
}
