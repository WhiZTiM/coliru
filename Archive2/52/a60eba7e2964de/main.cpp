/*
 ============================================================================
 Name        : A.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Size map
#define size_x 10
#define size_y 10
// node start
#define start_x 0
#define start_y 0
// node stop
#define stop_x 9
#define stop_y 9
//Connectivité 4 ou 8
#define connectivite 4

//Map
int tab[size_x][size_y]={
    				{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0}};

int tab_calcule[size_x][size_y]={
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0}};

int distance(int x1, int y1){
	return sqrt(pow((stop_x -x1),2) + pow((stop_y -y1),2));
}

int deplacement_x(int i){
	switch(i){
	case 1 : return -1;
	case 2 : return 0;
	case 3 : return 1;
	case 4 : return 0;
	//Diagonale
	case 5 : return -1;
	case 6 : return -1;
	case 7 : return 1;
	case 8 : return 1;
	//erreure
	default : return 0;
	}
}

int deplacement_y(int i){
	switch(i){
	case 1 : return 0;
	case 2 : return -1;
	case 3 : return 0;
	case 4 : return 1;
	//Diagonale
	case 5 : return -1;
	case 6 : return 1;
	case 7 : return -1;
	case 8 : return 1;
	//erreure
	default : return 0 ;
	}
}

int * node (int x, int y){
	int x_1 =0;
	int y_1 =0;
	int i=1;
	int prix_distance = 0;
	int prix_distance_tmp=5000;
	int coordonee[2] = {0,0};

	while(i<connectivite + 1){
		x_1 = deplacement_x(i) + x;
		y_1 = deplacement_y(i) + y;
		if (x_1<0 || y_1<0 || x_1 > size_x - 1 || y_1 > size_y - 1|| tab[x_1][y_1]==9 ){
			// point non valid
		}
		else {
			prix_distance =  distance(x_1,y_1);
			tab_calcule[x_1][y_1]= prix_distance;
			
			if (prix_distance < prix_distance_tmp) {
				prix_distance_tmp = prix_distance;
				coordonee [0] =  x_1;
				coordonee [1] = y_1;
			}
		}
		i++;
	}
	return coordonee;
}

int main(void) {
	int i =0;
	int j =0;
	int * coordonee={0};

	coordonee = node (start_x,start_y);
	
    while(coordonee[0]!=stop_x && coordonee[1]!=stop_y){
    	coordonee = node (coordonee[0],coordonee[1]);
    }
    
	//Affichage carte
	for(i = 0 ; i < size_x ; i++){
		printf("\r");
	    for(j = 0 ; j < size_y ; j++){
	    	printf(" %d", tab_calcule[i][j]+tab[i][j]);
	    }
	}
	printf("\r");
	return 0;
}
