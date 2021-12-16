#include <stdio.h>
#include <string.h>
#include "myStr.h"


/**
 * @brief THis is Helper for main Function.
 * @param txt  - the input String.
 * @return int  - the geometric value of the string (starting with a=A=1).
 */
int geometricValue(char txt[],int start, int end){
    int value = 0;
    int length = strlen(txt);

    for(int i=start; i<=end && txt[i] != '~' && txt[i] != '\0' && txt[i] != '\n' ; i++){
        if(txt[i]>=97 && txt[i]<= 122){
            value += (txt[i]-96);   
        }
        else if(txt[i]>=65 && txt[i]<= 90){
            value += (txt[i]-64); 
        }
        else{
            value += 0;
        }
    } 
    return value;   
}

char* geometric(char txt[]){
    int i=0;
    while (txt[i] != ' ' && txt[i] != '\n' && txt[i] != '\t'){
        i++;
    }
    int gv =geometricValue(txt,0,i); // gv = Geometric Value;
    i++;
    char all[1024];
    int ptr = 0;
    int counter;
    int sum;
    for(i; i<strlen(txt) && txt[i] != '~'; i++){
        sum = 0;
        counter = i-1;
        while(sum < gv && counter < strlen(txt)){
            counter++;
            if(((txt[i]>=65 && txt[i]<= 90) || (txt[i]>=97 && txt[i]<= 122)) && 
                            ((txt[counter]>=65 && txt[counter]<= 90) || (txt[counter]>=97 && txt[counter]<= 122))){
                sum = geometricValue(txt,i,counter);
            }
            if(sum >= gv){break;}
        }
        if(sum == gv){
            if(ptr>0){
               all[ptr] = '~';
            ptr++;
            }
            for(int k=i; k<=counter; k++){
                all[ptr] = txt[k];
                ptr++;
            }
            all[ptr] = '\0';
        }
    }
    char *ans;
    ans = all;
    return ans;
}

/**
 * @brief Helper function for reverse the char (a-z,b-y).
 * @param c - given char.
 * @return char reversed.
 */
char oppo(char c){
    char ans = '\0';
    if(c>=65 && c<=90){
        int x = c - 64;
        int y=0;
        for(int i=1; i<27;i++){
            if((x+y)==27){break;}
            else{
                y++;
            }
        }
        ans = y+64;
    }
    else if(c>=97 && c<=122){
        int x = c - 96;
        int y=0;
        for(int i=1; i<27;i++){
            if((x+y)==27){break;}
            else{
                y++;
            }
        }
        ans = y+96;
    }
    return ans;
}

int equals(char a[],char b[]){
    int flag1 = 1,flag2 =1, ptr =0;
    for(int i=0; i<strlen(b); i++){
        if((b[i]>=65 && b[i]<=90) || (b[i]>=97 && b[i] <=122)){
            if(a[ptr] != b[i]){
                flag1 = 0;
                break;
            }
            else{ptr++;}
        }
    }
    ptr = strlen(a)-1;
    for(int i=0; i<strlen(b); i++){
        if((b[i]>=65 && b[i]<=90) || (b[i]>=97 && b[i] <=122)){
            if(a[ptr] != b[i]){
                flag2 = 0;
                break;
            }
            else{ptr--;}
        }
    }
    
    if(flag1 == 0 && flag2 == 0){return 0;}
    else{
        return 1;
    }
}

