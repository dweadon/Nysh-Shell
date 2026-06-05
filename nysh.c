#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
// version 0.02.0
// commands
char *commands[] = {
    "spec",
    "whereami",
    "wipe",
    "hopon",
    "die",
    "say",
    "self",
    "selfroot",
    "sos",
    "nyamatrix",
    "respawn",
    "ghost",
};
// matrix built-in animation
int matrix(){    
    srand(time(NULL));
    printf("\033[2J\033[H");
    printf("\033[32m");

    while(1) {
        char symbol = (rand() % 94) + 33;
        printf("%c ", symbol);
        fflush(stdout);
        usleep(100); 
    }
}
// commands
void sos(){
    // just help command 
    int count = sizeof(commands) / sizeof(commands[0]);
    for (int i = 0; i < count; i++){
        printf("%s\n", commands[i]);
    }
}
void spec(){
    // list command
    pid_t pid = fork();
            if (pid == 0){
                // Child process
                char *args[] = {"ls", NULL};
                execvp("ls", args);
                perror("execvp");
            }
            else {
                // Parent process
                wait(NULL);
                
            }
}
void whereami(){
    // asks for current directory
    pid_t pid = fork();
            if (pid == 0){
                // Child process
                char *args[] = {"pwd", NULL};
                execvp("pwd", args);
                perror("execvp");
            }
            else {
                // Parent process
                wait(NULL);
            }

}
void self(){
    // ask for privileges and username
    pid_t pid = fork();
            if (pid == 0){
                // Child process
                char *args[] = {"whoami", NULL};
                execvp("whoami", args);
                perror("execvp");
            }
            else {
                // Parent process
                wait(NULL);
            }
}
void respawn(){
    // reboot option 
    pid_t pid = fork();
            if (pid == 0){
                // Child process
                char *args[] = {"systemctl", "reboot", NULL};
                execvp("systemctl", args);
                perror("execvp");
                
            }
            else {
                // Parent process
                wait(NULL);
            }
}
void ghost(){
    // processes running right now
    pid_t pid = fork();
            if (pid == 0){
                // Child process
                char *args[] = {"ps", NULL};
                execvp("ps", args);
                perror("execvp");
            }
            else{
                wait(NULL);
            }
}
int check(){
    // check function. whole brain of program
    char test[100];
    char name[1000] = "sheldon";
    char input[1000];
    char home[] = "/home/kill";
    char path[1000];
    getcwd(path, sizeof(path));
    
    char house[] = "/home/kill/code/output";
    
    while(1){
        //this section until "if" is input stuff
        char *shortpath = path + strlen(home);
        printf("%s@root:~%s$ ", name, shortpath);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        char *command = strtok(input, " ");
        char *argument = strtok(NULL, " ");
        
        
        // commands checks
        if (strcmp(command, "die") == 0) {
                break;
        }
        
        if (strcmp(input, "spec") == 0){
            spec();
        }
        else if (strcmp(input, "whereami") == 0){
            whereami();
        }
        else if (strcmp(input, "self") == 0){
            self();
        }
        else if (strcmp(input, "sos") == 0){
            sos();
        } 
        else if (strcmp(input, "respawn") == 0){
            respawn();
        }
        else if (strcmp(command, "hopon") == 0){
            if (argument == NULL){
                chdir(house);
            }
            else if(argument != NULL){
                chdir(argument);
                getcwd(path, sizeof(path));
            }
            
        }
        else if (strcmp(command, "spawn") == 0){
            if (argument == NULL){
                printf("You did not provide directory\n ");
            }
            else if(argument != NULL){
                
                mkdir(argument, 0777);
            }
        }
        else if (strcmp(input, "ghost") == 0){
            ghost();
        }
        else if(strcmp(input, "nyamatrix") == 0){
                matrix();
        }
        else if(strcmp(input, "wipe") == 0){
            system("clear");
        }
        // in case something goes wrong print:
        else{
            printf("Nysh: %s: command not found\n", input);
        
        }
    }
    return 0;
}
int main() {
    check();
}
