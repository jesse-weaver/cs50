#include <stdio.h>
#include <cs50.h>
#include <math.h>

int getNumberOfCoinsThatFit(int change, int coinValue);
int getCoinRemainder(int change, int coinValue);

int main(void)
{
    // declare constants
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // get the change owed
    int numberOfCoins, remainingChange, quarters, dimes, nickels, pennies;
    float changeOwed = get_float("Change owed: ");

    // convert to cents to avoid float precision issues
    int cents = round(changeOwed * 100);

    // handle quarters
    numberOfCoins = getNumberOfCoinsThatFit(cents, quarter);
    remainingChange = getCoinRemainder(cents, quarter);
    printf("number of quarters: %d, remaining change: %d\n", numberOfCoins, remainingChange);

    // handle dimes
    dimes = getNumberOfCoinsThatFit(remainingChange, dime);
    numberOfCoins += dimes;
    remainingChange = getCoinRemainder(remainingChange, dime);
    printf("number of dimes: %d, remaining change: %d\n", dimes, remainingChange); 

    // handle nickels
    nickels = getNumberOfCoinsThatFit(remainingChange, nickel);
    numberOfCoins += nickels;
    remainingChange = getCoinRemainder(remainingChange, nickel);
    printf("number of nickels: %d, remaining change: %d\n", nickels, remainingChange);

    // handle pennies
    pennies = getNumberOfCoinsThatFit(remainingChange, penny);
    numberOfCoins += pennies;
    remainingChange = getCoinRemainder(remainingChange, penny);
    printf("number of pennies: %d, remaining change: %d\n", pennies, remainingChange);

    // minimum number of coins
    printf("%d\n", numberOfCoins);
}

int getNumberOfCoinsThatFit(int change, int coinValue)
{
    return round(change / coinValue);   
}

int getCoinRemainder(int change, int coinValue)
{
    return change % coinValue;
}
