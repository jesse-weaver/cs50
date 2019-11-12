#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Main method to convert plain text to ciphertext
int main(int argc, string argv[])
{
    // validate number of args
    string usageMessage = "Usage: ./caesar key\n";
    if (argc != 2)
    {
        printf("%s", usageMessage);
        return 1;
    }

    // validate that the key is digits
    string keyArg = argv[1];
    for (int i = 0, n = strlen(keyArg); i < n; i++)
    {
        if (!isdigit(keyArg[i]))
        {
            printf("%s", usageMessage);
            return 1;
        }
    }

    int key = atoi(keyArg);
    string plaintext = get_string("plaintext: ");

    int length = strlen(plaintext);
    printf("ciphertext: ");
    
    // loop through each character in string and covert it using key
    for (int i = 0; i < length; i++)
    {
        char newCipher;
        if (isalpha(plaintext[i]))
        {
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

