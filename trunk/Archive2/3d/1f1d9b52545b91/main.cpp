#include <stdio.h>

static int N=50;

/*
static int startegy_1_ptr(int i, int *prisoner_A, int *prisoner_B)
{
    if( (i % 2) == 0) {
		*prisoner_A = *prisoner_A + 3;
		*prisoner_B = *prisoner_B + 3;
	}else{
		*prisoner_A = *prisoner_A + 10;
		*prisoner_B = *prisoner_B + 0;
	}

	return;
}
*/

static int startegy_1(int i, int pos, int prisoner_A[], int prisoner_B[])
{
	if( (i % 2) == 0) {
		prisoner_A[pos] += 3;
		prisoner_B[pos] += 3;
	}else{
		prisoner_A[pos] += 10;
		prisoner_B[pos] += 0;
	}

	return 1;
}

static int startegy_2(int i, int pos, int prisoner_A[], int prisoner_B[])
{
	if( (i % 2) == 0) {
		prisoner_A[pos] += 7;
		prisoner_B[pos] += 7;
	}else{
		prisoner_A[pos] += 0;
		prisoner_B[pos] += 10;
	}
	return 1;
}

static int startegy_3(int i, int pos, int prisoner_A[], int prisoner_B[])
{
	int j = i+1;
	static int prev_B = 0; /* 0 is omologia , 1 is mh_paradoxh */

	if( j < 3 ) {
		prisoner_A[pos] += 10;
		prisoner_B[pos] += 0;
		prev_B = 0;
	}else if( (j % 3) == 0){
		prisoner_A[pos] += ((prev_B == 0) ? 0 : 7);
		prisoner_B[pos] += ((prev_B == 0) ? 7 : 10);
		prev_B = 1;
	}else{
		prisoner_A[pos] += ((prev_B == 0) ? 7 : 10);
		prisoner_B[pos] += ((prev_B == 0) ? 7 : 0);
		prev_B = 0;
	}
	return 1;
}

static int startegy_4(int i, int pos, int prisoner_A[], int prisoner_B[])
{
	if( (i % 2) == 0) {
		prisoner_A[pos] += 10;
		prisoner_B[pos] += 0;
	}else{
		prisoner_A[pos] += 0;
		prisoner_B[pos] += 10;
	}
	return 1;
}

int main()
{
	int prisoner_A[4]={0};
	int prisoner_B[4]={0};
	int i;
		     
	for(i=0; i<N; i++){ /* Number of repeatet delema */
		startegy_1(i, 0, prisoner_A, prisoner_B);
		/* startegy_1_ptr(i, &prisoner_A[0], &prisoner_B[0]); BUT you need to know pointers */
		startegy_2(i, 1, prisoner_A, prisoner_B);
		startegy_3(i, 2, prisoner_A, prisoner_B);
		startegy_4(i, 3, prisoner_A, prisoner_B);
	}
		
	for(i=0; i<4; i++){
		printf("STRATEGY %d: YEARS FOR A: %d YEARS FOR B: %d\n", i+1, prisoner_A[i], prisoner_B[i]);
	}



		/* if dont want the functions use this
		for(j=0; j< 4; j++){
			switch(j){
				case 0:
				 break;
				case 1:
				 break;
				case 2:
				 break;
				case 3:
				 break;
			}
		}
		*/
	return 1;
}
