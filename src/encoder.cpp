#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <string>
#include <vector>
#include <memory>    // For std::shared_ptr
#include <iterator>  // For istreambuf_iterator

using namespace std;


// Huffman Tree Node

struct Node {
    unsigned char data;
    int frequency;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    // Leaf constructor
    Node(unsigned char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}

    // Internal node constructor
    Node(int f, shared_ptr<Node> l, shared_ptr<Node> r) 
        : data(0), frequency(f), left(l), right(r) {}

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};


// Min-Heap Comparator

struct Compare {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
        return a->frequency > b->frequency;
    }
};


// Build Huffman Tree

shared_ptr<Node> buildHuffmanTree(const array<int, 256>& frequency) {
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;

    // Create leaf nodes
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            pq.push(make_shared<Node>(static_cast<unsigned char>(i), frequency[i]));
        }
    }

    if (pq.empty()) return nullptr; // Empty file

    // Combine the two minimum-frequency nodes
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        auto parent = make_shared<Node>(left->frequency + right->frequency, left, right);
        pq.push(parent);
    }

    return pq.top();
}


// Generate Huffman Codes

void generateCodes(const shared_ptr<Node>& root, string currentCode, array<string, 256>& codes) {
    if (!root) return;

    if (root->isLeaf()) {
        if (currentCode.empty()) currentCode = "0"; // Handle single-character files
        codes[root->data] = currentCode;
        return;
    }

    generateCodes(root->left, currentCode + "0", codes);
    generateCodes(root->right, currentCode + "1", codes);
}

// ------------------------------
// Print Huffman Code Table
// ------------------------------
void printCodeTable(const array<int, 256>& frequency, const array<string, 256>& codes) {
    cout << "\nHuffman Code Table\n";
    cout << "------------------\n";

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            // Note: Printing 'i' as an integer, but could be formatted as a character if printable
            cout << "Byte: " << i
                 << " | Frequency: " << frequency[i]
                 << " | Code: " << codes[i] << '\n';
        }
    }
}


// Encode Data from Memory

string encodeData(const string& fileData, const array<string, 256>& codes) {
    string encodedData;
    
    // OPTIMIZATION: Pre-allocate memory to prevent string reallocations
    // Max potential size is 256 bits per byte (very rare), but typically 8-12 bits.
    encodedData.reserve(fileData.size() * 8); 

    for (char byte : fileData) {
        unsigned char value = static_cast<unsigned char>(byte);
        encodedData += codes[value];
    }

    return encodedData;
}


// Main Function

int main() {
    string filename = "simple.txt";

    // OPTIMIZATION: Read the entire file into a string buffer at once
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening file!\n";
        return 1;
    }

    string fileData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    if (fileData.empty()) {
        cout << "File is empty.\n";
        return 0;
    }

    // Frequency table
    array<int, 256> frequency{};
    for (char byte : fileData) {
        unsigned char value = static_cast<unsigned char>(byte);
        frequency[value]++;
    }

    int totalBytes = static_cast<int>(fileData.size());

    cout << "Original File Analysis\n";
    cout << "---------------------\n";
    cout << "Total bytes: " << totalBytes << '\n';

    // Build Huffman Tree
    shared_ptr<Node> root = buildHuffmanTree(frequency);
    
    // Code lookup table
    array<string, 256> codes{};
    generateCodes(root, "", codes);

    printCodeTable(frequency, codes);

    // Encode input
    string encodedData = encodeData(fileData, codes);

    // Display encoded result (Preview only to prevent console freezing)
    cout << "\nEncoded Data (First 100 bits)\n";
    cout << "------------\n";
    cout << encodedData.substr(0, min((size_t)100, encodedData.size())) << "...\n";

    // Calculate encoded size
    size_t encodedBits = encodedData.size();

    cout << "\nCompression Analysis\n";
    cout << "-------------------\n";
    cout << "Original size: " << (long long)totalBytes * 8 << " bits\n";
    cout << "Encoded size:  " << encodedBits << " bits\n";

    if (totalBytes > 0 && encodedBits > 0) {
        double compressionRatio = static_cast<double>(totalBytes * 8) / encodedBits;
        double savings = 100.0 * (1.0 - static_cast<double>(encodedBits) / (totalBytes * 8));

        cout << "Compression ratio: " << compressionRatio << ":1\n";
        cout << "Space saved: " << savings << "%\n";
    }

    // Note: No need to call deleteTree() because std::shared_ptr automatically 
    // cleans up the memory when 'root' goes out of scope at the end of main.

    return 0;
}