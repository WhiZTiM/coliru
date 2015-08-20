struct s { int x = 100, y = 3; };

class c {
    int x, y;
public:
    c( s v ) : x( v.x ), y( v.y ) {}
};

s q ({ .x = 5 });
c r ({ .x = 5 });

int main() {}