#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

std::unordered_map<int, std::string> kvMap;

// TODO: Implement populating kvMap from database.txt
void populateMap() {

}

// TODO: Implement saving kvMap to database.txt
void saveToDatabase() {

}

std::string validateOperation(const std::string& cmd) {
    if (cmd == "") { return "iv"; }
    else if (cmd == "quit") { return cmd; }

    char op = cmd[0];

    if (op == 'p' || op == 'g' || op == 'd' || op == 'c' || op == 'a') {
        return cmd;  // Valid operation
    }
    
    return "iv";  // Invalid operation
}

std::vector<std::string> split(std::string str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, ',')) {
        result.push_back(token);
    }

    return result;
}

std::string getInput() {
    std::string line;
    printf("Please enter a command or 'quit' to exit program (type 'list' to see all valid commands):\n");
    std::getline(std::cin, line);

    if (line == "list") {
        printf("put: The format is 'p,key,value' where key is an integer, and value an arbitrary string (without commas in it).\n");
        printf("get: The format is 'g,key where' key is an integer. If the key is present, the system should print out the key, followed by a comma, followed by the value, followed by a newline (\n). If not present, print an error message on a line by itself, of the form K not found where K is the actual value of the key, i.e., some integer.\n");
        printf("delete: The format is 'd,key' which either deletes the relevant key-value pair (and prints nothing), or fails to do so (and prints K not found where K is the actual value of the key, i.e., some integer).\n");
        printf("clear: The format is 'c'. This command simply removes all key-value pairs from the database.\n");
        printf("all: The format is 'a'. This command prints out all key-value pairs in the database, in any order, with one key-value pair per line, each key and value separated by a comma.\n");
        printf("quit: Thr format is 'quit'. Exits the program and saves information to a persistent text-based database.\n");
        
        return "list";
    }

    return validateOperation(line);

}

void put(std::string command) {
    std::vector<std::string> tokened = split(command);
    // TODO: Validate command

    int key = std::stoi(tokened[1]);   
    std::string val = tokened[2];
    kvMap[key] = val;
}

void get(std::string command) {
    std::vector<std::string> tokened = split(command);
    // TODO: Validate command, validate key

    int key = std::stoi(tokened[1]);
    std::string val = kvMap[key];

    std::string message = std::to_string(key) + "," + val;
    std::cout << message << std:: endl;
}

void del(std::string command) {
    std::vector<std::string> tokened = split(command);
    // TODO: Validate command

    int key = std::stoi(tokened[1]);

    if (kvMap.find(key) != kvMap.end()) {
        kvMap.erase(key);
        std::cout << key << " deleted" << std::endl;
    } else {
        std::cout << key << " not found" << std::endl;
    }
}

void all() {
    for (const auto& pair : kvMap) {
        std::cout << pair.first << "," << pair.second << std::endl;
    }
}

int main() {
    populateMap();

    int run = 1;
    while (run == 1) {
        std::string command = getInput();
        if (command == "list") { continue; }
        else if (command == "iv") {
            printf("bad command\n");
            continue;
        }
        else if (command == "quit") {
            saveToDatabase();

            run = 0;
            break;
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
                kvMap.clear();
                break;
            case 'a':
                all();
                break;
        }       
    }
    
    return 0;
}