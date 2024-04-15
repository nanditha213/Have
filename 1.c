
// https://www.youtube.com/watch?v=EO7y1rw9bqo

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(){
    int i, ident=0, num=0, ope=0;
    char s[30];

    printf("Enter Eqquation : ");
    fflush(stdout);
    scanf("%s", s);

    for(i=0; s[i]!='\0'; i++){
        char ch = s[i];

        if(isaplpha(ch)){
            printf("%c is an identifier.\n", ch);
            ident++;
        }
        else if(isdigit(ch)){
            printf("%c is a number.\n", ch);
            num++;

        }
        else{
            printf("%c is an operator.\n", ch);
            ope++;

        }
    }

    printf("Identifiers : %d\n", ident);
    printf("Numbers : %d\n", num);
    printf("Operators : %d\n", ope);
    printf("Total Tokens : %d\n", ident+num+ope);

    return 0;


}
