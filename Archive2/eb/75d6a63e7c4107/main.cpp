#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

// From 11/15/14; JOB PEGS program hopefully

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Board {int t[6][6]; int move; bool moved; bool listed; int moves[36]; 
    };

int ScoreItA(Board b){
    return b.t[0][0];
}

void PrintIt(Board b){

std::cout   <<b.t[0][0] <<"\t\t\t\t"<<1<<","<<1<<":"<<b.t[1][1]<<" ";
    for (int x=0; x<36; x++) {std::cout<<b.moves[x]<<":";}
    std::cout<<"\n";
std::cout               <<"\t\t\t"  <<1<<","<<2<<":"<<b.t[1][2]<<"\t\t"<<2<<","<<2<<":"<<b.t[2][2]<<"\n";
std::cout               <<"\t\t"    <<1<<","<<3<<":"<<b.t[1][3]<<"\t\t"<<2<<","<<3<<":"<<b.t[2][3]<<"\t\t"<<3<<","<<3<<":"<<b.t[3][3]<<"\n";
std::cout               <<"\t"      <<1<<","<<4<<":"<<b.t[1][4]<<"\t\t"<<2<<","<<4<<":"<<b.t[2][4]<<"\t\t"<<3<<","<<4<<":"<<b.t[3][4]<<"\t\t"<<4<<","<<4<<":"<<b.t[4][4]<<"\n";
std::cout                           <<1<<","<<5<<":"<<b.t[1][5]<<"\t\t"<<2<<","<<5<<":"<<b.t[2][5]<<"\t\t"<<3<<","<<5<<":"<<b.t[3][5]<<"\t\t"<<4<<","<<5<<":"<<b.t[4][5]<<"\t\t"<<5<<","<<5<<":"<<b.t[5][5]<<"\n";
std::cout << "Altered " << b.moved;
//std::cout << x << "," << y << ":" << b.t[x][y] << "\t";
//        }
//        std:: cout << std::endl;
//    }
    std:: cout << std::endl;
}

Board Move(Board b, int n){
    Board b1;
    for (int x=0; x<6; x++) {
        for (int y=0; y<6; y++) {
            b1.t[x][y] = b.t[x][y];
        }
    }
    //for (int x=0; x<6; x++) { b1.t[0][x] = 0;}
    for (int x=0; x<36; x++) { b1.moves[x] = 0;}
    b1.move = 0;
    b1.t[0][0] = (b.t[0][0]+1);
    int ax, ay, cx, cy;
    ax = int(b.moves[n]/1000);
    ay = int((b.moves[n] - (1000*ax))/100);
    cx = int((b.moves[n] - (1000*ax) - (100*ay))/10);
    cy = int(b.moves[n] - (1000*ax) - (100*ay) - (10*cx));
//std::cout<<"n="<<n<<" b.moves[n]:"<<b.moves[n]<<":"<<ax<<","<<ay<<":"<<cx<<","<<cy<<"\n";
    b1.t[ax][ay] = 0;
    b1.t[cx][cy] = 1;
//PrintIt(b1);
    return b1;
}

