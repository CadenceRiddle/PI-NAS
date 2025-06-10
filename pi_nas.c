#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // for stat()
#include <unistd.h>    // for access()

#define MAX_LINE 128
#define MAX_FIELD 64
#define MAX_PATH 256

// Trim newline and carriage return characters
void trim_newline(char* str) {
    str[strcspn(str, "\r\n")] = '\0';
}

// Check if path is a directory
int is_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file-or-directory-to-transfer>\n", argv[0]);
        return 1;
    }

    const char* local_path = argv[1];
    char remote_ip[MAX_FIELD] = {0};
    char remote_user[MAX_FIELD] = {0};
    char remote_path[MAX_PATH] = {0};

    FILE *config = fopen("config.txt", "r");
    if (!config) {
        perror("Failed to open config.txt");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), config)) {
        trim_newline(line);

        if (strncmp(line, "ip=", 3) == 0) {
            strncpy(remote_ip, line + 3, MAX_FIELD - 1);
            trim_newline(remote_ip);
        } else if (strncmp(line, "user=", 5) == 0) {
            strncpy(remote_user, line + 5, MAX_FIELD - 1);
            trim_newline(remote_user);
        } else if (strncmp(line, "path=", 5) == 0) {
            strncpy(remote_path, line + 5, MAX_PATH - 1);
            trim_newline(remote_path);
        }
    }
    fclose(config);

    if (strlen(remote_ip) == 0 || strlen(remote_user) == 0 || strlen(remote_path) == 0) {
        fprintf(stderr, "Invalid config file: missing ip, user, or path.\n");
        return 1;
    }

    // Determine if path is a directory
    int is_dir = is_directory(local_path);

    // Choose -r flag if it's a directory
    const char *scp_flags = is_dir ? "-r" : "";

    // Build scp command
    char command[1024];
    snprintf(command, sizeof(command),
        "scp %s \"%s\" %s@%s:\"%s\"",
        scp_flags, local_path, remote_user, remote_ip, remote_path
    );

    // Run it
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "File or directory transfer failed (scp exit code %d)\n", result);
        return 1;
    }

    return 0;
}
