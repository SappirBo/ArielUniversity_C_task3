#include <stdio.h>
#include <string.h>
#include "my_string.h"


/**
 * @brief THis is Helper for main Function.
 * @param txt  - the input String.
 * @return int  - the geometric value of the string (starting with a=A=1).
 */
int geometricValue(char txt[],int start, int end){
    int value = 0;
    // int length = strlen(txt);

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

char* geometric(char word[], char txt[]){
    // int i=0;
    // while (txt[i] != ' ' && txt[i] != '\n' && txt[i] != '\t' && ( txt[i] != 92 && txt[i] != 110)&& txt[i] != 13){
    //     i++;
    // }
    int gv =geometricValue(word,0,strlen(word)); // gv = Geometric Value;
    int i=0;
    char all[1024];
    int ptr = 0;
    int counter;
    int sum;
    for(; i<strlen(txt) && txt[i] != '~'; i++){
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

char* Atbash(char word[],char txt[]){
    int i=0, ptr =0, flag;
    int size = strlen(word);
    char wordRev[strlen(word)];
    for(int j=0; j<strlen(word); j++){
        wordRev[j] = oppo(word[j]);
    }
    char all[1024]= {0};
    char tmp[size];
    int counter = 0,index = 0,letters;
    for(; i<strlen(txt); i++){
        counter = i;
        letters = 0;
        if((txt[i] > 64 && txt[i]<91) || (txt[i] > 96 && txt[i]<123)){
            while(letters != strlen(wordRev) && counter<strlen(txt)){
                if(((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123))  ){ 
                    letters++;
                }
                counter++;
            }
            ptr = 0;
            if(letters == strlen(wordRev)){
                for(int k=0;k < counter-i;k++){
                    if((txt[i+k] > 64 && txt[i+k]<91) || (txt[i+k] > 96 && txt[i+k]<123)){
                        tmp[ptr] = txt[i+k];
                        ptr++;
                    }
                }
                tmp[ptr] = '\0';
            }
        }
        if((tmp[0] > 64 && tmp[0]<91) || (tmp[0] > 96 && tmp[0]<123)){
            // Flag Check - if flag=0 -> it is not atbash.
            flag = equals(wordRev,tmp);
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
        
    }
    // all[index-1] = '\0';
    char *p;
    p = all;
    return p;
    
}

int containe(char txt[],char c, int times){
    int flag = 0;
    int i=0;
    for(;i<strlen(txt);i++){
        if(txt[i]==c){flag += 1;}
    }
    if(flag == times){return 1;}
    else{
        return -1;
    }
}

int sameLetters(char word[],char tmp[]){
    int size = strlen(tmp); 
    int index = 1,count;
    // printf("for word[%s] and tmp[%s] ,",word,tmp);
    int sum[size];
    for(int i=0; i<size; i++){
        count =0;
        for(int j=0; j<size; j++){
            if(word[i] == word[j]){
                count++;
            }
        }
        sum[i]=count;
    }
    
    for(int i=0; i<size; i++){
        index = containe(tmp,word[i],sum[i]);
        // printf("tmp containe %c = %d\n",word[i],index);
        if(index == -1){break;}
    }
    if(index == -1){
        return 0;
    }else{
        return 1;
    }
}

char* Anagram(char word[] ,char txt[]){
    int i=0,index=0;
    char all[1024];
    char tmp[strlen(word)];
    int counter, letters,ptr,flag;
    for(; i<strlen(txt)-strlen(word); i++){
        counter = i;
        letters = 0;
        if((txt[i] > 64 && txt[i]<91) || (txt[i] > 96 && txt[i]<123)){
            while(letters != strlen(word) && ((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123) || txt[counter] == ' ')){
                if(((txt[counter] > 64 && txt[counter]<91) || (txt[counter] > 96 && txt[counter]<123))){
                    letters++;
                }
                counter++;
            }
            if(letters == strlen(word)){
                ptr = 0;
                for(int k=0;k < counter-i;k++){
                    if((txt[i+k] > 64 && txt[i+k]<91) || (txt[i+k] > 96 && txt[i+k]<123)){
                        tmp[ptr] = txt[i+k];
                        ptr++;
                    }
                }
                tmp[ptr] = '\0';
            }
        }
        if(letters == strlen(word)){
            flag = sameLetters(tmp,word);
            // printf("flag = %d\n",flag);
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
    }
    all[index] = '\0';
    char *p;
    p = all;
    return p;
}
