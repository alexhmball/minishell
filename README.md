
# Minishell - *as beautiful as a shell*

Minishell, as beautiful as a shell, is a project that allowed me to explore the world of Unix shell development. The project's goal was to create a functional shell, similar to Bash, capable of handling commands, executing programs, managing environment variables, and implementing various shell features.

## Learning Outcomes
Through the Minishell project, I achieved the following learning outcomes:

1. **Shell Architecture and Prompt Display:** I gained a comprehensive understanding of how shells operate and learned to display a user-friendly prompt while waiting for new commands.

2. **History Functionality:** I successfully implemented a working history feature, allowing users to access previous commands using up and down arrow keys.

3. **Command Execution:** I learned to search for and launch the right executable based on the PATH variable or using relative/absolute paths.

4. **Signal Handling:** I managed signals effectively by using a single global variable to indicate received signals, ensuring the signal handler did not access critical data structures.

5. **Quoting and Special Character Handling:** I implemented proper handling of single quotes, double quotes, and special characters to prevent unnecessary interpretation by the shell.

6. **Redirections and Pipes:** I successfully implemented input/output redirections and pipe functionality, allowing commands to interact with each other through pipes.

7. **Environment Variable Expansion:** I learned to handle environment variables (e.g., $PATH) and expand them to their respective values.

8. **Built-in Commands:** I implemented various built-in commands, such as echo, cd, pwd, export, unset, env, and exit, adhering to their specified functionalities.

9. **Error Handling and Memory Management:** I enhanced my skills in error handling and memory management, striving to minimize memory leaks and ensuring the efficiency of my code.

## Reflection
The Minishell project was an enlightening experience that provided me with an in-depth understanding of shell development and command-line processing. It challenged me to think critically about user input, command execution, and the behavior of various shell features.

By developing Minishell, I honed my skills in handling signals, managing memory, and ensuring proper command parsing and execution. I also gained a better appreciation for the complexities involved in creating a functional and user-friendly shell.

Overall, the Minishell project was a valuable learning opportunity that reinforced my understanding of Unix systems and shell programming. It allowed me to step into the shoes of developers from the past who strived to create user-friendly interfaces for interacting with computers, and I now have a deeper appreciation for the evolution of shells and their importance in the world of IT
