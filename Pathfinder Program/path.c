#include <stdio.h>
#include <stdbool.h>

void main(){
    //Declare variables
    FILE *fptr;
    bool isFound = 0;
    char c;
    char file_name[20];
    int i,j,M,N,entryCount=0;
    int entranceCoor[2]={0}, exitCoor[2]={0}, currentCoor[2]={0};
    
    //Ask the user to define the size of the field
    printf("Enter the amount of rows: ");
    scanf("%d",&M);
    printf("Enter the amount of columns: ");
    scanf("%d",&N);
    
    char array[M][N]; //This is the array to hold the field
    
    //Ask the user enter the file name
    printf("Type in the name of the file containing the field\n");
    scanf("%s", file_name);
    fptr=fopen(file_name, "r");
    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
            c=fgetc(fptr);
            while(!((c=='1')||(c=='0'))) c=fgetc(fptr);
            array[i][j]=c;
        }
    }
    fclose(fptr);
    
    
    //Display the array that was entered by the user
    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
            if(j==0){
                printf("\n");
            }
            printf("%c", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    /*
    *
    * Now that we have the field, we must find it's entrance and exit
    *
    */
    
    //Here the entrance and exit are calculated
    while(entryCount != 2){
        //Check the north edge
        for(i=0; i<N; i++){
            if(array[0][i] == '0' && entryCount == 0){
                entranceCoor[0] = 0;
                entranceCoor[1] = i;
                entryCount++;
            }
            else if(array[0][i] == '0' && entranceCoor != exitCoor){
                exitCoor[0] = 0;
                exitCoor[1] = i;
                entryCount++;
                break;
            }
        }
        //Check the east edge
        for(i=0; i<M; i++){
            if(array[i][N-1] == '0' && entryCount == 0){
                entranceCoor[0] = i;
                entranceCoor[1] = N-1;
                entryCount++;
            }
            else if(array[i][N-1] == '0' && entranceCoor != exitCoor){
                exitCoor[0] = i;
                exitCoor[1] = N-1;
                entryCount++;
                break;
            }
        }
        //Check the south edge
        for(i=N-1; i>=0; i--){
            if(array[M-1][i] == '0' && entryCount == 0){
                entranceCoor[0] = M-1;
                entranceCoor[1] = i;
                entryCount++;
            }
            else if(array[M-1][i] == '0' && entranceCoor != exitCoor){
                exitCoor[0] = M-1;
                exitCoor[1] = i;
                entryCount++;
                break;
            }
        }
        //check the west edge
        for(i=M-1; i>=0; i--){
            if(array[i][0] == '0' && entryCount == 0){
                entranceCoor[0] = i;
                entranceCoor[1] = 0;
                entryCount++;
            }
            else if(array[i][0] == '0' && entranceCoor != exitCoor){
                exitCoor[0] = i;
                exitCoor[1] = 0;
                entryCount++;
                break;
            }
        }
    }
    
    //Tell the user where the entrance and exit is
    printf("The entrance coordinate is (%d, %d)\n", entranceCoor[0], entranceCoor[1]);
    printf("The exit coordinate is (%d, %d)\n", exitCoor[0], exitCoor[1]);
    
    /*
    *
    *Now that we have our entrance and exit, we must start at the entrance and find the exit
    *(If there is one)
    * In this part we will use a switch statement to determine where to go
    */
    
    //Before we do anything we should set our direction
    char direction;
    if(entranceCoor[0] == 0){
        direction = 's'; //If the entrance is on the north side then face south
    }
    if(entranceCoor[1] == N-1){
        direction = 'w'; //If the entrance is on the east side then face west
    }
    if(entranceCoor[0] == M-1){
        direction = 'n'; //If the entrance is on the south side then face north
    }
    if(entranceCoor[1] == 0){
        direction = 'e'; //If the entrance is on the west side then face east
    }
    //We need to start at the entrance
    int row = entranceCoor[0], column = entranceCoor[1];
    //We can clearly show where the entrance and exit is with these labels
    array[row][column] = 'S';
    array[exitCoor[0]][exitCoor[1]] = 'F';
    
    /*
    *
    *This section looks really complicated below, but do no fear
    *It is just calculating which direction to go based on the actual
    *compass direction
    *I use n, e, s, w for North, East, South, and West
    *
    */
    while(isFound == 0){
        if(direction == 'n'){ //If we are facing NORTH
            if(array[row][column+1] != '1'){
                direction = 'e'; //Try going right
                column++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row-1][column] != '1'){
                direction = 'n'; //Try going straight
                row--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column-1] != '1'){
                direction = 'w'; //Try going left
                column--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row+1][column] != '1'){
                direction = 's'; //Try going backwards
                row++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
        }
        if(direction == 'e'){ //If we are facing East
            if(array[row+1][column] != '1'){
                direction = 's'; //Go right
                row++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column+1] != '1'){
                direction = 'e'; //Go straight
                column++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row-1][column] != '1'){
                direction = 'n'; //Go left
                row--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column-1] != '1'){
                direction = 'w'; //Go backwards
                column--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
        }
        if(direction == 's'){ //If we are facing South
            if(array[row][column-1] != '1'){
                direction = 'w'; //Go right
                column--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row+1][column] != '1'){
                direction = 's'; //Go straight
                row++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column+1] != '1'){
                direction = 'e'; //Go left
                column++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row-1][column] != '1'){
                direction = 'n'; //Go backwards
                row--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
        }
        if(direction == 'w'){ //If we are facing West
            if(array[row-1][column] != '1'){
                direction = 'n'; //Go right
                row--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column-1] != '1'){
                direction = 'w'; //Go straight
                column--;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row+1][column] != '1'){
                direction = 's'; //Go left
                row++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
            else if(array[row][column+1] != '1'){
                direction = 'e'; //Go backwards
                column++;
                array[row][column] = 'X';
                if(row == exitCoor[0] && column == exitCoor[1]){
                    isFound = 1;
                    break;
                }
                else if(row == entranceCoor[0] && column == entranceCoor[1]){
                    isFound = 1;
                    break;
                }
            }
        }
    }
    
    /*
    *
    *Now that we have either solved or have not solved the field
    *It is time to report it to the user and display the attempted fild
    */
    
    if(row == exitCoor[0] && column == exitCoor[1]){
        printf("The puzzle has been solved.\n");
    }
    else if(row == entranceCoor[0] && column == entranceCoor[1]){
        printf("There is no solution.\n");
    }
    
    //Diaplay the array once again
    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
            if(j==0){
                printf("\n");
            }
        printf("%c", array[i][j]);
        }
    printf("\n");
    }
    printf("\n");
}
