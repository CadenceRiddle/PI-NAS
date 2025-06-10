#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define MAX_FIELD 64
#define MAX_PATH 256

// Helper to trim both \n and \r from strings
void trim_newline(char* str) {
    str[strcspn(str, "\r\n")] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-local-file>\n", argv[0]);
        return 1;
    }

    const char* local_file = argv[1];
    char remote_ip[MAX_FIELD] = {0};
    char remote_user[MAX_FIELD] = {0};
    char remote_path[MAX_PATH] = {0};

    // Open config file
    FILE *config = fopen("config.txt", "r");
    if (!config) {
        perror("Failed to open config.txt");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), config)) {
        trim_newline(line);  // Clean the line first

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

    // Validate all fields were populated
    if (strlen(remote_ip) == 0 || strlen(remote_user) == 0 || strlen(remote_path) == 0) {
        fprintf(stderr, "Invalid config file: missing ip, user, or path.\n");
        return 1;
    }

    // Debug print (safe to remove later)
    printf("DEBUG:\n  user='%s'\n  ip='%s'\n  path='%s'\n", remote_user, remote_ip, remote_path);

    // Build the scp command
    char command[512];
    snprintf(command, sizeof(command),
        "scp \"%s\" %s@%s:\"%s\"",
        local_file, remote_user, remote_ip, remote_path
    );

    // Execute it
    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "File transfer failed (scp exit code %d)\n", result);
        return 1;
    }

    return 0;
}
