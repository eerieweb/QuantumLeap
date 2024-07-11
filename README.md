# QuantumLeap

# Command Line Interpreter in C

This command line interpreter in C is a simple program designed to allow users to enter basic commands and execute built-in or external programs. It was developed as a learning project to demonstrate the fundamental principles of developing a shell.

## Features

- **Built-in Commands:** Supports `cd`, `help`, and `exit` commands.
- **External Command Execution:** Can execute external system commands like `ls`, `cat`, etc.
- **Process Management:** Uses `fork()`, `execvp()`, and `waitpid()` to create and manage processes when executing commands.
- **Command Parsing:** Splits user-entered commands into tokens for proper handling.

## Project Structure

```plaintext
interpreter/
├── src/
│   ├── main.c
│   ├── shell.c
│   ├── parser.c
│   ├── commands.c
│   ├── utils.c
│   └── ...
├── include/
│   ├── shell.h
│   ├── parser.h
│   ├── commands.h
│   ├── utils.h
│   └── ...
├── Makefile
└── .vscode/
    └── c_cpp_properties.json
```

- `src/` : Contains the main source files.
- `include/` : Contains the corresponding header files.
- `Makefile` : Automates the project compilation.
- `.vscode/` : Configuration for VSCode.

## Usage
Prerequisites
Ensure you have GCC (GNU Compiler Collection) installed on your system.

## Compilation
1 - Open a terminal in the project directory.

2 - Use the make command to compile the project.

```make```

## Execution
After compilation, run the generated program.

```./interpreter```

## Available Commands
Use commands like `cd`, `help`, `exit` to interact with the shell.
Execute external programs by typing their name, such as `ls`, `cat`, `etc`.

## Example
To launch the shell and execute a few commands:
```$ ./interpreter
Prompt> help
Shell Help
Type program names and arguments, and hit enter.
The following are built-in:
  cd
  help
  exit
Use the man command for information on other programs.
Prompt> cd ..
Prompt> ls
README.md  include/  main.c  Makefile  src/
Prompt> exit
$
```
## Contribution
Contributions are welcome! For bug fixes, feature improvements, or suggestions, please open an issue or submit a pull request.


## Note
Make sure to replace interpreter with the actual name of your executable if different.
Customize the specific details of your project, including examples and structure, according to your configuration.


```This README provides a clear and concise overview of your project, its features, usage instructions, and project structure. Be sure to keep it updated with any changes to your project.```






