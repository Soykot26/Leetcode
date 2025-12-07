#include<stdio.h>
int main(){
    
    FILE *fp = NULL;
    char name[25];
    int age;
    printf("Enter your name and age:\n");
    scanf("%s %d", name, &age);
    //fprintf(file_pointer, "formate specifer", list of variables);


   fp = fopen("PF.txt", "w");
   if(fp == NULL){
       printf("File not found");
   }
   else{
    fprintf(fp, "%s\t%d", name, age);
    printf("Data written to file successfully\n");
    fclose(fp);

   }
    return 0;
}