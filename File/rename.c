#include<stdio.h>
/*
syntax of rename function:
int rename(old_filename, new_filename);
-> Return 0 if succesful
-> Return non zero value if an error occurs while renaming
*/

int main(){
    if(rename("saikot.txt", "example.txt") == 0){
        printf("File renamed successfully.\n");
    }
    else{
        printf("Error renaming file.\n");
    }


   return 0; 
}