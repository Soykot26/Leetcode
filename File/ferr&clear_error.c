#include<stdio.h>

    // int ferror(FILE *fp);if return 0 then the last operation was successful
    //if return non zero value then an error occurred during the last operation
    //(problem ase aitay buji na ken jani)
    //void clearerr(FILE *fp);
int main(){
    int status;
    char data[20]="hello world";
    FILE *fp = fopen("example.txt", "w");
    if (fp != NULL){
        fprintf(fp,"%s", data);
        status =ferror(fp);
        printf("%d\n", status);
        if(status==0){
            puts("Last operation was successful.\n");
        }
        else{
            puts("Error occurred during the last operation.\n");
        }

    }
    else{

        puts("File opening failed.\n");
    }
    
return 0;
}