#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>


// commands for "sos"
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
    "make",
    "spawn"
};

// matrix built-in animation
void matrix(char *argv[]){    
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
void sos(char *argv[]){
    int count = sizeof(commands) / sizeof(commands[0]);
    for (int i = 0; i < count; i++){
        printf("%s\n", commands[i]);
    }
}

void spec(char *argv[]){
    pid_t pid = fork();
    if (pid == 0){
        char *args[] = {"ls", NULL};
        execvp("ls", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}

void whereami(char *argv[]){
    pid_t pid = fork();
    if (pid == 0){
        char *args[] = {"pwd", NULL};
        execvp("pwd", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}

void self(char *argv[]){
    pid_t pid = fork();
    if (pid == 0){
        char *args[] = {"whoami", NULL};
        execvp("whoami", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}

void respawn(char *argv[]){
    pid_t pid = fork();
    if (pid == 0){
        char *args[] = {"systemctl", "reboot", NULL};
        execvp("systemctl", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}
void zap(char *argv[]){
    if (argv[1] == NULL){
        printf("usage: del <file>\n");
        return;
    }

    if (remove(argv[1]) == 0){
        printf("Nysh: deleted: %s\n", argv[1]);
    } else {
        perror("zap");
    }
}
void ghost(char *argv[]){
    pid_t pid = fork();
    if (pid == 0){
        char *args[] = {"ps", NULL};
        execvp("ps", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}

void spawn(char *argv[]){
    if (argv[1] == NULL){
        printf("Error: missing directory name\n");
    } else {
        if (mkdir(argv[1], 0777) == -1) {
            perror("Nysh");
            
        } 
    }
}

void hopon(char *argv[]){
    const char *home = "/home/kill/code";
    if (argv[1] == NULL){
        
        if (chdir(home) == -1)
            perror("Nysh");
    } else {
        if (chdir(argv[1]) == -1) {
            perror("Nysh");
            
        }
    }
}
void wipe(char *argv[])
{
    system("clear");
}
void make(char *argv[]){
    if (argv[1] == NULL){
        printf("Name of the program could not be defined\nUsage: make <filename>");
    }
    FILE *f = fopen(argv[1], "w");
    if (f == NULL){
        perror("Nysh");
        return;
    }
    fclose(f);
}
void say(char *argv[]){
    int i = 1;
    while (argv[i] != NULL){
        printf("%s ", argv[i]);
        i++;
    }
    printf("\n");
}
void show(char *argv[]){
    FILE* show;
    int character;
    show = fopen(argv[1], "r+");
    if (show == NULL) {
        perror("Nysh");
        
        return;
    }
    while ((character = fgetc(show)) != EOF) {
        putchar(character);
    }
    putchar('\n');
    fclose(show);
}
void edit (char *argv[]){
    FILE* show;
    int character;
    show = fopen(argv[1], "w");
    if (show == NULL) {
        perror("Nysh");
        
        return;
    }
    while ((character = fgetc(show)) != EOF) {
        putchar(character);
    }
    putchar('\n');
    fclose(show);
}
// function pointer now accepts argv
typedef void (*func_ptr)(char *argv[]);
// 
struct command_map {
    char *name;
    func_ptr function;
};
// command list for check
struct command_map cmd_table[] = {
    {"spec", spec},
    {"self", self},
    {"ghost", ghost},
    {"sos", sos},
    {"respawn", respawn},
    {"whereami", whereami},
    {"nyamatrix", matrix},
    {"spawn", spawn},
    {"hopon", hopon},
    {"make", make},
    {"wipe", wipe},
    {"say", say},
    {"show", show},
    {"edit",edit},
    {"zap", zap}
};

void check(){
    char name[] = "sheldon";
    char home[] = "/home/kill";
    char cwd[1024];

    while(1){
        char prompt[2000];

        getcwd(cwd, sizeof(cwd));

        char *shortpath = cwd;
        if(strncmp(cwd, home, strlen(home)) == 0)
            shortpath = cwd + strlen(home);

        sprintf(prompt, "%s@root:~%s$ ", name, shortpath);

        char *input = readline(prompt);
        if(!input) break;

        if(input[0] != '\0')
            add_history(input);

        if(strcmp(input, "die") == 0){
            free(input);
            break;
        }

        char *argv[64];
        int i = 0;

        char *token = strtok(input, " ");
        while(token){
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;

        if(!argv[0]){
            free(input);
            continue;
        }

        int found = 0;
        int count = sizeof(cmd_table) / sizeof(cmd_table[0]);

        for(int j = 0; j < count; j++){
            if(strcmp(argv[0], cmd_table[j].name) == 0){
                cmd_table[j].function(argv);
                found = 1;
                break;
            }
        }

        if(!found){
            pid_t pid = fork();
            if(pid == 0){
                execvp(argv[0], argv);
                perror("Nysh");
                exit(1);
            }
            wait(NULL);
        }

        free(input);
    }
}

int main(){
    check();
    return 0;
}
