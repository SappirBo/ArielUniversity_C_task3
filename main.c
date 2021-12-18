#define end 126
#include <stdio.h>
#include <string.h>
#include "my_string.h"

int main(){
    char word[30]={0};
    char txt[1024]={0};
    scanf("%s",word);
    int index = 0;
    char tmp;
    while(index<1024){
        scanf("%c",&tmp);
        txt[index] = tmp;
        index++;
        if(tmp == end ){
            break;
            }
    }
    index =0;
    index = 0;
    char *p = NULL;
    p = geometric(word,txt);
    printf("Gematria Sequences: %s\n",p);
    p = Atbash(word,txt);
    printf("Atbash Sequences: %s\n",p);
    p = Anagram(word,txt);
    printf("Anagram Sequences: %s",p);
    
    return 0;
}