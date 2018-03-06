# Path Planning Project Using C

This is one of the projects which I did in COMP20005 Engineering Computation Semester 1, 2016, at the University of Melbourne. This project was so interesting that I have always remembered it.

A simple path planning algorithm was implemented by using C programming language. For more details regarding the requirements of the project, please see the included PDF file.

Test cases have been included as text files for demonstration purposes.

To compile the project:

```
gcc -Wall -o myass2 myass2.c
```

To run the project with test case 0:

```
myass2 < test1.txt
```

## Example Input

```
#####.###.#####
#.....#.#.....#
#.###.#.#####.#
#.#...#.......#
#...#########.#
###.#.........#
#.#.#.#########
#.....#.......#
#.#####.#####.#
#.....#.......#
#####.#########
```
The content of `test1.txt` is shown above. There are two types of blocks in the text file:
* `#` indicates a wall cell which cannot be passed through.
* `.` indicates a passable cell which can be traversed through.

## Example Output
There are various output stages in the implementation. I will be mainly discussing the Stage 4 output as all the previous stages were in-between milestones which eventually lead up to Stage 4.

Running the program with test1.txt as the input file will yield the following Stage 4 output.

```
Stage 4
=======
maze solution
##########00######  ##########
##        ..##  ##          ##
##  ######02##  ##########  ##
##  ##..04..##              ##
##    06##################  ##
######..##                  ##
##  ##08##  ##################
##..10..    ##--------------##
##12##########--##########--##
##..14..16..##--------------##
##########18##################
```

If there is a solution to the given maze text file, the output will indicate whether there is a solution. In this case, there is a solution and the program outlines the shortest path to the exit at the bottom, while counting and displaying the number of steps required to reach the exit.

From this output, we can see the shortest path to complete the maze and it requires 18 steps to go from start to finish.

## Additional Notes
Feel free to make some interesting input files and see how well this program holds. 


