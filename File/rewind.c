#include<stdio.h>
int main(){
    FILE *fp = fopen("example.txt", "r");
    while(!feof(fp)){
        putchar(fgetc(fp));

    }
    printf("\n");
    rewind(fp);
    while(!feof(fp)){
        putchar(fgetc(fp));
    }
    return 0;
}
//(aita mainly use kora hoise onno file a  kisu ase naki oita porar laigga like jodi 1st while
//loop diya akbar pora jay and jkhane sesh hoy oi jaga thaikka abr new koira file read ar laiggga
// rewind use kora hoise)