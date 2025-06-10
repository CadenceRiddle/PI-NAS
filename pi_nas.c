#include <stdlib.h>
#include <stdio.h>
#include <libssh/libssh.h>

int main(void){

    ssh_session session = ssh_new(); //create a new ssh object
    ssh_options_set(session, SSH_OPTIONS_HOST, "ENTER IP ADDRESS HERE"); //set the host address
    ssh_options_set(session, SSH_OPTIONS_USER, "ENTER USERNAME HERE"); //set the username

    if (ssh_connect(session) != SSH_OK) { //try to connect to the SSH server
        fprintf(stderr, "Error: %s\n", ssh_get_error(session)); //if connection fails, print the error
        return 1;
    }

    if (ssh_userauth_password(session, "pi", "your_password") != SSH_AUTH_SUCCESS) { //authenticate using username and password
        fprintf(stderr, "Auth failed: %s\n", ssh_get_error(session)); //if authentication fails, print the error
        return 1;
    }

    ssh_channel channel = ssh_channel_new(session); //create a new SSH channel

    if (channel == NULL) { //check if the channel was created successfully
        fprintf(stderr, "Error creating channel: %s\n", ssh_get_error(session)); 
        ssh_disconnect(session);
        ssh_free(session);
        return 1;
    }

    return 0;
}