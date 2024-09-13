# `minishell` -- Simple Shell Client in C

minishell is a simple shell client written in C that replicates many of the basic functionalities of the bash shell. This group project includes support for command execution, history, redirections, pipes, environment variables, and various built-in commands.

## Learning Outcomes

### Challenges faced

- This project presented a higher level of complexity and scope compared to previous ones, requiring a more strategic approach.
- The project requirements from the school were vague regarding the extent of feature implementation. While recreating Bash in its entirety was beyond the scope, there were ambiguous aspects, such as whether environment variables in heredocs should be replaced. Answers from classmates were often conflicting.
- Personally, understanding how pipes functioned was a challenge; hands-on experimentation proved to be the most effective learning method.


### Key Takeaways

- Planning the project and deeply understanding Bash's intricacies proved invaluable. Unlike other students who had to restart multiple times, I was able to retain most of my code throughout the project. In terms of defining project scope, you generally have the flexibility to implement features as long as you can justify them to evaluators. If not specifically mentioned in the project requirements (e.g., subshells), the decision to include a feature is up to the student.
- Although I didn’t enforce it with my teammate, working with separate branches for different features often resolved conflicting changes effectively.

### New Technologies or Techniques

- In addition to me starting to use more of git's features and spending more time on the planning phase of the project, I learned techniques regarding file manipulation, signal handling, code structure, and project planning.

### Code Architecture/Approach

- Using tokens was a particularly effective approach. While other students focused heavily on string manipulation, I found that breaking down strings into multiple tokens and applying operations to these tokens helped maintain clear and organized logic.
- Modular code also facilitated debugging and the division of responsibilities.

### In Retrospect

- Implementing a suite of automated tests would have greatly benefited the development process. Although creating automated tests is time-consuming, it ultimately saves time in manual testing and catches errors early, especially given the many edge cases in this project. Learning to create automated tests is a valuable skill for software developers.
## Features

### Command Execution

- **Prompt**: Displays a prompt while waiting for a new command.
- **History**: Maintains a history of executed commands, allowing you to navigate through previous commands.
- **Executable Search**: Locates and executes the correct executable based on the `PATH` environment variable, as well as relative or absolute paths.

### Quoting and Special Characters

- **Single Quotes** (`'`): Prevents the shell from interpreting meta-characters within the quoted sequence.
- **Double Quotes** (`"`): Prevents the shell from interpreting meta-characters within the quoted sequence, except for $ (dollar sign).
- **Unclosed Quotes and Special Characters**: The shell does not interpret unclosed quotes or special characters such as `\` or `;` .

### Redirections

- **Input Redirection** (`<`): Redirects input from a file.
- **Output Redirection** (`>`): Redirects output to a file, overwriting the file if it exists.
- **Append Output Redirection** (`>>`): Redirects output to a file, appending to the file if it exists.
- **Heredoc** (`<<`): Accepts input until a line containing a specified delimiter is seen. This input is not added to the command history.

### Pipes

- **Pipes** (`|`): Connects the output of one command to the input of the next command in a pipeline.

### Environment Variables

- **Environment Variables** (`$VAR`): Expands to the value of the specified environment variable.
- **Exit Status** (`$?`): Expands to the exit status of the most recently executed foreground pipeline.

### Signal Handling in Interactive Mode
- `Ctrl-C`: Displays a new prompt without terminating the shell.
- `Ctrl-D`: Exits the shell.
- `Ctrl-\`: Ignored by the shell, mirroring bash behavior.

### Built-in Commands

The following built-in commands are implemented with specific options:

- `echo`: Supports the `-n` option to suppress the trailing newline.
- `cd`: Supports changing directories, using either relative or absolute paths.
- `pwd`: Prints the current working directory, without any options.
- `export`: Exports variables to the environment, with no additional options.
- `unset`: Unsets environment variables, with no additional options.
- `env`: Prints the environment variables, without any options or arguments.
- `exit`: Exits the shell, with no options.

### Logical Operators

- **Logical AND** (`&&`) **and OR** (`||`): Supports command chaining with logical operators, respecting parenthesis for prioritization.

### Wildcards

**Wildcard Expansion** (`*`): Expands to match filenames in the current working directory.

## Installation and Usage

### Dependencies

This project relies on the [GNU readline](https://tiswww.case.edu/php/chet/readline/rltop.html) library. Readline is a standard library on most Linux systems. MacOS users can obtain readline from [Homebrew](https://formulae.brew.sh/formula/readline#default).

### Building the Shell

To build the shell, simply run:

```bash
make
```

### Running the Shell

Once built, you can start the shell by executing:

```bash
./minishell
```

### Exiting the Shell

You can exit the shell you have two options:
- Use the `exit` command
- Press `Ctrl-D`

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/DavePie/MiniShell/blob/master/LICENSE) file for details.
