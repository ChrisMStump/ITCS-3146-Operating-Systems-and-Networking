#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Linked list to hold the words in a paragraph.
struct wordList{
	char *word;
	struct wordList *next;
};
//Linked list to hold each paragraph.
struct paragraphList{
	struct wordList *firstWord;
	struct paragraphList *next;
}*paraHead = NULL, *paraTail = NULL;

//These are the function prototypes.
void readFile();
void justifyText(int);
void printText(char *line, int lineSize);
char * getLine(FILE *fp);
void newParagraph();
void removeParagraph();
void addWord(char *string);
char * removeWord();


int main(){
    int lineSize;
    readFile();
    printf("Enter the number of characters to be printed per line (40 - 100): ");
    scanf("%d",&lineSize);
	justifyText(lineSize);
}

//This function reads the file and puts the lines of text into the dually linked list.
void readFile(){
	FILE *fp = NULL;
	char fileName[50];		// Holds the name of the file.
	char *line;				// Holds the string of a line from the file.
	char *lineTok;			// Line after it has been tokenized.
	char *String = malloc(30*sizeof(char));

	// Ask for the file name.
    printf("Enter the file name containing the text: ");
    scanf("%s",fileName);
    fp = fopen(fileName,"r"); //Open the file.


	// Create the first paragraph.
	newParagraph();

	// Keep reading until the end of the file.
	while(!feof(fp)){
		line = getLine(fp);	// Get line of text from the file
		if(strlen(line) == 0){ //If there is an empty line, then this is the start of a new paragraph.
			if(paraTail->firstWord != NULL){
				newParagraph();
			}
		}
		else{
			lineTok = strtok(line," ");	// Tokenize the line of text.
			while(lineTok != NULL){ //Add each word into the word list.
				addWord(lineTok);
				lineTok = strtok(NULL," ");
			}
		}
	}
	fclose(fp);
}

// Goes through the dually linked list of words and justifies the text according to the specified size.
void justifyText(int lineSize){
	char *line, *word;

	printf("\n");	// Line break

	// Get memory for justified line.
	line = malloc(sizeof(char)*(lineSize + 1));

	strcpy(line,""); // Clear the current value of line.

	// While the are more paragraphs to be read.
	while(paraHead != NULL && paraHead->firstWord != NULL){
		word = removeWord();	// Get the next word in the list

		// Is it the last word?
		if(paraHead->firstWord == NULL){
			// Is the current line empty?
			if(strlen(line) == 0){
				printf("%s\n\n",word); //Just print the word.
			}
			else{ // If current line is not empty
				if((strlen(line) + strlen(word) + 2) <= (lineSize + 1)){ // Will it fit on the line?
					printf("%s %s\n\n",line,word); // If so, then concatenate it and print the line.
				}
				else{ // If it won't fit on the line
					// Print the word on the next line.
					printText(line,lineSize);
					printf("%s\n\n",word);
				}
				strcpy(line,""); // Clear line since it has already been printed.
			}
			removeParagraph(); // The paragraph is done with so it should be deleted.
		}
		else{ //If the word is not the last word.
			if((strlen(line) + strlen(word) + 2) <= (lineSize + 1)){ //Will it fit on the current line?
				if(strlen(line) == 0){ //If the line is empty add the word.
					strcpy(line,word);
				}
				else{ //If not empty just concatenate the word to the end.
					sprintf(line, "%s %s", line, word);
				}
			}
			else{ //If it does not fit on the line,
				printText(line,lineSize); //Print the current line and start a new line with the current word.
				strcpy(line,word);
			}
		}
	}
	free(line);
}

// Function to get a line from the file
char * getLine(FILE *fp){
	char *line = NULL, *temp = NULL;
	size_t size = 0, index = 0;
	int currentLetter = 1;

	// While we haven't reached the end of the line.
	while(currentLetter){
		currentLetter = fgetc(fp); //Go through each character.
		if(currentLetter == EOF || currentLetter == '\n'){
			currentLetter = 0; //Sentinel
		}
		if(size <= index){
			size += sizeof(char);
			temp = realloc(line,size);
			if(!temp){
				free(line);
				line = NULL;
				break;
			}
			line = temp;
		}
		line[index++] = currentLetter; //Add the character to the line.
	}
	return line;
}

// Function to print a justified line of text.
void printText(char *line, int lineSize){
	int i, j;
	int evenSpaceDistribute, spaceRemainder; // Used to compute the number of spaces that need to be distributed.
	int existingSpaces, remainingSpaces; // Number of existing spaces, and the additional space in the line

	// How many more spaces need to be printed to justify?
	remainingSpaces = lineSize - strlen(line);

	// How many spaces are there currently?
	existingSpaces = 0;
	for(i = 0; line[i] != '\0'; i++){
		if(isspace(line[i])){
			existingSpaces++;
		}
	}
	// If there is already the correct amount of characters print the line.
	if(remainingSpaces == 0){
		printf("%s\n",line);
		return;
	}

	evenSpaceDistribute = (remainingSpaces + existingSpaces) / existingSpaces;	// Number of spaces that will be equally distributed
	spaceRemainder = (remainingSpaces + existingSpaces) % existingSpaces;	// Number of remaining spaces to distribute

	// Distribute spaces throughout the text to justify.
	for(i = 0; line[i] != '\0'; i++){
		if(isspace(line[i])){
			for(j = 0; j < evenSpaceDistribute; j++){
				printf("%c",' ');
			}
			if(spaceRemainder > 0){
				printf("%c",' ');
				spaceRemainder--;
			}
		}
		else{
			printf("%c",line[i]);
		}
	}
	printf("\n");
}

// Create a new paragraph.
void newParagraph(){
    struct paragraphList *newPara;
    newPara = malloc(sizeof(struct paragraphList));

	// Initialize the contents.
    newPara->firstWord = NULL;
    newPara->next = NULL;

    if(paraHead == NULL){ //If there are no other paragraphs this is the first.
        paraHead = newPara;
    }
    else{ //If the first then it is the last.
        paraTail->next = newPara;
    }
    paraTail = newPara;
}

// Function the adds a word to a word list.
void addWord(char *string){
    struct wordList *newWord;
    newWord = malloc(sizeof(struct wordList));

    newWord->word = string;
    newWord->next = NULL;

	// If it is the first word reference firstWord to that word.
    if(paraTail->firstWord == NULL){
        paraTail->firstWord = newWord;
    }
    else{
        struct wordList *current = paraTail->firstWord;
        while(current->next != NULL){ //Go to the end of the list and put the word there
            current = current->next;
        }
        current->next = newWord;
    }
}

// Function to remove the header paragraph
void removeParagraph(){
	struct paragraphList *temp = paraHead;	//Temp holds the first paragraph.
	paraHead = paraHead->next; //Dereference the header paragraph.
	free(temp);
}

// Removes word from the list.
char * removeWord(){
	struct wordList *temp = paraHead->firstWord;
	char *string = temp->word;
	paraHead->firstWord = paraHead->firstWord->next; // The first word becomes the next word.
	free(temp);
	return string;
}
