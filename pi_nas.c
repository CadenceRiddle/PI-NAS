#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum lengths for strings we're going to read
#define MAX_LINE 128
#define MAX_FIELD 64
#define MAX_PATH 256

int main(int argc, char *argv[]) {
    // Check that exactly one argument (file to upload) is passed
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-local-file>\n", argv[0]);
        return 1;
    }

    // Store the local file path from the command-line argument
    const char* local_file = argv[1];

    // Buffers to store values from config.txt
    char remote_ip[MAX_FIELD] = {0};
    char remote_user[MAX_FIELD] = {0};
    char remote_path[MAX_PATH] = {0};

    // Open the config file
    FILE *config = fopen("config.txt", "r");
    if (!config) {
        perror("Failed to open config.txt");
        return 1;
    }

    // Read each line of the config file
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), config)) {
        // Check for "ip=" line
        if (strncmp(line, "ip=", 3) == 0) {
            strncpy(remote_ip, line + 3, MAX_FIELD - 1);
            remote_ip[strcspn(remote_ip, "\n")] = '\0'; // Remove newline
        }
        // Check for "user=" line
        else if (strncmp(line, "user=", 5) == 0) {
            strncpy(remote_user, line + 5, MAX_FIELD - 1);
            remote_user[strcspn(remote_user, "\n")] = '\0';
        }
        // Check for "path=" line
        else if (strncmp(line, "path=", 5) == 0) {
            strncpy(remote_path, line + 5, MAX_PATH - 1);
            remote_path[strcspn(remote_path, "\n")] = '\0';
        }
    }
    fclose(config); // Done with the config file

    // Make sure all fields were loaded
    if (strlen(remote_ip) == 0 || strlen(remote_user) == 0 || strlen(remote_path) == 0) {
        fprintf(stderr, "Invalid config file: missing ip, user, or path.\n");
        return 1;
    }

    // Prepare the scp command
    char command[512];
    snprintf(command, sizeof(command),
        "scp \"%s\" %s@%s:\"%s\"",
        local_file, remote_user, remote_ip, remote_path
    );

    // Execute the SCP command to send the file
    int result = system(command);

    // Report success or failure
    if (result != 0) {
        fprintf(stderr, "File transfer failed (scp exit code %d)\n", result);
        return 1;
    }

    return 0;
}
