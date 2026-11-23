#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>

int main() {
    std::ifstream file("simple.txt", std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::array<std::uint64_t, 256> frequency{};
    std::uint64_t total = 0;

    // Read in large blocks instead of byte by byte
    std::vector<char> buffer(1 << 16); // 64 KB

    while (file) {
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        std::streamsize n = file.gcount();

        for (std::streamsize i = 0; i < n; ++i) {
            ++frequency[static_cast<unsigned char>(buffer[i])];
        }
        total += static_cast<std::uint64_t>(n);
    }

    std::cout << "\nByte Frequency Analysis\n"
              << "--------------------------\n";

    for (int i = 0; i < 256; ++i) {
        if (frequency[i] == 0) continue;

        std::cout << "Byte: " << i
                  << " | Frequency: " << frequency[i];

        if (i >= 32 && i <= 126) {
            std::cout << " | Character: " << static_cast<char>(i);
        }
        std::cout << '\n';
    }

    std::cout << "\nTotal Bytes: " << total << '\n';

    return 0;
}