#include<stdio.h>
int main()
{

FILE *fp = fopen("input.txt", "r");
if(fp == NULL){
    perror("Error opening file\n");
}
else{

int ch_code = '\0';
while((ch_code=fgetc(fp)) != EOF){
    printf( " %c", ch_code);//for char with asci val just add %d:.....,ch_code

}
//1st word
//ch_code=fgetc(fp); //to move the pointer to next character
//printf( "%d : %c\n", ch_code, ch_code );
//2nd word
//ch_code=fgetc(fp); //to move the pointer to next character
//printf( "%d : %c\n", ch_code, ch_code );
}
    return 0;
}