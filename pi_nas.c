#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 2) { // Check if the correct number of arguments is provided
        fprintf(stderr, "Usage: %s <path-to-local-file>\n", argv[0]);
        return 1;
    }

    const char* local_file = argv[1]; // Local file path provided as command line argument
    const char* remote_user = "USERNAME"; // Remote user
    const char* remote_ip = "IP"; // VPN IP
    const char* remote_path = "PATH";
    
    char command[512]; // Buffer to hold the SCP command
    snprintf(command, sizeof(command), 
        "scp \"%s\" %s@%s:%s",
        local_file, remote_user, remote_ip, remote_path
    ); // Construct the SCP command

    int result = system(command); // Execute the SCP command

    if (result != 0) {
        fprintf(stderr, "Error: file transfer failed (scp exit code %d)\n", result);
        return 1;
    } // Check if the command was successful

    return 0;
}