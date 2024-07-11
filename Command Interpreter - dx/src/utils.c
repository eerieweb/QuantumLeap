#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "utils.h"

// Function to handle file redirections.
void handle_redirection(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL;
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (strcmp(args[i], ">>") == 0) {
            args[i] = NULL;
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (strcmp(args[i], "<") == 0) {
            args[i] = NULL;
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        i++;
    }
}

// Function to handle piping.
void handle_piping(char **args) {
    int pipefd[2];
    pid_t pid;
    int i = 0;

    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL;
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                wait(NULL);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[1]);
                close(pipefd[0]);
                execvp(args[i + 1], args + i + 1);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
}
