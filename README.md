# `minishell` -- Simple Shell Client in C
## Overview

minishell is a simple shell client written in C that replicates many of the basic functionalities of the bash shell. This project includes support for command execution, history, redirections, pipes, environment variable handling, and various built-in commands. The shell is designed to operate with minimal use of global variables, particularly to handle signals securely without exposing the main data structures.
## Features
### Command Execution
- Prompt: Displays a prompt while waiting for a new command.
- History: Maintains a history of executed commands, allowing you to navigate through previous commands.
- Executable Search: Locates and executes the correct executable based on the PATH environment variable, or using a relative or absolute path.

### Quoting and Special Characters

- Single Quotes ('): Prevents the shell from interpreting meta-characters within the quoted sequence.
- Double Quotes ("): Prevents the shell from interpreting meta-characters within the quoted sequence, except for $ (dollar sign).
- Unclosed Quotes and Special Characters: The shell does not interpret unclosed quotes or special characters such as \ (backslash) or ; (semicolon).

### Redirections

- Input Redirection (<): Redirects input from a file.
- Output Redirection (>): Redirects output to a file, overwriting the file if it exists.
- Append Output Redirection (>>): Redirects output to a file, appending to the file if it exists.
- Heredoc (<<): Accepts input until a line containing a specified delimiter is seen. This input is not added to the command history.

### Pipes
- Pipes (|): Connects the output of one command to the input of the next command in a pipeline.

### Environment Variables

- Environment Variables (`$VAR`): Expands to the value of the specified environment variable.
- Exit Status (`$?`): Expands to the exit status of the most recently executed foreground pipeline.

### Signal Handling in Interactive Mode
- Ctrl-C: Displays a new prompt on a new line without terminating the shell.
- Ctrl-D: Exits the shell.
- Ctrl-\: Ignored by the shell, similar to bash behavior.

### Built-in Commands

The following built-in commands are implemented with specific options:

- `echo`: Supports the -n option to suppress the trailing newline.
- `cd`: Supports changing directories using only relative or absolute paths.
- `pwd`: Prints the current working directory, without any options.
- `export`: Exports variables to the environment, with no additional options.
- `unset`: Unsets environment variables, with no additional options.
- `env`: Prints the environment variables, without any options or arguments.
- `exit`: Exits the shell, with no options.

### Logical Operators

 Logical AND (&&) and OR (||): Implements command chaining with logical operators, respecting parenthesis for prioritization.

### Wildcards

Wildcard Expansion (*): Expands wildcards to match filenames in the current working directory.

## Installation and Usage
### Building the Shell

To build the shell, simply run:

```make```

Running the Shell

Once built, you can start the shell by executing:

```./minishell```

Exiting the Shell

You can exit the shell by typing exit or by pressing Ctrl-D.
## License

This project is licensed under the MIT License. See the LICENSE file for details.
