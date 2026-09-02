# C - Simple Shell

## Description
A simple UNIX command interpreter built in C as part of the Holberton School curriculum. This shell mimics basic functionalities of the standard `sh` shell, supporting both interactive and non-interactive execution modes.

## Authors
- Noura Nasser Alotaibi (nourahnassiralotaibi1999@gmail.com)
- Saud Zaid Alhammadi (saud.zaid.442@gmail.com)

## Features
- **Interactive Mode:** Displays a prompt (`($) `) and waits for user input.
- **Non-Interactive Mode:** Reads and executes commands piped or redirected from standard input.
- **Command Execution:** Uses system calls (`fork`, `execve`, `wait`) to execute commands safely.
- **PATH Resolution:** Searches for executable command binaries within the `PATH` environment variable.

## Requirements
- Allowed editors: `vi`, `vim`, `emacs`
- Compilation Environment: Ubuntu 20.04 LTS
- Compiler Flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Coding Style: Follows the Betty style guide.

## Compilation
To compile the shell, run:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage
### 1. Interactive Mode
```bash
$ ./hsh
($) /bin/ls
($) exit
```

### 2. Non-Interactive Mode
```bash
$ echo "/bin/ls" | ./hsh
```
