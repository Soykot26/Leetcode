#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct student
{
    int id;
 
    char name[50];

};
int main(){
    struct student s[100];
    int count =0; 
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        printf("File not found");
        return 0;
    }
    else{

       while
        (fscanf(fp, "%d %s\n", &s[count].id, s[count].name) != EOF){
            count++;
    }
    
        fclose(fp);

        if (count == 0){
            printf("No student records found.\n");
            return 0;
        }
        else{
        srand(time(NULL));
        int random_index = rand() % count;
        printf("Randomly selected student:\n");
        printf("ID: %d\n", s[random_index].id);
        printf("Name: %s\n", s[random_index].name);
        
    }

}
   return 0;
}

