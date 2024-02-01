//#include <iostream>
//#include <vector>
//#include <string>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <sys/types.h>
//
//const int HISTORY_SIZE = 10;
//
//void executeCommand(const std::vector<std::string>& args) {
//    pid_t pid = fork();
//
//    if (pid == -1) {
//        std::cerr << "Error creating child process\n";
//        exit(EXIT_FAILURE);
//    } else if (pid == 0) {
//        // Child process
//        char** argv = new char*[args.size() + 1];
//        for (size_t i = 0; i < args.size(); ++i) {
//            argv[i] = const_cast<char*>(args[i].c_str());
//        }
//        argv[args.size()] = nullptr;
//
//        execvp(args[0].c_str(), argv);
//
//        // If execvp fails
//        std::cerr << "Error executing command: " << args[0] << "\n";
//        exit(EXIT_FAILURE);
//    } else {
//        // Parent process
//        wait(nullptr);
//    }
//}
//
//int main() {
//    std::vector<std::string> history;
//    char cwd[1024];
//
//    while (true) {
//        getcwd(cwd, sizeof(cwd));
//        std::cout << "Current Path: " << cwd << " $ ";
//
//        std::string input;
//        std::getline(std::cin, input);
//
//        // Save command to history
//        history.insert(history.begin(), input);
//        if (history.size() > HISTORY_SIZE) {
//            history.pop_back();
//        }
//
//        if (input == "exit") {
//            break;
//        } else if (input == "history") {
//            std::cout << "Command History:\n";
//            for (const auto& cmd : history) {
//                std::cout << "  " << cmd << "\n";
//            }
//        } else if (input.find("cd ") == 0) {
//            // Change directory
//            std::string path = input.substr(3);
//            if (chdir(path.c_str()) != 0) {
//                std::cerr << "Error changing directory to " << path << "\n";
//            }
//        } else {
//            // External command
//            std::vector<std::string> args;
//            size_t pos = 0;
//            while ((pos = input.find(' ')) != std::string::npos) {
//                args.push_back(input.substr(0, pos));
//                input.erase(0, pos + 1);
//            }
//            args.push_back(input);
//
//            executeCommand(args);
//        }
//    }
//
//    return 0;
//}
