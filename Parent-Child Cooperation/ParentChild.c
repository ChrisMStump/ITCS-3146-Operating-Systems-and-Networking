#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(){
    pid_t child_pid;
    int input = 0;
    do{ //Give the user a menu to choose from
        printf("Choose the function to be performed by the child:\n");
        printf("(1) Display current date and time\n");
        printf("(2) Display the calendar of the current month\n");
        printf("(3) List the files in the current directory\n");
        printf("(4) Exit from the program\n");
        printf("Enter your choice: ");
        scanf("%d",&input);
        
        child_pid = fork();
        
        if(child_pid >= 0){ //Check whether or not the fork() command succeeded
			if(child_pid == 0){ //To be executed by the CHILD
       
				if(input==1){ //The user input will determine which system command is called
					printf("\nChild process ID %ld; Parent ID %ld \n\n",(long)getpid(),(long)getppid());
					system("date");
				}
				else if(input==2){
					printf("\nChild process ID %ld; Parent ID %ld \n\n",(long)getpid(),(long)getppid());
					system("cal");
				}
				else if(input==3){
					printf("\nChild process ID %ld; Parent ID %ld \n\n",(long)getpid(),(long)getppid());
					system("ls -l");
				}
				else if(input==4){
					printf("\nProgram terminated \n\n");
					exit(1);
				}
				else{ //If the user did not enter in a valid number
					printf("You did not enter a valid choice\n\n");
					exit(0);
				}  
                exit(0); //Exit the loop
			} 
			else{ //To be executed by the PARENT
				wait(NULL); //Wait for the child process to finish
				printf("\nCurrent process PID %ld \n\n ", (long)getpid());
			}
        }
		else{  //If fork failed
        printf("Failed to fork\n");
        return 1;
        }
    }
    while(input!=4); //Keep the program running until the user wishes to exit
    return 0;
}