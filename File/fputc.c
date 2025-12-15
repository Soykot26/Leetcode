#include<stdio.h>
int main(){
    char data[]="Hello World";
    FILE *fp = fopen("output.txt", "w");
    if(fp == NULL){
        printf("Error opening file\n");
}
else{


int index=0;
char ch='\0';
while(data[index] != '\0'){
   ch= fputc(data[index], fp);//print("%c",fputc('A',fp))‹//fputc('B',fp);//fputc('C',fp);
fputc('C',fp);
   printf("%c", ch);
    index++;
}
}
return 0;
}