bool ListMoves(Board& b)
{
    int num = 0;
        if (!b.listed) {
        for (int x=0; x<6; x++) {
            for (int y=0; y<6; y++) {
                //std::cout << "Checking:" << x << "," << y << "\n";
                // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
                if ((x==1) && (y==1)) {
                    if ((b.t[1][1]==1) && (b.t[1][2]==1) && (b.t[1][3]==0)) {b.moves[num++]=1113; }
                    if ((b.t[1][1]==1) && (b.t[2][2]==1) && (b.t[3][3]==0)) {b.moves[num++]=1133; }
                    }
                if ((x==1) && (y==2)) {
                    if ((b.t[1][2]==1) && (b.t[1][3]==1) && (b.t[1][4]==0)) {b.moves[num++]=1214; }
                    if ((b.t[1][2]==1) && (b.t[2][3]==1) && (b.t[3][4]==0)) {b.moves[num++]=1234; }
                    }
                if ((x==1) && (y==3)) {
                    if ((b.t[1][3]==1) && (b.t[1][2]==1) && (b.t[1][1]==0)) {b.moves[num++]=1311; }
                    if ((b.t[1][3]==1) && (b.t[1][4]==1) && (b.t[1][5]==0)) {b.moves[num++]=1315; }
                    if ((b.t[1][3]==1) && (b.t[2][3]==1) && (b.t[3][3]==0)) {b.moves[num++]=1333; }
                    if ((b.t[1][3]==1) && (b.t[2][4]==1) && (b.t[3][5]==0)) {b.moves[num++]=1335; }
                    }
                if ((x==1) && (y==4)) {
                    if ((b.t[1][4]==1) && (b.t[1][3]==1) && (b.t[1][2]==0)) {b.moves[num++]=1412; }
                    if ((b.t[1][4]==1) && (b.t[2][4]==1) && (b.t[3][4]==0)) {b.moves[num++]=1434; }
                    }
                if ((x==1) && (y==5)) {
                    if ((b.t[1][5]==1) && (b.t[1][4]==1) && (b.t[1][3]==0)) {b.moves[num++]=1513; }
                    if ((b.t[1][5]==1) && (b.t[2][5]==1) && (b.t[3][5]==0)) {b.moves[num++]=1535; }
                    }
                if ((x==2) && (y==2)) {
                    if ((b.t[2][2]==1) && (b.t[3][3]==1) && (b.t[4][4]==0)) {b.moves[num++]=2244; }
                    if ((b.t[2][2]==1) && (b.t[2][3]==1) && (b.t[2][4]==0)) {b.moves[num++]=2224; }
                    }
                if ((x==2) && (y==3)) {
                    if ((b.t[2][3]==1) && (b.t[2][4]==1) && (b.t[2][5]==0)) {b.moves[num++]=2325; }
                    if ((b.t[2][3]==1) && (b.t[3][4]==1) && (b.t[4][5]==0)) {b.moves[num++]=2345; }
                    }
                if ((x==2) && (y==4)) {
                    if ((b.t[2][4]==1) && (b.t[2][3]==1) && (b.t[2][2]==0)) {b.moves[num++]=2422; }
                    if ((b.t[2][4]==1) && (b.t[3][4]==1) && (b.t[4][4]==0)) {b.moves[num++]=2444; }
                    }
                if ((x==2) && (y==5)) {
                    if ((b.t[2][5]==1) && (b.t[2][4]==1) && (b.t[2][3]==0)) {b.moves[num++]=2523; }
                    if ((b.t[2][5]==1) && (b.t[3][5]==1) && (b.t[4][5]==0)) {b.moves[num++]=2545; }
                    }
                if ((x==3) && (y==3)) {
                    if ((b.t[3][3]==1) && (b.t[2][3]==1) && (b.t[1][3]==0)) {b.moves[num++]=3313; }
                    if ((b.t[3][3]==1) && (b.t[2][2]==1) && (b.t[1][1]==0)) {b.moves[num++]=3311; }
                    if ((b.t[3][3]==1) && (b.t[4][4]==1) && (b.t[5][5]==0)) {b.moves[num++]=3355; }
                    if ((b.t[3][3]==1) && (b.t[3][4]==1) && (b.t[3][5]==0)) {b.moves[num++]=3335; }
                    }
                if ((x==3) && (y==4)) {
                    if ((b.t[3][4]==1) && (b.t[2][3]==1) && (b.t[1][2]==0)) {b.moves[num++]=3412; }
                    if ((b.t[3][4]==1) && (b.t[2][4]==1) && (b.t[1][4]==0)) {b.moves[num++]=3414; }
                    }
                if ((x==3) && (y==5)) {
                    if ((b.t[3][5]==1) && (b.t[2][5]==1) && (b.t[1][5]==0)) {b.moves[num++]=3515; }
                    if ((b.t[3][5]==1) && (b.t[4][5]==1) && (b.t[5][5]==0)) {b.moves[num++]=3555; }
                    if ((b.t[3][5]==1) && (b.t[2][4]==1) && (b.t[1][3]==0)) {b.moves[num++]=3513; }
                    if ((b.t[3][5]==1) && (b.t[3][4]==1) && (b.t[3][3]==0)) {b.moves[num++]=3533; }
                    }
                if ((x==4) && (y==4)) {
                    if ((b.t[4][4]==1) && (b.t[3][3]==1) && (b.t[2][2]==0)) {b.moves[num++]=4422; }
                    if ((b.t[4][4]==1) && (b.t[3][4]==1) && (b.t[2][4]==0)) {b.moves[num++]=4424; }
                    }
                if ((x==4) && (y==5)) {
                    if ((b.t[4][5]==1) && (b.t[3][4]==1) && (b.t[2][3]==0)) {b.moves[num++]=4523; }
                    if ((b.t[4][5]==1) && (b.t[3][5]==1) && (b.t[2][5]==0)) {b.moves[num++]=4525; }
                    }
                if ((x==5) && (y==5)) {
                    if ((b.t[5][5]==1) && (b.t[4][4]==1) && (b.t[3][3]==0)) {b.moves[num++]=5533; }
                    if ((b.t[5][5]==1) && (b.t[4][5]==1) && (b.t[3][5]==0)) {b.moves[num++]=5535; }
                    }
            }         
        }
        }
        b.move=num;
        if (num==0) {b.listed=0;} else {b.listed=1;}
        //b.moved=1;
    //for (int x=0;x<36;x++) {std::cout << b.moves[x] << " ";} std::cout<<b.move<<"\n";
    return b.moved;
}



