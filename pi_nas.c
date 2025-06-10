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
    

    return 0;
}