char* Atbash(char txt[]){
    int i=0, ptr =0, flag;
    while (txt[i] != ' ' && txt[i] != '\n' && txt[i] != '\t'){
        i++;
    }
    char word[i-1];
    i++;
    for(int k=0; k<i; k++){
        word[k] = txt[k];
    }
    for(int j=0; j<strlen(word); j++){
        word[j] = oppo(word[j]);
    }
    char all[1024];
    char tmp[strlen(word)];
    int counter = 0,index = 0,letters;
    for(i; i<strlen(txt)-strlen(word); i++){
        counter = i-1;
        letters = 0;
        if((txt[i] > 64 && txt[i]<91) || (txt[i] > 96 && txt[i]<123)){
            while(letters <= strlen(word)){
                counter++;
                if(((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123))  ){//&& txt[counter] != '\0'
                    letters++;
                }
            }
            ptr = 0;
            for(int k=0;k < counter-i;k++){
                if((txt[i+k] > 64 && txt[i+k]<91) || (txt[i+k] > 96 && txt[i+k]<123)){
                    tmp[ptr] = txt[i+k];
                    ptr++;
                }
            }
            tmp[ptr] = '\0';
        }
        // Flag Check - if flag=0 -> it is not atbash.
        flag = equals(word,tmp);
        if(flag == 1){
            if(index > 0){
                all[index] = '~';
                index++;
            }
            for(int k=0; k < counter-i; k++){
                all[index] = txt[i+k];
                index++;
            }
            all[index] = '\0';
        }
    }
    all[index-1] = '\0';
    char *p;
    p = all;
    return p;
    
}

int containe(char txt[],char c){
    int flag = 0;
    for(int i=0;i<strlen(txt);i++){
        if(txt[i]==c){flag = 1;}
        if(flag == 1){break;}
    }
    return flag;
}

int sameSame(char a[],char b[]){
    int flag =0;
    for(int i=0; i<strlen(a); i++){
        flag = containe(b,a[i]);
        if(flag == 0){break;}
    }
    return flag;
}

char* Anagram(char txt[]){
    int i=0,index=0;
    while (txt[i] != ' ' && txt[i] != '\n' && txt[i] != '\t'){
        i++;
    }
    char word[i-1];
    i++;
    for(int k=0; k<i-1; k++){
        word[k] = txt[k];
    }
    char all[1024];
    char tmp[strlen(word)];
    int counter, letters,ptr,flag;
    for(i=strlen(word)+1; i<strlen(txt)-strlen(word); i++){
        counter = i;
        letters = 0;
        if((txt[i] > 64 && txt[i]<91) || (txt[i] > 96 && txt[i]<123) || txt[i] == ' '){
            while(letters <= strlen(word) && ((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123) || txt[counter] == ' ')){
                if(((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123))){
                    letters++;
                }
                counter++;
            }
            ptr = 0;
            for(int k=0;k < counter-i;k++){
                if((txt[i+k] > 64 && txt[i+k]<91) || (txt[i+k] > 96 && txt[i+k]<123)){
                    tmp[ptr] = txt[i+k];
                    ptr++;
                }
            }
            tmp[ptr] = '\0';
        }
        flag = sameSame(word,tmp);
        if(flag == 1){
            if(index > 0){
                all[index] = '~';
                index++;
            }
            for(int k=0; k < counter-i; k++){
                all[index] = txt[i+k];
                index++;
            }
        }
    }
    all[index] = '\0';
    char *p;
    p = all;
    return p;
}

//
// int main(){
//     char txt[] = "bee‬‬/nI’m‬‬ ‫‪bringing‬‬ ‫‪home‬‬ ‫‪my‬‬ ‫‪baby‬‬ ‫‪bumble‬‬ ‫‪bee‬‬‪\nWon’t‬‬ ‫‪my‬‬ ‫‪Mommy‬‬ ‫‪be‬‬ ‫‪so‬‬ ‫‪proud‬‬ ‫‪of‬‬ ‫‪me‬‬‪\nI’m‬‬ ‫‪bringing‬‬ ‫‪home‬‬ ‫‪my‬‬ ‫‪baby‬‬ ‫‪bumble‬‬ ‫‪bee‬‬ ‫–‬ \nOUCH‬‬ ‫‪It‬‬ ‫‪stung‬‬ ‫~!!‪me‬‬";
//     char *ptr;
//     ptr = txt;
//     int counter = 0;
//      char *p ; 
//     p = geometric(txt);
//     printf("Gematria Sequences: %s\n",p);
//     p = Atbash(txt);
//     printf("Atbash Sequences: %s\n",p);
//     p = Anagram(txt);
//     printf("Anagram Sequences: %s\n",p);
//     return 0;
// }
