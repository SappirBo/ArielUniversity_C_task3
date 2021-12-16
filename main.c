#include <stdio.h>
// #include "my_string.h"
#include "myStr.h"

int main(){
    char txt[1024];
    scanf("%1024s",txt);
    printf("you entered:\n%s\n",txt);

    char *p = NULL;
    p = geometric(txt);
    printf("Gematria Sequences: %s\n",p);
    p = Atbash(txt);
    printf("Atbash Sequences: %s\n",p);
    p = Anagram(txt);
    printf("Anagram Sequences: %s\n",p);
    
    return 0;
}