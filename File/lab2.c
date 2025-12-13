#include<stdio.h>
int main()
{

FILE *fp = fopen("omi.txt", "r");
if(fp == NULL){
    perror("Error opening file\n");
}
else{
int ch_code = '\0';
while((ch_code=fgetc(fp)) != EOF){
    printf( "%c",ch_code);

   }
}
       
    return 0;
}   