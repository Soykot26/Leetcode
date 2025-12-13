#include<stdio.h>
int main(){
    
    FILE *fp = NULL;
    //char name[25];
    int age;
    char name2[25];
    //fscanf(file_pointer, "format string", list of address of variables);


   fp = fopen("SF.txt", "r");
   if(fp == NULL){
       printf("File not found");
   }
   else{
    //fscanf(fp, "%s %s", name, name2);
    fscanf(fp, "%s/t%d", name2, &age);
    //printf("Name read from file: %s %s", name, name2);
    printf("Name read from file: %s%d", name2, age);
    fclose(fp);
   } 
    return 0;
}   