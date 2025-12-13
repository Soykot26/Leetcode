#include<stdio.h>
/*syntax of temp file function:
FILE *tmpfile();
-> creates a temporary binary file and opens it for update (w+b mode)
*/
int main(){
    char data[]="Hello learner.";
    int length = strlen(data);
    int  counter =-1;
    FILE *temp_fp = tmpfile();
    if(temp_fp != NULL){
        puts("Temporary file created successfully.\n");
        while(++counter < length){
            fputc(data[counter], temp_fp);
        }
        rewind (temp_fp); //to set the file position to the beginning of the file
        while(!feof(temp_fp)) {
            putchar (fgetc(temp_fp));
        }
    }
    else{
        puts("Error creating temporary file.\n");
    }

    return 0;
}