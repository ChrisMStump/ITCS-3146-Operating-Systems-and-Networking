In this program the wall follower algorithm is used to solve the field. The “person” follows the wall on his right until eventually the maze is solved. If he ends up at the beginning then there is no solution. There are five steps in determining which way to go.

1.	Can I go right?
2.	If so, go right. (Ask question one again).
3.	If you can’t go right, then ask can I go straight or left?
4.	If possible go straight first, otherwise go left.
5.	Otherwise go backwards.

This algorithm will ensure that we will traverse completely through the maze until it is either solved or not solved.

The field is represented as an array. This allows for coordinates to be compared easily. It is also easy to change values within the array. Everything inside the field array is of type char, so to find out whether something equals another we must say: Does array[][] == ‘  ‘? 

As far as it has been tested, all mazes of different sizes work and it is able to state whether or not it is solved. 
