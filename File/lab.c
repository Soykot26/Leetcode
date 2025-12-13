#include<stdio.h>
int main(){
    FILE *fp=fopen("rat.txt","r");
    if(fp==NULL){
        printf("Error opening file\n"); 
}
char key;
while ((key=fgetc (fp))!=EOF){
    printf("%c",key);
}
fclose(fp);
return 0;
}
