#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
//all the commands get stored in this array
char input[100];
char *command[20];
int size_cmd = 0;
char *history[1000];
int proc_id[1000];
int hist = 0;
struct timeval start_time[1000];
struct timeval end_time[1000];
int num_commands = 0;
// max commands using pipe "|" can be 10
char *commands_[10];


//this function can be used for implementing the history command as told in 'g'
void print_history_cmd(){
    printf("%5s  %60s\t%17s\t%17s\t%9s\n","PID","Command","Start_time(ms)","End_time(ms)","Exec_time(ms)");
    for(int i=0; i<hist;i++){
        printf("%5d. %60s\t%10ld:%6ld\t%10ld:%6ld\t%9ld\n", proc_id[i], history[i],start_time[i].tv_sec,start_time[i].tv_usec,end_time[i].tv_sec,end_time[i].tv_usec,(end_time[i].tv_sec - start_time[i].tv_sec) * 1000000 + (end_time[i].tv_usec - start_time[i].tv_usec));
    }
    return;
}

void print_history_only(){
    printf("%7s %40s\n","PID","Command");
    for(int i=0; i<hist;i++){
        printf("%7d %40s\n", proc_id[i], history[i]);
    }
    return;
}

void add_command_to_history(char * command)
{
    history[hist++] = strdup(command);
}


// Used for seperating commands and arguments
char** seperate_user_input(char* usr_input){
    // char* output[10];
    // int j=0;
    // for(int i=0;i<usr_input[i]!="\0";i++){
    //     char* temp_string="";
    //     if(usr_input[i]==" "){
    //         output[j]=temp_string;
    //         temp_string=""; 
    //         j++;
    //         i++;
    //     }
    // }
    // return output;

    char *sep;
    size_cmd = 0;
    sep = strtok(input," ");
    while (sep != NULL)
    {
        command[size_cmd] = sep;
        size_cmd++;
        sep = strtok(NULL," ");
    }
    command[size_cmd] = NULL;
    return command;
    
}


// function for forking the process into two parts and executing using the array of arguments sreated in the seperate_usr_input function
int create_process_to_run(char** enter_the_ptr_to_Array){
    char **arr_of_args = enter_the_ptr_to_Array;
    pid_t processes_status_1=fork();

    if(processes_status_1<0){
        printf("Error in creating the child...");
        return 1;
    }
    else if (processes_status_1==0)
    {
        // printf("I'm the child process ID = %d",getpid());
        // if (strcmp(arr_of_args[0],"history") == 0){print_history_cmd();printf("\n");    }
        execvp(arr_of_args[0],arr_of_args);
        // printf("%d\n",ret);
        // printf("-1\n");
        // processes_status_1 = -1;
        perror("execvp");
        exit(EXIT_FAILURE);
        // printf("This is child process");
    }
    else{
        // printf("This is parent process");
        waitpid(processes_status_1,NULL,0);
    }
    


    return processes_status_1;
}

//this command accepts the user input of commands and the arguments and returns the execution status of the commands it gets executed
int launch(char* entered_text){
    int process_status;
    char** array_of_args = seperate_user_input(entered_text);
    process_status = create_process_to_run(array_of_args);

    //to print the history when the history command is entered
    // if(strcmp(entered_text,"history")==0){
    //     print_history_cmd();
    //     return 1;
    // }
    return process_status;

}


//This function is used to check the status of the function and print the status of the execution of the command inserted.
void process_status_fn(int status){
    if(status==1){
        printf("Successful execution of process");
    }
    else{
        printf("Process execution failed");
    }
}


//program execution starts here
int main(){
    // int i=0;

    // printf("Your command entered should not have a backslash or quotes in them. ");
    // printf(" ");

    //adding the 3-steps in the do-while loop in part 'a'
    do{
        //displaying the command prompt of out choice as asked in part 'b'
        memset(input,0,sizeof(input));
        printf("SimpleShell@Grp-52: > ");
        fgets(input,100,stdin);
        if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n'))
        {
        	input[strlen (input) - 1] = '\0';
        }
        // printf("input was = %s\n",input);
        // history[hist] = input;
        // hist++;
        add_command_to_history(input);
        // printf(" ");
        // printf("%s", input);
        if (strcmp(input,"exit") == 0) {print_history_cmd();break;}
        if (strcmp(input,"history") == 0){print_history_only();continue;}

        // note the start time
        gettimeofday(&start_time[hist-1],NULL);
        int process_status = launch(input);
        // note the end time
        gettimeofday(&end_time[hist-1],NULL);
        // printf("%d\n",process_status);
        proc_id[hist-1] = process_status;
        // if (process_status == -1){continue;}
        // process_status_fn(process_status);

        // i++;
    }while(1);


    return 0;
}