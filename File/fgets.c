#include<stdio.h>
int main(){
    
    FILE *fp = NULL;
    char data[100];
    //fgets(variable to store, size, file_pointer);
   fp = fopen("GS.txt", "r");
   if(fp == NULL){
       printf("File not found");
   }
   else{
    while (!feof(fp))
    {
        fgets(data, sizeof(data), fp);
        printf("the char readed were: %s", data);
        /* code */
    }
    


    fclose(fp);
   }
    return 0;
}