int main()
{       
    std::vector<std::string> words = { "Hello", "from", "GCC", __VERSION__, "!" };
    std::cout << words << std::endl;

    vector<Board> b0(1);
    for (int x=0; x<6; x++) {
        for (int y=0; y<6; y++) {
            b0.at(0).t[x][y] = 1;
        }
    }

    b0.at(0).t[0][0] = 0; //Level of Board
    b0.at(0).t[5][5] = 0;
    b0.at(0).moved=0; // not listed moved yet

std::for_each(b0.begin(), b0.end(), PrintIt); std::cout<<"********\n";
    std::for_each(b0.begin(), b0.end(), ListMoves);  
    int ListedNotMoved = b0.size();
    for (int x = 0; x<(b0.at(0).move); x++) {b0.push_back(Move(b0.at(0),x));}
    
    int Moved = b0.size();
    std::cout<< num<<"\n";

std::for_each(b0.begin(), b0.end(), PrintIt); std::cout<<"********\n";
    std::for_each(b0.begin(), b0.end(), ListMoves); //only adds moves if not listed already 
    for (uint x = 1; x<(b0.size()); x++)
        for (int y = 0; y<b0.at(x).move; y++) {
            b0.push_back(Move(b0.at(x),y));
            ListedNotMoved++;
        }
        
std::for_each(b0.begin(), b0.end(), PrintIt); std::cout<<"********\n";

    int Score[16]={0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
    for (uint x = 0; x<(b0.size()); x++) {
        switch (ScoreItA(b0.at(x))) {
        case (0):Score[0]++;Score[15]++;break;
        case (1):Score[1]++;Score[15]++;break;
        case (2):Score[2]++;Score[15]++;break;
        case (3):Score[3]++;Score[15]++;break;
        case (4):Score[4]++;Score[15]++;break;
        case (5):Score[5]++;Score[15]++;break;
        case (6):Score[6]++;Score[15]++;break;
        case (7):Score[7]++;Score[15]++;break;
        case (8):Score[8]++;Score[15]++;break;
        case (9):Score[9]++;Score[15]++;break;
        case (10):Score[10]++;Score[15]++;break;
        case (11):Score[11]++;Score[15]++;break;
        case (12):Score[12]++;Score[15]++;break;
        case (13):Score[13]++;Score[15]++;break;
        case (14):Score[14]++;Score[15]++;break;
        case (15):Score[15]++;Score[15]++;break;
        default: ;
        }
    }

//    for (int x = 0; x<15; x++) {std::cout << "Number of Level: "<<x<<"="<<Score[x]<<"for records:"<< b0.size() <<Score[15]<<"\n";}
//    std::for_each(b0.begin(), b0.end(), PrintIt); 
}
