#include "Compression.h"

/**
 * Constructor
 */
Compression::Compression(std::string path) : dangling(0), list_of_words(0) {
    this->readData(path);
}

/**
 * Read data from input file to memory
 */
void Compression::readData(std::string path) {
    std::ifstream file;
    file.open(path, file.in);
    char *line;
    if (file.is_open()) {
        while (!file.eof()) {
            file.getline(line, 256);
            list_of_words.emplace_back(extractValue(line));
        }
    }
    file.close();
}

/**
 * Manage the UD check algorithm
 */
bool Compression::UD_check() {
    int *steps;
    for (int i = 0; i < sizeof(list_of_words) / sizeof(int); i++) {
        for (int j = 0; j < sizeof(list_of_words) / sizeof(int); j++) {
            if (i != j) {
                if (startsWith(list_of_words[i], list_of_words[j], steps)) {
                    int temp = list_of_words[j] << *(steps);
                    dangling.push_back((list_of_words[i] ^ temp));
                }
            }
        }
    }
    return isDanglingInCode();
}

/**
 * Looks for all danglings in the list of words, in order to confirm UD
 */
bool Compression::isDanglingInCode() {
    for (int current : dangling) {
        if (contains(current)) {
            return false;
        }
    }
    return true;
}

/**
 * Looks for one dangling in the list of words
 */
bool Compression::contains(int word) {
    for (int i : list_of_words) {
        if (word == i) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if word2 is prefix of word1, if yes assign the number of bit shifting to steps variable
 */
bool Compression::startsWith(int word1, int word2, int *steps) {
    int temp = word1;
    int counter = 0;
    while (temp > 0) {
        if ((temp ^ word2) == 0) {
            *steps = counter;
            return true;
        }
        temp = (temp >> 1);
        counter++;
    }
    return false;
}

int Compression::extractValue(char *line) {
    int bits = (line[1] - 48);
    int index = 4;
    int value = 0;
    int current = line[index] - 48;
    while (bits > 0) {

    }
    return value;
}