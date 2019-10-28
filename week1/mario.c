#include <stdio.h>
#include <cs50.h>

int main (void) 
{
    string block = "#";
    int height;
    
    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
        
    printf("The entered height is %i\n", height);
    
    for (int row = 1; row <= height; row++) {
        int numSpaces = height - row;
        int numBricks = height - numSpaces;
        int endBricks = numBricks;
        while (numSpaces > 0) {
            printf(" ");
            numSpaces--;
        }
        while (numBricks > 0) {
            printf("%s", block);
            numBricks--;
        }
        printf("  ");
        while (endBricks > 0) {
            printf("%s", block);
            endBricks--;
        }
        printf("\n");
    }
}
