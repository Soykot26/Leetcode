#include<stdio.h>
int main(){
    //syntax of the remove dunction:
    //int remove(filename);
    //if return value is 
    //.                    0 -> file removed successfully
    //.                    non-zero value -> error occurred while removing the file
    //status = remove("filename/....txt");(if inside another folder that file)
    int status = remove("example.txt");
    if(status == 0){
        puts("File removed successfully.\n");
    }
    else{
        puts("Error removing file.\n");
    }
return 0;
}