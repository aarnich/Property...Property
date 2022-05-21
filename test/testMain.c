#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
typedef int (*intfunc)(int arg1, int arg2);

// change return type depending on the function being called
int base()
{
  return 1;
}
int unit(){
  return 1;
}
char* base_str(){
  return "00";
}
char* unit_str(){
  return "00";
}
void range_test(int testlength)
{
  int max, min; // define min and max before running the test
  int errors = 0;
  for (size_t i = 0; i < testlength; i++) {
    if(unit() > max || unit() < min)
    {
      printf("FAILED: base = %d,%d | unit = %d\n",min,max,unit());
      errors += 1;
    }
    else
      printf("PASSED\n");
  } 
}
void str_test(int testlength)
{
  int errors;
  for(size_t i = 0; i < testlength; i++)
  {
    char* unitstr = unit_str();
    char* basestr = base_str();
    if(strcmp(unitstr, basestr))
      printf("PASSED\n");
    else
    {
      printf("FAILED: base = %s | unit = %s\n",base_str(),unit_str());
      errors += 1;
    }
  }
}
int base_propertycost(int property) // DONE
{
  switch (property) {
    case 2:
      return 150;
    case 7:
      return 100;
    default:
      return (property % 7) * 20;
  }
}
int unit_propertycost(int propIndex)
{
    if (propIndex == 2)
        return 150;
    if (propIndex == 7)
        return 100;
    return (propIndex % 7) * 20;
}
int base_mutateindex(int num)
{
  int STATEKEY = 303;
  int OFFSET = -4;
  return STATEKEY + (num - OFFSET) * 10;
}


int exponentiateNum(int base, int power)
{
    int num = 1; // base case
    if (power == 0)
    {
        return num;
    }

    for (int i = power; i > 0; i--)
    {
        num *= base; // base does not change, num keeps being multiplied
    }
    return num;
}

int normalizeNumByIndex(int num, int index)
{ //index starts at 0 and is ordered from right to left
    return (
        (num / exponentiateNum(10, index)) // delimit num by index
        * exponentiateNum(10, index));     // set every value to zero
}

int unit_mutateindex(int value, int index, int STATEKEY)
{
  int OFFSET = -4;
  
    if ((STATEKEY / exponentiateNum(10, index - 1) == 0) || index < 1)
    { // if the given index is outside of the statekey's range
            printf("\ninvalid index");
        return 0; // standard error value
    }

    index -= 1;
    int normalizedNum = normalizeNumByIndex(STATEKEY, index + 1);  // set values inclusive of index to zero
    int insertion = (value - OFFSET) * exponentiateNum(10, index); // insert the mutation by the index's position
    int trailing = STATEKEY % exponentiateNum(10, index);          // add trailing unmutated numbers
    int mutatedStateKey = normalizedNum + insertion + trailing;    // final summation

    return mutatedStateKey;
  
}

int getDigits(int num)
{
  int counter = 0;
  while(num > 0)
  {
    num /= 10; 
    counter++;
  }
  return counter;
}

// ACTIVE TESTING //
 
void int_test(int testlength)
{
  int errors = 0;
  int input_set[] = {0,1,2,3,4,5,6,7,8,9};
  int acc = 0;
  for (size_t i = testlength - 1; i > 0; i--) {
    if(base(input_set[acc]) == unit(input_set[acc]))
      printf("PASSED\n");
    else {
      printf("FAILED: for input: %d | base = %d | unit = %d\n",input_set[acc],base(input_set[acc]),unit(input_set[acc]));
      errors += 1;
    }
    acc += 1;
    acc %= sizeof input_set / sizeof input_set[0];
  } 
  printf("%d cases tested\n",testlength);
  printf("errors: %d",errors);
}
bool unit_playerOwns(unsigned int playerID, int propIndicator){
    if(propIndicator == 5) // if the current property cannot be owned
        return false;
    if((playerID % 2 == propIndicator % 2) && propIndicator != 0) // if the property is even/odd and is not owned by the bank
        return true;

    return false; // false by default
}
bool base_playerOwns()
{
  return false;
}

void ownership_testing(int testlength)
{
  int errors = 0;
  int acc = 0;
  int input_set[] = {1,3,7,9,11,13,15,17};
  for (size_t i = testlength - 1; i > 0; i--) {
    if(base_playerOwns() == unit_playerOwns(2,input_set[acc]))
      printf("PASSED\n");
    else {
      printf("FAILED: for input: %d | base = %d | unit = %d\n",input_set[acc],base_playerOwns(),unit_playerOwns(1,input_set[acc]));
      errors += 1;
    }
    acc += 1;
    acc %= sizeof input_set / sizeof input_set[0];
  } 
  printf("%d cases tested\n",testlength);
  printf("errors: %d",errors);
}
int readStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, int OFFSET)
{
    if (STATEKEY / exponentiateNum(10, index - 1) == 0 || index < 1)
    { // if the given index is outside of the statekey's range

            printf("\ninvalid index");

        return 0; // standard error value
    }

    return (((STATEKEY / exponentiateNum(10, index - 1)) % 10) + OFFSET);
}
int generateStatekey(int statekey, int i)
{
  statekey = unit_mutateindex(readStatekeyAtIndex(statekey,i%10,-4)+1,i%10,statekey);
  return statekey;
}
void generateDataset(int* data[], int length)
{
  int statekey = 444545444;
  int intSet[length];
  for (size_t i = 0; i < length; i++) {
   intSet[i] = generateStatekey(statekey,i);
  }
  *data = intSet; 
}
void digit_testing(int length)
{
  int basedigits = 9; 
  int acc = 0;
  int errors = 0;
  int input_set[length];
  input_set[0] = 444545444;
  for (size_t j = 1; j <= length; j++) {
    if(j % 30 == 0)
    {
      input_set[j] = 400959004;
    }
    if(j % 20 == 0)
    {
      input_set[j] = 999454999;
      continue;
    } 
    if(j % 10 == 0)
    {
      input_set[j] = 444545444;
      continue;
    }
    input_set[j] = generateStatekey(input_set[j-1],j);
    if(getDigits(input_set[j]) > basedigits)
        input_set[j] /= 10;
  }
  for (size_t i = length; i > 0; i--) {
    if(basedigits == getDigits(input_set[acc]))
      printf("PASSED: %d || %d\n",getDigits(input_set[acc]),input_set[acc]);
    else {
      printf("FAILED: for input: %d | base = %d | unit = %d\n",input_set[acc],basedigits,getDigits(input_set[acc]));
      errors += 1;
    }
    acc += 1;
  } 
  printf("%d cases tested\n",length);
  printf("errors: %d",errors);
}
// void intTest(intfunc foo, intfunc base)
// {
//   
// }
int main ()
{
  ownership_testing(100000);
}
