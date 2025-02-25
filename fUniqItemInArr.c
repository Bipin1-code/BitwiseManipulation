/*
  Find the unique element from an array and two unique element from an array:
  Given an array where every element appears twice except one, find the unique element using XOR.
  Given an array where every element appears twice except two numbers, find those two numbers.
*/

#include <stdio.h>

void findUnique(int number[], size_t s){
  printf("Array: ");
  for(size_t i = 0; i < s; i++){
    printf("%d ", number[i]);
  }
  printf("\n");
  int unique = 0;
  for(size_t i = 0; i < s; i++){
    unique ^= number[i];
  }
  printf("Unique element is %d.\n", unique);
}

void findtwoUnique(int number[], size_t s){
  printf("Array: ");
  for(size_t i = 0; i < s; i++){
    printf("%d ", number[i]);
  }
  printf("\n");
  int xorAll = 0;
  //Step1: XOR all numbers -> gives XOR of two unique numbers
  for(size_t i = 0; i < s; i++){
    xorAll ^= number[i];
  }
  //Step2: Find the rightmost set bit (where the two numbers differ)
  int rightmostSetBit = xorAll & -xorAll; //Gets the lowest set bit
  printf("RightMostSetBit is %d.\n", rightmostSetBit);
  int num1 = 0, num2 = 0;
  
  //Step3: Divide numbers into two groups and XOR separately
  for(size_t i = 0; i < s; i++){
    if(number[i] & rightmostSetBit){
      num1 ^= number[i]; //Group 1 (bit is 1)
    }else{
      num2 ^= number[i]; //Group 2 (bit is 0)
    }
  }
  printf("The two unique numbers are: %d and %d.\n", num1, num2);
}

int main(){
  int n[] = {5, 2, 4, 2, 5, 1};
  int arr[] = {5, 4, 3, 5, 4};
  size_t size = sizeof(n)/sizeof(n[0]);
  size_t sizeArr = sizeof(arr)/sizeof(arr[0]);
  findtwoUnique(n, size); //for to find the two unique elements present inside the array
  findUnique(arr, sizeArr);//for to find the single unique item present inside the array
  return 0;
}
