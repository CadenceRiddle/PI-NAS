#include <stdlib.h>
#include <stdio.h>
#include <libssh/libssh.h>

int main(void){
    ssh_session session = ssh_new(); //create a new ssh object
    ssh_options_set(session, SSH_OPTIONS_HOST, "ENTER IP ADDRESS HERE"); //set the host address
    ssh_options_set(session, SSH_OPTIONS_USER, "ENTER USERNAME HERE"); //set the username

    return 0;
}