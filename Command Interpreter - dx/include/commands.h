#ifndef COMMANDS_H
#define COMMANDS_H

int shell_num_builtins();
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_launch(char **args);

#endif
