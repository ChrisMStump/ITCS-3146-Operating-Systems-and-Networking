Program Documentation

Part 1.
The main data structures used in this program is two linked lists.
The first linked list called ‘wordList’ holds every word for a given paragraph.
The second linked list called ‘paragraphList’ which holds each of the wordList’s.
Basically, it is a dually linked list.

When the program first executes, the ‘readFile’ function is called. This is where the user enters the file name.
One the file name is enter the program opens the file to read. The ‘getLine’ function is called the read the file line by line.
 The ‘getLine’ function reads in a line character by character and stores each character into an array of characters. This continues until ‘getLine’ reaches the end of line character or “/0”.
Once the program has read in an entire line it is able to be tokenized using the space as a delimiter. Then, one by one, each token is added into a linked list. The words are added into the same linked list until the program reaches a line with size 0. This means that there is a start to a new paragraph. Once the program reaches a line with size 0, a new paragraph is created and the program will continue reading in the lines. These steps continue until it reaches the end of file.

Part 2.
Now that we have all the text separated by paragraphs in the dually linked list structure, the next step is to justify the text.
The program asks the user the length of the line to be printed.
Then, the ‘justifyText’ function is called passing along the ‘lineSize’ as a parameter.
The program goes through the ‘paragraphList’ structure until there are no more paragraphs to be read.

There are a couple conditions which the program looks for:

1.	Is it the last word in the ‘wordList’ structure?
2.	Will the word fit on the current with the size specifications?

If it is the last word the program will delete that paragraph and move onto the next one.
If it is not the last word then it will just continue going through the words.
This part of the program is sort of like the delete key on the keyboard because it goes through deleting each word in the list from the beginning to the end and deletes the paragraphs in order from beginning to the end.
The program removes words and paragraphs by pointing the ‘firstWord’ or ‘firstPara’ to the next word or paragraph and this dereferences them.

The actual printing of the text occurs as the words and paragraphs are being deleted in the ‘printText’ function. Once a line is full according to the specified size, the program determines how many more characters are needed to be justified.
The program calculates the amount of spaces it needs left to be justified and then adds extra spaces where there are already spaces in order to justify the text.
Once all the spaces are evenly distributed, the program writes to the screen the justified text.
