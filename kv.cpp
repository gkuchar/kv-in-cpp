#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map<int, std::string> kvMap;

// TODO: Implement populating kvMap from database.txt
void populateMap() {

}

// TODO: Implement saving kvMap to database.txt
void saveToDatabase() {

}

std::string validateOperation(const std::string& cmd) {
    if (cmd == "") { return "iv";}
    else if (cmd == "quit") { return cmd; }

    char op = cmd[0];

    if (op != 'p' || op != 'g' || op != 'd' || op != 'c' || op != 'a') { return "iv"; }

    return cmd;
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

            run == 0;
            break;
        }

        char operation = command[0];

        // TODO: Switch statement on operation
    }
    
    return 0;
}