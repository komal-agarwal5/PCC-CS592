# PCC-CS592

This repository contains various assignments covered as part of the Operating Systems Lab. The assignments cover a wide range of topics including shell scripting, process synchronization, inter-process communication, and more.

## Getting Started

Follow the instructions below to set up and use the contents of this repository.

### Prerequisites

- A Unix-like operating system (Linux, macOS) or a Unix shell environment on Windows (e.g., Git Bash, WSL).
- GCC compiler for compiling C programs.
- AWK for running AWK scripts.

### Cloning the Repository

Clone this repository to your local machine using the following command:

```sh
git clone https://github.com/komal-agarwal5/PCC-CS592.git
```

### Running Shell Scripts from the Terminal

To execute your bash scripts from the terminal, you can either change the permissions to make the script executable or run it directly using the `bash` command. 

To change permissions and run the script:

```sh
chmod u+x <script_name>.sh
./<script_name>.sh
```
Alternatively, you can run the script directly with:
```sh
bash <script_name>.sh
```

To run AWK scripts, use the following command:
```
awk -f <script_name>.awk input_file
```

### Running C programs:

For general C programs, use:

```
gcc <program_name>.c -o <executable_name>
```

To run the compiled program:

```   
./<executable_name>
```

To run the program in the background (allowing terminal access while the process runs):

```   
./<executable_name> &
```

For checking zombie processes, you can run the ps -f f command while one of the processes is still executing. 