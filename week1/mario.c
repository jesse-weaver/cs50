#include <stdio.h>
#include <cs50.h>

int main (void) 
{
    // set up variables
    string block = "#";
    int height;

    // get user input    
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
        
    printf("The entered height is %i\n", height);
    
    // loop over each row and input proper amount of bricks
    for (int row = 1; row <= height; row++) {
        int numSpaces = height - row;
        int numBricks = height - numSpaces;
        int endBricks = numBricks;

        // spaces first
        while (numSpaces > 0) {
            printf(" ");
            numSpaces--;
        }

        // then bricks
        while (numBricks > 0) {
            printf("%s", block);
            numBricks--;
        }
        //
        // then 2 spaces before 2nd side of pyramid
        printf("  ");

        // the 2nd side of bricks
        while (endBricks > 0) {
            printf("%s", block);
            endBricks--;
        }
        printf("\n");
    }
}
