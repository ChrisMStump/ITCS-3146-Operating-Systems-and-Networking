Assignment Three Documentation

In this programming assignment, the user is given a menu to choose whether they want to:

1.	Display current date and time
2.	Display the calendar of the current month
3.	List the files in the current directory
4.	Exit the program

The program executes the fork command.
If child_pid is greater than 0 than that means that the fork command succeeded.
Now, there are two processes. A parent process and a child process. An if statement determines which commands are executed by the child and the other for the parent.
If child_pid is 0 meaning it is the child code then the program will go through an if and else if statement block to determine which system call the user wants to execute.
If child_pid is greater than 0 that means it is the parent process and the wait command is called which will make it wait until the child processes are finished.
The program will continue in the do while loop until the user selects 4 to terminate the program.
