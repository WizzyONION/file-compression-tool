#include <iostream>
#include <fstream>
#include <array>

using namespace std;

int main() {

    ifstream file("simple.txt", ios::binary);

    if (!file) {
        cout << "Error opening file" << endl;
        return 1;
    }

    array<int, 256> frequency{};

    char byte;
    int count = 0;

    // Read file byte by byte
    while (file.get(byte)) {

        // Convert byte to unsigned value
        unsigned char value = static_cast<unsigned char>(byte);

        // Display byte value
        cout << "Byte Value: " << static_cast<int>(value) << endl;

        // Increment frequency
        frequency[value]++;

        // Count total bytes
        count++;
    }

    cout << "\nByte Frequency Analysis\n";
    cout << "--------------------------\n";

    for (int i = 0; i < 256; i++) {

        if (frequency[i] > 0) {

            cout << "Byte: " << i
                 << " | Frequency: " << frequency[i];

            if (i >= 32 && i <= 126) {
                cout << " | Character: " << static_cast<char>(i);
            }

            cout << '\n';
        }
    }

    cout << "\nTotal Bytes: " << count << '\n';

    file.close();

    return 0;
}