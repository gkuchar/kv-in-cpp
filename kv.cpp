#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

std::unordered_map<int, std::string> kvMap;

std::vector<std::string> split(std::string str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, ',')) {
        result.push_back(token);
    }

    return result;
}

void populateMap() {
    std::ifstream file("database.txt");
    
    if (!file) {
        std::ofstream outputFile("database.txt");
        outputFile.close();
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> tokened = split(line);
        
        if (tokened.size() != 2) continue;
        
        try {
            int key = std::stoi(tokened[0]);   
            std::string val = tokened[1];
            kvMap[key] = val;
        } catch (...) {
            continue;
        }
    }
    
    file.close();
}

void saveToDatabase() {
    std::ofstream file("database.txt");
    
    if (!file) {
        std::cerr << "Error: Could not open database.txt for writing" << std::endl;
        exit(1);
    }
    
    for (const auto& pair : kvMap) {
        file << pair.first << "," << pair.second << std::endl;
    }
    
    file.close();
}

void put(std::string command) {
    std::vector<std::string> tokened = split(command);
    
    if (tokened.size() < 3) {
        std::cout << "bad command" << std::endl;
        return;
    }

    // Validate that key is an integer
    try {
        int key = std::stoi(tokened[1]);   
        std::string val = tokened[2];
        kvMap[key] = val;
    } catch (const std::invalid_argument&) {
        std::cout << "bad command" << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "bad command" << std::endl;
    }
}

void get(std::string command) {
    std::vector<std::string> tokened = split(command);
    
    if (tokened.size() < 2) {
        std::cout << "bad command" << std::endl;
        return;
    }

    // Validate that key is an integer
    try {
        int key = std::stoi(tokened[1]);
        
        if (kvMap.find(key) != kvMap.end()) {
            std::string val = kvMap[key];
            std::cout << key << "," << val << std::endl;
        } else {
            std::cout << key << " not found" << std::endl;
        }
    } catch (const std::invalid_argument&) {
        std::cout << "bad command" << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "bad command" << std::endl;
    }
}

void del(std::string command) {
    std::vector<std::string> tokened = split(command);
    
    if (tokened.size() < 2) {
        std::cout << "bad command" << std::endl;
        return;
    }

    // Validate that key is an integer
    try {
        int key = std::stoi(tokened[1]);

        if (kvMap.find(key) != kvMap.end()) {
            kvMap.erase(key);
        } else {
            std::cout << key << " not found" << std::endl;
        }
    } catch (const std::invalid_argument&) {
        std::cout << "bad command" << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "bad command" << std::endl;
    }
}

void all() {
    for (const auto& pair : kvMap) {
        std::cout << pair.first << "," << pair.second << std::endl;
    }
}

void clear() {
    kvMap.clear();
}

void processCommand(const std::string& command) {
    if (command.empty()) {
        std::cout << "bad command" << std::endl;
        return;
    }

    char operation = command[0];

    switch (operation) {
        case 'p':
            put(command);
            break;
        case 'g':
            get(command);
            break;
        case 'd':
            del(command);
            break;
        case 'c':
            clear();
            break;
        case 'a':
            all();
            break;
        default:
            std::cout << "bad command" << std::endl;
            break;
    }
}

int main(int argc, char* argv[]) {
    populateMap();

    // Process each command-line argument
    for (int i = 1; i < argc; i++) {
        processCommand(argv[i]);
    }
    
    saveToDatabase();
    
    return 0;
}