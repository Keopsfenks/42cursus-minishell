#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_PATH_LEN 1024

void execute_command(char *command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Çocuk işlem
        char *args[64];
        char *token = strtok(command, " ");
        int arg_index = 0;
        
        while (token != NULL) {
            args[arg_index++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_index] = NULL;

        // Komutun tam yolunu bulma
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "/bin/%s", args[0]);
        
        execve(full_path, args, NULL);
        perror("execve error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Ebeveyn işlem
        wait(NULL);
    } else {
        // Fork hatası
        perror("fork error");
    }
}

int main() {
    char *buffer;
    
    while (1) {
        buffer = readline("Minishell> ");
        
        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            break;
        }
        
        execute_command(buffer);
        
        add_history(buffer);
        free(buffer);
    }
    
    return 0;
}
