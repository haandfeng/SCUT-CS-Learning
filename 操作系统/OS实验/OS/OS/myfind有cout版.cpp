#include <iostream>
#include <cstring>
#include <dirent.h>
#include <fnmatch.h>  // Add this include for fnmatch
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

void findFiles(const char* path, const char* name, int mtime) {
    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build full path
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Get file status
        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            closedir(dir);
            return;
        }

        // Check for -name option
        if (name && fnmatch(name, entry->d_name, FNM_PERIOD) != 0) {
            continue; // Name does not match
        }

        // Check for -mtime option
        if (mtime > 0) {
            time_t current_time = time(nullptr);
            time_t modified_time = file_stat.st_mtime;
            int days_difference = (current_time - modified_time) / (60 * 60 * 24);
//3>1
            if (days_difference > mtime) {
                continue; // Modification time does not match
            }
        }

        // Print the matching file path
        std::cout << full_path << std::endl;

        // Recursively search directories
        if (S_ISDIR(file_stat.st_mode)) {
            findFiles(full_path, name, mtime);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " PATH -option parameters" << std::endl;
        return 1;
    }

    const char* path = argv[1];
    const char* name = nullptr;
    int mtime = -1;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "-name") == 0 && i + 1 < argc) {
            name = argv[i + 1];
            ++i;
        } else if (strcmp(argv[i], "-mtime") == 0 && i + 1 < argc) {
            mtime = atoi(argv[i + 1]);
            ++i;
        }
    }
    std::cout << mtime << std::endl;
    findFiles(path, name, mtime);

    return 0;
}
