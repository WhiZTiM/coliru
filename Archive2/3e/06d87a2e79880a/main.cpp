#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Sums all digits of a number until there is only one digit */
int sumDigits(int n)
{
    int res=0;
    while(n>0)
    {
        res+=n%10;
        n/=10;
    }
    return res<10 ? res : sumDigits(res);
}

/* Allocates a string, must be freed */
char* SumCharsAndDigits(const char *str)
{
    int sum=0;
    char* res;
    while(*str)
    {
        if(*str>='0' && *str<='9') sum+=*str-'0';
        else if(*str>='a' && *str<='z') sum+=*str-'a'+1;
        else if(*str>='A' && *str<='Z') sum+=*str-'A'+1;
        str++;
    }
    res=(char*)malloc(2);
    res[0]='0'+sumDigits(sum);
    res[1]=0;
    return res;
}

/* Returns 1 if the strings are equal, 0 otherwise */
int strEquals(const char *a, const char *b)
{
    while(*a && *b)
    {
        if(*a!=*b) return 0;
        a++;
        b++;
    }
    return(*a==0 && *b==0);
}

void testSumCharsAndDigits(const char *in, const char *out)
{
    char *res=SumCharsAndDigits(in);
    printf("SumCharsAndDigits(\"%s\") returns \"%s\" : %s\n",in,res,strEquals(res,out) ? "PASS" : "FAIL");
    free(res);
}

typedef struct WordInfos_s
{
    char *str;
    int sum;
} WordInfos;

/* Count words and fills a WordInfos array if the pointer passed is not NULL*/
int countWords(const char *str, WordInfos *wordInfos)
{
    const char *pos=str;
    const char *wordPos;
    char *tmp;
    int nbWords=0;
    while(*pos)
    {
        while(*pos && *pos==' ') pos++;
        if(*pos)
        {
            wordPos=pos;
            while(*pos && *pos!=' ') pos++;
            if(wordInfos)
            {
                tmp=(char*)malloc(pos-wordPos+1);
                wordInfos[nbWords].str=tmp;
                while(*wordPos && *wordPos!=' ') *tmp++=*wordPos++;
                *tmp=0;
                tmp=SumCharsAndDigits(wordInfos[nbWords].str);
                wordInfos[nbWords].sum=*tmp-'0';
                free(tmp);
            }
            nbWords++;
        }
    }
    return nbWords;
}

void mergeSortArray(WordInfos *array, int n)
{
    WordInfos *tempArray,*array0,*array1;
    int size0,size1,pos=0;
    if(n<2) return;
    else
    {
        size0=n/2;
        size1=n-size0;
        mergeSortArray(array,size0);
        array0=array;
        array1=array+size0;
        mergeSortArray(array1,size1);
        tempArray=(WordInfos*)malloc(n*sizeof(WordInfos));
        while(size0 && size1)
        {
            if(array0->sum<array1->sum)
            {
                tempArray[pos++]=*array0;
                size0--;
                array0++;
            }
            else
            {
                tempArray[pos++]=*array1;
                size1--;
                array1++;
            }
        }
        while(size0)
        {
            tempArray[pos++]=*array0;
            size0--;
            array0++;
        }
        while(size1)
        {
            tempArray[pos++]=*array1;
            size1--;
            array1++;
        }
        memcpy(array,tempArray,n*sizeof(WordInfos));
    }
}

void PrintWordsSorted(const char* str)
{
    int nbWords,i;
    WordInfos *wordInfos;

    /* Create and fill the array of words */
    nbWords=countWords(str,NULL);
    wordInfos=(WordInfos*)malloc(sizeof(WordInfos)*nbWords);
    countWords(str,wordInfos);

    /* Sort it*/
    mergeSortArray(wordInfos,nbWords);

    /* Print it and free it*/
    for(i=0;i<nbWords;i++)
    {
        printf("%d: %s\n",wordInfos[i].sum,wordInfos[i].str);
        free(wordInfos[i].str);
    }
    free(wordInfos);
}

int main(int argc, char **argv)
{
    testSumCharsAndDigits("123","6");
    testSumCharsAndDigits("1234","1");
    testSumCharsAndDigits("ab","3");
    testSumCharsAndDigits("CD","7");
    testSumCharsAndDigits("12+aB$ ","6");
    testSumCharsAndDigits("","0");
    printf("\n");
    PrintWordsSorted("Mon code est cool !");
    printf("\n");
    PrintWordsSorted("");
    printf("\n");
    PrintWordsSorted("  That's all Folks !  ");
    return 0;
}
