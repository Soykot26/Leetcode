#include<stdio.h>

int main()
{

   FILE *fp = fopen("str.txt", "w");
   char input_str[100];
   if(fp==NULL){
       printf("Error opening file\n");
    }   else{
         printf("Enter a string:\n ");
       gets(input_str);
       fputs(input_str,fp);
       printf("String written to file successfully.\n");
    fclose(fp);
    }


    return 0;
}
