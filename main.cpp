#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

const std::string CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
const size_t LINE_LENGTH = 195;
const size_t LINES_PER_PAGE = 200;
const size_t PAGES_TO_GENERATE = 3800;

std::string generate_line(size_t length, std::mt19937& gen, std::uniform_int_distribution<>& dis) {
    std::string line;
    for (size_t i = 0; i < length; ++i) {
        line += CHARSET[dis(gen)];
    }
    return line;
}

int main() {
    std::ofstream file("babylonian_library.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, CHARSET.size() - 1);

    for (size_t page = 0; page < PAGES_TO_GENERATE; ++page) {
        for (size_t line = 0; line < LINES_PER_PAGE; ++line) {
            std::string line_text = generate_line(LINE_LENGTH, gen, dis);
            file << line_text << std::endl;
        }
        file << "\n--- Page " << page + 1 << " ---\n" << std::endl;
    }

    file.close();
    return 0;
}