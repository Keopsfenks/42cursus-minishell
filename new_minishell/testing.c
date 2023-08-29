#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void execute_command(char *command) {
    // Bellek tahsisi
    char *args[64];
    char *token = strtok(command, " ");
    int arg_index = 0;
    
    while (token != NULL) {
        args[arg_index++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_index] = NULL;
    
    // Çocuk işlem oluşturma
    pid_t pid = fork();
    
    if (pid == 0) {
        // Çocuk işlem
        execvp(args[0], args);
        perror("execvp error");
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
        
        // "exit" komutu ile çıkış yap
        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            break;
        }
        
        // Komutu çalıştır
        execute_command(buffer);
        
        // Geçmişi kaydet
        add_history(buffer);
        free(buffer);
    }
    
    return 0;
}
