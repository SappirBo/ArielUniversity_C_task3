#include <stdio.h>
#include <string.h>
#include "my_string.h"


/**
 * @brief THis is Helper for geometric Function.
 * @param txt  - the input String.
 * @return int  - the geometric value of the string (starting with a=A=1).
 */
int geometricValue(char txt[],int start, int end){
    int value = 0;
    for(int i=start; i<=end && txt[i] != '~'  ; i++){
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

/**
 * @brief  This function gets word and text, it findes all the sub strings in a given text the geometricly indenical to the word. 
 * 
 * @param word - char with 30 bytes max.
 * @param txt  - text with 1024 bytes max.
 * @return char* - pointer to an array with all the Strings that geometricly indenical to word. 
 */
char* geometric(char word[], char txt[]){
    int gv =geometricValue(word,0,strlen(word)); // gv = Geometric Value;
    int i=0; // i will be the index of the first char we will test
    char all[1024]; // the string that will containe all outcomes
    int ptr = 0; // pointer to the String(all) location
    int counter; // every check will be between i - counter.
    int sum; // the geometric value of the given string.
    for(; i<strlen(txt) && txt[i] != '~'; i++){
        sum = 0;
        counter = i-1;
        while(sum < gv && counter < strlen(txt)){
            counter++;
            if(((txt[i]>=65 && txt[i]<= 90) || (txt[i]>=97 && txt[i]<= 122)) && 
                            (txt[counter] != 126)){ 
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
 * @brief Helper function for Atbash, it reverses the chars (a-z,b-y).
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
/**
 * @brief Helper to Atbash, check if two Strings are equal (normaly and reversed).
 * 
 * @param a Char array 1;
 * @param b Char array 2;
 * @return int = 1 for True, int = 0 for False;
 */
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

/**
 * @brief This function gets word and text (as Strings) and find all the sub strings of the text that are Atbash equal to word.
 * 
 * @param word - char with 30 bytes max.
 * @param txt  - text with 1024 bytes max.
 * @return char* - pointer to an array.
 */
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
    char *p;
    p = all;
    return p;
}

/**
 * @brief Helper for sameLetters, it checks if char, String(char Array) and int (Y)
 *        and check how many times the char appears in the String (Let it be X),
 *        and then check if x = Y.
 * @param txt - char Array
 * @param c - char
 * @param Y -int, the amount of times to check
 * @return int = 0 if c not appears in txt Y times, int = 1 if it does.
 */
int containe(char txt[],char c, int Y){
    int flag = 0;
    int i=0;
    for(;i<strlen(txt);i++){
        if(txt[i]==c){flag += 1;}
    }
    if(flag == Y){return 1;}
    else{
        return -1;
    }
}

/**
 * @brief Helper for Anagram. checks if to char Array have exacly the same lettes.
 * 
 * @param word char Array 1;
 * @param tmp char Array 2;
 * @return int = 1 for True, int = 0 for False;
 */
int sameLetters(char word[],char tmp[]){
    int size = strlen(tmp); 
    int index = 1,count;
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
        if(index == -1){break;}
    }
    if(index == -1){
        return 0;
    }else{
        return 1;
    }
}

/**
 * @brief this function returns all the Anagram subStrings of given text.
 * 
 * @param word - char with 30 bytes max.
 * @param txt  - text with 1024 bytes max.
 * @return char* - pointer to an array. 
 */
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
