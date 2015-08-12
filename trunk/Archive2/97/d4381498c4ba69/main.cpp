#include <vector>
#include <iostream>
#include <assert.h>

template <typename C>
void output(const C& c_, int len)
{
    for ( int i=0; i<len;i++)
    {
        //std::cout << c_[i] << ", ";
        printf("%d, ", c_[i]);
    }
    //std::cout << std::endl;
    printf("\n");
}

void swap(int *c, int a, int b) {
    int tmp = c[a];
    c[a] = c[b];
    c[b] = tmp;
}

void myAlgoInplace(int* c, int len) {
    int poslen = 0, neglen = 0, zerolen = 0;
    for (int i=0; i < len; i++) {
        if (c[i] == 0) 
            zerolen++;
        else if (c[i]>0)
            poslen++;
        else
            neglen++;
    }
    int curneg = 0;
    int curzero = neglen;
    int curpos = neglen+zerolen;
    for (int i=0; i< neglen; i++) {
        for (int j=0; j< len; j++) {
            if (c[j] < 0) {
                printf("[i:%d]1 j:%d swapping %d and %d\n", i, j, c[i], c[j]);
                swap(c, i, j);
                curneg++;
                break;
            }
        }
    }
    for (int i=neglen; i< neglen+zerolen; i++) {
        for (int j=0; j< len; j++) {
            if (c[j] == 0) {
                printf("[i:%d]2 j:%d swapping %d and %d\n", i, j, c[i], c[j]);
                swap(c, i, j);
                curzero++;
                break;
            }
        }
    }
    for (int i=neglen+zerolen; i< len; i++) {
        for (int j=0; j< len; j++) {
            if (c[j] > 0) {
                printf("[i:%d]3 j:%d swapping %d and %d\n", i, j, c[i], c[j]);
                swap(c, i, j);
                curpos++;
                break;
            }
        }
    }
}

int* myAlgo(int* c_, int len)
{
    int poslen = 0, neglen = 0, zerolen = 0;
    for (int i=0; i < len; i++) {
        if (c_[i] == 0) 
            zerolen++;
        else if (c_[i]>0)
            poslen++;
        else
            neglen++;
    }
    int* res = (int*) malloc(sizeof(int)*len);
    int curneg = 0;
    int curzero = neglen;
    int curpos = neglen+zerolen;
    for (int i=0; i < len; i++) {
        if (c_[i] == 0) {
            res[curzero] = c_[i];
            curzero++;
        } else if (c_[i]>0) {
            res[curpos] = c_[i];
            curpos++;
        } else {
            res[curneg] = c_[i];
            curneg++;
        }
    }

    return res;
}

int main(int argc, char* argv[])
{
    //std::vector<int> vec { 1, 0, -2, 1, -1, 2, 0 };
    int vec[] = { 1, 0, -2, 1, -1, 2, 0 };
    int len = sizeof(vec)/sizeof(int);
    std::cout << "Input: " << std::endl;
    output(vec, len);
    myAlgoInplace(vec, len);
    std::cout << "Output: " << std::endl;
    output(vec, len);
    return 0;
}

