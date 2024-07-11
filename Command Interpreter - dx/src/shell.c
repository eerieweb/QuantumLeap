#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell.h"
#include "parser.h"
#include "commands.h"
#include "utils.h"

#define BUFFER_SIZE 1024

void shell_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        handle_redirection(args); // Ajout de la gestion des redirections
        handle_piping(args); // Ajout de la gestion des pipes
        status = shell_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *shell_read_line() {
    char *line = NULL;
    ssize_t bufsize = 0; // getline() will allocate a buffer for us
    getline(&line, &bufsize, stdin);
    return line;
}

char **shell_split_line(char *line) {
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int shell_execute(char **args) {
    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    for (int i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}

int shell_launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
