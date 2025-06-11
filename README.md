# 🔗 Pipex

Welcome to **Pipex**, a project that dives deep into the UNIX mechanism of **pipes** 🧪!  
It is part of the 42 school curriculum and written in C. Through this project, you’ll learn how commands in shell are connected and executed using low-level process and file descriptor management.

---

## 📌 What is Pipex?

Pipex recreates the behavior of shell piping (`|`) by executing a sequence of commands where the output of one command is passed as input to the next.

This project replicates the functionality of:

```bash
< file1 cmd1 | cmd2 > file2
```
and extends it to support:

✅ Multiple chained commands

✅ Here document (<<) with appending redirection (>>)

---

## 💡 Key Concepts

* **Processes** 👤: Using fork to create child processes to run commands.
* **Pipes** 🧵: Connecting file descriptors with pipe() to transfer data between commands.
* **Redirection** ➡️: Using dup2() to redirect stdin/stdout as needed for piping.
* **Exec family** 🚀: Running external programs using execve().
* **Error handling & memory management** 🛠️: Carefully catching all errors and avoiding memory leaks.

---

## ⚙️ How it works

The basic execution format is: `./pipex file1 cmd1 cmd2 file2`

Which performs: `< file1 cmd1 | cmd2 > file2`

You can chain multiple commands: `./pipex infile "cmd1" "cmd2" "cmd3" "..." "cmdN" outfile`

Equivalent to: `< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile`

---

## 📝 Here-Doc Document

Support for the special case where input is taken from a delimiter, similar to shell's **<<**: `./pipex here_doc LIMITER "cmd1" "cmd2" outfile`

Equivalent to: `cmd1 << LIMITER | cmd2 >> outfile`

This allows your program to behave like a shell in more interactive and complex scenarios.
