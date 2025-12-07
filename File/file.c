#include<stdio.h>

int main(){
    
    FILE *file_pointer = NULL;
   file_pointer = fopen("sample.txt", "a");
   if(file_pointer == NULL){
       printf("File not found");
   }
   else{
    printf("File opened successfully\n");
    fclose(file_pointer);
   }
    return 0;
}