#include <stdio.h>
#include <cs50.h>
#include <math.h>

int getFirstNDigits(long number, int numberOfDigits);
int getNumberOfDigits(long number);
bool checkVisa(long ccNumber);
bool checkMasterCard(long ccNumber);
bool checkAmex(long ccNumber);
bool isValidCC(long ccNumber);

int main(void)
{
  long ccNumber;
  do
  {
    ccNumber = get_long("Number: ");
  } while (ccNumber < 0);

  bool isVisa = checkVisa(ccNumber);
  bool isAmex = checkAmex(ccNumber);
  bool isMasterCard = checkMasterCard(ccNumber);

  if (!isVisa && !isAmex && !isMasterCard)
  {
    printf("INVALID\n");
    return 0;
  }

  if (!isValidCC(ccNumber))
  {
    printf("INVALID\n");
    return 0;
  }

  if (isVisa)
  {
    printf("VISA\n");
    return 0;
  }

  if (isMasterCard)
  {
    printf("MASTERCARD\n");
    return 0;
  }

  if (isAmex)
  {
    printf("AMEX\n");
    return 0;
  }
}

// get the first n digits for a given CC
int getFirstNDigits(long number, int numberOfDigits)
{
  return number / pow(10, numberOfDigits);
}

// determine the number of digits of a long number
int getNumberOfDigits(long number)
{
  return log10(number) + 1;
}

// identify if the card is a VISA
bool checkVisa(long ccNumber)
{
  int numOfDigits = getNumberOfDigits(ccNumber);
  if (numOfDigits != 13 && numOfDigits != 16)
  {
    return false;
  }
  return getFirstNDigits(ccNumber, numOfDigits - 1) == 4;
}

// identify if the card is a Amex
bool checkAmex(long ccNumber)
{
  int numOfDigits = getNumberOfDigits(ccNumber);
  if (numOfDigits != 15)
  {
    return false;
  }
  int firstDigits = getFirstNDigits(ccNumber, numOfDigits - 2);
  return firstDigits == 34 || firstDigits == 37;
}

// identify if the card is a MasterCard
bool checkMasterCard(long ccNumber)
{
  int numOfDigits = getNumberOfDigits(ccNumber);
  if (numOfDigits != 16)
  {
    return false;
  }
  int firstDigits = getFirstNDigits(ccNumber, numOfDigits - 2);
  return firstDigits >= 51 && firstDigits <= 55;
}

// use Luhn's algorithm to determine if CC is a valid number
bool isValidCC(long ccNumber)
{
  int digitsMultipliedBy2Sum = 0;
  int otherDigitsSum = 0;
  int numOfDigits = getNumberOfDigits(ccNumber);
  int digits[numOfDigits];
  long remainingDigits = ccNumber;

  int count = 0;
  while (remainingDigits > 0)
  {
    digits[count] = remainingDigits % 10;
    if (count % 2 > 0)
    {
      // multiple every other number by 2 starting with 2nd to last
      digits[count] *= 2;
    }
    remainingDigits = remainingDigits / 10;
    count++;
  }

  for (int i = 0; i < numOfDigits; i++)
  {
    if (i % 2 == 0)
    {
      otherDigitsSum += digits[i];
    }
    else
    {
      // if a given int is > 10 then split up into digits
      if (digits[i] > 9)
      {
        digitsMultipliedBy2Sum += round(digits[i] / 10);
        digitsMultipliedBy2Sum += digits[i] % 10;
      }
      else
      {
        digitsMultipliedBy2Sum += digits[i];
      }
    }
  }

  // if the sum of the digits is divisible by 10 card is valid
  if ((digitsMultipliedBy2Sum + otherDigitsSum) % 10 > 0)
  {
    return false;
  }
  return true;
}
