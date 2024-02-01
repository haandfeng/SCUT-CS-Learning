//
//  interpreter.cpp
//  OS
//
//  Created by 谭演锋 on 2023/12/22.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

const int HISTORY_SIZE = 10;
std::vector<std::string> history;
std::string path= "";
char updatedPath[256];
// Function to split a string into a vector of words
std::vector<std::string> splitString(const std::string &input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to execute internal commands
void executeInternalCommand(const std::string &command) {
    if (command == "cd") {
        // Change directory command

        if (chdir(path.c_str()) != 0) {
            perror("cd");
        }
        else{
            getcwd(updatedPath, sizeof(updatedPath));
        }
    } else if (command == "exit") {
        // Exit command
        exit(0);
    } else if (command == "history") {
        // Display command history
        std::cout << "Command History:" << std::endl;
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << i + 1 << ": " << history[i] << std::endl;
        }
    }
}

// Function to execute external commands
void executeExternalCommand(const std::vector<std::string> &args) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char **argv = new char *[args.size() + 1];
        for (size_t i = 0; i < args.size(); ++i) {
            argv[i] = const_cast<char *>(args[i].c_str());
        }
        argv[args.size()] = nullptr;

        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
        }
        delete[] argv;
        exit(0);
    } else if (pid > 0) {
        // Parent process
        wait(nullptr); // Wait for the child process to finish
    } else {
        perror("fork");
    }
}

int main() {

    while (true) {
        // Display prompt
        getcwd(updatedPath, sizeof(updatedPath));
        std::cout << "myShell>"<<updatedPath;

        // Read input
        std::string input;
        std::getline(std::cin, input);

        // Add command to history
        history.push_back(input);
        if (history.size() > HISTORY_SIZE) {
            history.erase(history.begin());
        }

        // Split input into command and arguments
        std::vector<std::string> tokens = splitString(input);
        if (tokens.empty()) {
            continue; // Empty input, prompt again
        }

        // Execute internal or external command
        if (tokens[0] == "cd" || tokens[0] == "exit" || tokens[0] == "history") {
            if(tokens[0] == "cd"){
                path = tokens[1];
            }
            executeInternalCommand(tokens[0]);
        } else {
            executeExternalCommand(tokens);
        }
    }

    return 0;
}
