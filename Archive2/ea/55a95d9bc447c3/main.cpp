struct Point{
    double p1, p2;
    Point(double p11, double p21){p1=p11;p2=p21;}
    Point add(){return Point(p1+1,p2+1);}
    void set(){p1=0;p2=0;}
};

int main(){
    Point(1,2).add().set();
}