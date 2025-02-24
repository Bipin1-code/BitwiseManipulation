
//This program give you the basic of bitwise operation overview

/*
  Read these before delve into code:
   1. Modern computers uses two's complement
      where MSB(Most significant bit) is sign bit where 0 means '+' and 1 means '-'
   2. Make yourself with binary reperesentation and it's types.
   3. "<<" this means left-shift:
      Left-shift used to fast multiplication by 2 pow n.
      For instance: num = 0000 0101; //in decimal 5
                    num = num << n;  (5 * (2 pow n))//n is should be position integer
                    suppose n is 2.
                    then
                    num = 0001 0100; (in decimal 20 )
                    //As you can see bit move to left side 2 time and 2 0's bit add at the end
                    
   4. ">>" this means right-shift:
       Right-shift used to fast division by 2 pow n.
       For instance: num = 0000 1000; //in decimal 8
                     num = num >> n; ( 8 / (2 pow 2))
                     let n = 2
                     then
                     num = 0000 0010; //in decimal 2
                     //As you can see bit move to right side 2 time and Last bit discard in each step
 */

#include <stdio.h>
#include <stdint.h>

//This function is used to print the number in binary 32-bit format
//Without this 32-bit format print in decimal form
void print32Bit(uint32_t number){
  for(size_t i = 32; i-- > 0;){
    printf("%d", (number >> i) & 1);
  }
  printf("\n");
}

//This is for to set bit, when I say set bit: it meant with turning 0 to 1
void setBit(uint32_t number, size_t position){
  print32Bit(number);
  //Why maskbit? because we don't want to affect the other bit
  uint32_t maskBit = (1 << position); 
  number |= maskBit; //Note: OR '|' is used to meger two binary numbers
  print32Bit(number);
}

//This is for to clear bit, when I say clear bit: it meant with turning 1 to 0
void clearBit(uint32_t number, size_t position){
  print32Bit(number);
  uint32_t maskBit = (1 << position);
  number &= (~maskBit); //Note: AND '&' is used to clearing, subtract and extract the bit
  print32Bit(number);
}

//This function is used to toggle the bit, hence as name.
void toggleBit(uint32_t number, size_t position){
  print32Bit(number);
  uint32_t maskBit = (1 << position);
  print32Bit(maskBit);
  number ^= maskBit; //Note: XOR '^' is used to subtraction, toggle bit
  print32Bit(number);
}

void checkBitIsSet(uint32_t number, size_t position){
  print32Bit(number);
  uint32_t maskBit = 1 << position;
  if(number & maskBit){
    printf("k-th bit %zu is already set.\n", position);
  }else{
    printf("k-th bit %zu is not set.\n", position);
  }
}

void count1sInBitRepresentation(uint32_t num){
  size_t count = 0;
  while(num){
    num = num & (num - 1); //Note: num - 1 is arithmetic operation
    /* How above line working?
       first: num = 8  //0000 1000
       second: num - 1 = 7 //0000 0111 (num - 1 flips the rightmost 1 bit to 0 and turns all bits after it to 1)
       third: '&' operation //if both bits are 1 then result is 1, else 0.
       but in this example it doesn't have so count++
       num becomes 0 and loops break
     */
    count++;
  }
  printf("Number of 1's present in num is %zu.\n", count);
}

void checkIfNumIsPowOf2(uint32_t number){
  if(number > 0 && (number & (number - 1)) == 0){
    printf("Number %u is the power of 2.\n", number);
  }
  else{
    printf("Number %u is not the power of 2.\n", number);
  }
}

//Swap by using bitwise operation
void swap2Number(uint32_t *n1, uint32_t *n2){
  *n1 ^= *n2; 
  *n2 ^= *n1;
  *n1 ^= *n2;
}

void reverseBit(uint32_t n){
  print32Bit(n);
  uint32_t revNum = 0;
  for(size_t i = 0; i < 32; i++){
    revNum = (revNum << 1) | (n & 1);
    /*
      n & 1 extract Last bit from n
      revNum move to left making space for add the bit which we extracted
      OR '|' merge the extracted bit to the revNum
     */
    n >>=1; //discard the last bit which we extract and shift to right with 1 step
  }
  printf("revNum is %u.\n", revNum);
  print32Bit(revNum);
}

int main(){
  uint32_t num = 43261596;
  uint32_t num1 = 20;
  size_t kBit = 2;
  setBit(num, kBit);
  clearBit(num, kBit);
  toggleBit(num, kBit);
  checkBitIsSet(num, kBit);
  count1sInBitRepresentation(num);
  checkIfNumIsPowOf2(num);
  swap2Number(&num, &num1);
  printf("num is %u and num1 is %u.\n", num, num1);
  reverseBit(num);
  return 0;
}
