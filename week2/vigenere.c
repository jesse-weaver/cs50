#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

// Main method to convert plain text to ciphertext
int main(int argc, string argv[])
{
    // validate number of args
    string usageMessage = "Usage: ./vigenere keyword\n";
    if (argc != 2)
    {
        printf("%s", usageMessage);
        return 1;
    }

    // validate that the key is digits
    string keyArg = argv[1];
    for (int i = 0, n = strlen(keyArg); i < n; i++)
    {
        if (!isalpha(keyArg[i]))
        {
            printf("%s", usageMessage);
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");

    // get the length of the strings
    int length = strlen(plaintext);
    int keyLength = strlen(keyArg);
    int keyCounter = 0;
    printf("ciphertext: ");
    
    // loop through each character in string and covert it using key
    for (int i = 0; i < length; i++)
    {
        char newCipher;
        if (isalpha(plaintext[i]))
        {
            // calculate the num of characters to shift
            int key = shift(keyArg[keyCounter]);
            keyCounter += 1;

            // if we've been through each char in key, start back at the beginning
            if (keyCounter > keyLength - 1)
            {
                keyCounter = 0;
            }            
            int asciiNum = plaintext[i] + key;
            newCipher = (plaintext[i] + key);
            if (islower(plaintext[i]))
            {
                newCipher = (plaintext[i] - 97 + key) % 26 + 97;
            }
            if (isupper(plaintext[i]))
            {
                newCipher = (plaintext[i] - 65 + key) % 26 + 65;
            }
        }
        else
        {
            newCipher = plaintext[i];
        }
        printf("%c", newCipher);
    }
    printf("\n");
}

// function to determine how many characters to shift based on a char
int shift(char c)
{
    if isupper(c)
    {
        return c - 65;
    }
    else
    {
        return c - 97;
    }
}
