# Operating_systems
## Project Description :
The main function consists of a do-while loop which is responsible for taking input of the command form the user and calling the launch function. The launch function then calls seperate_user_input function returning a " " separated array of strings
terminated by NULL. This array of strings is passed to create_process_and_run function that creates a child process and executes the input command using execvp() function.
The command input is taken to be less than 100 bytes and is assumed to have a maximum of 19 arguments. The history is only able to handle upto first 1000 commands only.

## How To Run :
Run the command "gcc simpleShell.c -o shell" and run "./shell" in the same directory in wsl.


#### Contributors : 
#### Manas Chhabra, Mann Nariya
