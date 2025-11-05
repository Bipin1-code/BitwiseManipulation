
#include <stdio.h>
#include <unistd.h>

typedef enum {
  DATABLOCK = 0,
  METABLOCK,
} BlockType;

//Bit-fields STRUCT
typedef struct{
  unsigned char blockStatus: 1;
  unsigned char blockType  : 3;
  unsigned char            : 4;
  unsigned char blockNum   : 8;
  unsigned char nextPOffset: 8;
  char fileName[16];
} MetaHeaders;

//REGULAR STRUCT
typedef struct{
  unsigned char blockStatus;
  unsigned char blockType;  
  unsigned char blockNum; 
  unsigned char nextPOffset;
  char fileName[16];
} MetaHeader;

void printBits(unsigned char n){
  for(int i = 8 - 1; i >= 0; i--){
    unsigned char bit = (n >> i) & 1;
    printf("%u", bit);
    if(i % 8 == 0)printf(" ");
  }
  printf("\n");
}


void packMetaHeaders(MetaHeader m){
  //lets do packing
  //always first plan which part of bit go on which position.
  unsigned char packed[19] = {0};
  
  packed[0] = ((m.blockStatus & 0x1) << 7)
    | ((m.blockType & 0x7) << 4)
    | ((m.blockNum >> 4) & 0xf);

  packed[1] = ((m.blockNum & 0xf) << 4)
    | ((m.nextPOffset >> 4) & 0xf);
  
  packed[2] = ((m.nextPOffset & 0xf) << 4);

  memcpy(&packed[3], m.fileName, 16);
  
  //Print Raw memory bits after manual masked
  for(int i = 0; i < (int)sizeof(packed); i++)
    printBits(packed[i]);

  MetaHeader um = {0};
  um.blockStatus = (packed[0] >> 7) & 0x1;
  um.blockType = (packed[0] >> 4) & 0x7;
  um.blockNum = ((packed[0] & 0xf) << 4) | ((packed[1] >> 4) & 0xf);
  um.nextPOffset = ((packed[1] & 0xf) << 4) | ((packed[2] >> 4) & 0xf);
  memcpy(um.fileName, &packed[3], 16);

  printf("blockStatus = %d \nblockType = %d \n\
blockNum = %d\nnextOffSet = %d\nfileName = %s\n",
	 um.blockStatus,
	 um.blockType,
	 um.blockNum,
	 um.nextPOffset,
	 um.fileName);
}

int main(){

  MetaHeaders mH = {
    .blockStatus = 1,
    .blockType = METABLOCK,
    .blockNum = 15,
    .nextPOffset = 15,
    .fileName = "TestFile.bin"
  };

  printf("Raw memory bit:\n");
  unsigned char *bytes = (unsigned char*)&mH;
  for(size_t i = 0; i < sizeof(mH); i++){
    printf("[%2zu] : ", i);
    printf("[%3u] : ", bytes[i]);
    printBits(bytes[i]);
  }

  
  printf("Size of MetaHeaders = %zu\n", sizeof(MetaHeaders));

  const char *fileName = "bitFile.bin";
  
  FILE *f = NULL;
  if(access(fileName, F_OK) != 0){
    f = fopen(fileName, "wb+");
    fprintf(stdout, "File %s created successfully.\n", fileName);
    fwrite(&mH, sizeof(MetaHeaders), 1, f);
  }else{
    f = fopen(fileName, "rb+");
    fprintf(stdout, "File %s open successfully.\n", fileName);
  }
  if(!f){
    perror("Error occur when try to open file.\n");
    return 1;
  }
  MetaHeaders rmh;
  fread(&rmh, sizeof(MetaHeaders), 1, f);
  printf("blockStatus = %u \nblockType = %u \n\
blockNum = %u\nnextOffSet = %u\nfileName = %s\n",
	 rmh.blockStatus,
	 rmh.blockType,
	 rmh.blockNum,
	 rmh.nextPOffset,
	 rmh.fileName);

  //using manual packing
  puts("\nManual way: ");
   MetaHeader m = {
    .blockStatus = 1,
    .blockType = METABLOCK,
    .blockNum = 15,
    .nextPOffset = 15,
    .fileName = "TestFile.bin"
  };
  packMetaHeaders(m);
  
  fclose(f);
  
  return 0;
}

/*
----------OUTPUT----------------
Raw memory bit:
[ 0] : [  3] : 00000011
[ 1] : [ 15] : 00001111
[ 2] : [ 15] : 00001111
[ 3] : [ 84] : 01010100
[ 4] : [101] : 01100101
[ 5] : [115] : 01110011
[ 6] : [116] : 01110100
[ 7] : [ 70] : 01000110
[ 8] : [105] : 01101001
[ 9] : [108] : 01101100
[10] : [101] : 01100101
[11] : [ 46] : 00101110
[12] : [ 98] : 01100010
[13] : [105] : 01101001
[14] : [110] : 01101110
[15] : [  0] : 00000000
[16] : [  0] : 00000000
[17] : [  0] : 00000000
[18] : [  0] : 00000000
Size of MetaHeaders = 19
File bitFile.bin open successfully.
blockStatus = 1
blockType = 1
blockNum = 120
nextOffSet = 224
fileName = TestFile.bin

Manual way:
10010000
11110000
11110000
01010100
01100101
01110011
01110100
01000110
01101001
01101100
01100101
00101110
01100010
01101001
01101110
00000000
00000000
00000000
00000000
blockStatus = 1
blockType = 1
blockNum = 15
nextOffSet = 15
fileName = TestFile.bin

*/
