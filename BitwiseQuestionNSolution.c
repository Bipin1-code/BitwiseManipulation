
// Detect if two numbers have opposite signs without using if-else or multiplication/division.

#include <stdio.h>

void print32Bit(int n){
  for(size_t i = 32; i-- > 0;){
    printf("%d", (n >> i) & 1);
  }
  printf("\n");
}

void detectNumsHaveOppositeSigns(int n1, int n2){
  print32Bit(n1);
  print32Bit(n2);
  int maskBit = (1 << 31);
  print32Bit(maskBit);
  int signN1 = n1 & maskBit;
  int signN2 = n2 & maskBit;
  print32Bit(signN1);
  print32Bit(signN2);

  printf("%s.\n",
         (signN1 != signN2) ? "Yes!! Numbers signs are opposite" : "No!! Numbers signs are not opposite");
}

unsigned int PowerOf2GreaterThanNum(unsigned int n){
  /* int power = 1; */
  /* while(power <= n){ */
  /*   power <<= 1; */
  /* } */
  /* return power; */

  //This is faster way
  if(n && !(n & (n - 1))) return n << 1;
  n--; //for to handle the case when n is itself a power of 2
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}
int main(){
  int num1 = -32, num2 = -4;
  detectNumsHaveOppositeSigns(num1, num2);
  int powerOf2GTNum = PowerOf2GreaterThanNum(num1);
  printf("Next power of 2 greater than the %d is %d.\n", num1, powerOf2GTNum);
  return 0;
}
