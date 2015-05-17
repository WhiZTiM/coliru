#include <iostream>
#include <string>
#include <vector>

using namespace std;
//Search in a sorted but rotated array

class Solution {
        int searchSortedRotated(vector<int> A, int target) {
            //assume A is increasing order, and no duplicates
        int n=A.size();
        int first=0, last=n;
        while (first<=last) {
            int mid = first+(last-first)/2;
                if (target==A[mid]) { 
                return mid; 
            }
            if (A[first]<A[mid]) {
                if (A[first]<target && target<A[mid]) {
                    last = mid;
                }
                else{ first = mid+1; }
            }
            else{
                if (A[mid]<target && target<A[last-1]) {
                    first = mid+1;
                }
                else{ last = mid; }
            }
        }
        return -1;
    }
};

int main() {
    
}

