#include <iostream>


class Topology {
    public: 
        Topology();
        ~Topology();

        void set_dim(int);
        void set_sizes(int*);

        int get_dim();
        int* get_sizes();

    private:
        int dim;
        int *sizes;
};

Topology::Topology(){

}
Topology::~Topology(){ 
    if (sizes != NULL) 
        delete sizes; 
}
void Topology::set_dim(int dim_){
    dim = dim_;
}
void Topology::set_sizes(int *sizes_){ 
    sizes = new int[dim];
    for (int i = 0; i < dim; i++){
        sizes[i] = sizes_[i];
    }
}
int Topology::get_dim(){
    return dim;
}
int* Topology::get_sizes(){ 
    return sizes;
}

class Parallelization{
    public:
        Parallelization();
        ~Parallelization();

        void set_topology(Topology top);
    private:
};

Parallelization::Parallelization(){

}
Parallelization::~Parallelization(){

}
void Parallelization::set_topology(Topology top){
    int *s = top.get_sizes();
    for (int i = 0; i < top.get_dim(); i++){
        std::cout << s[i] << " "; // here it prints different numbers, like the vector was never initialized [23144, 352452]
    }
}


class Architecture {
    public: 
        Architecture();
        ~Architecture();

        void set_topology(Topology top);

    private:
        Parallelization p;
};

Architecture::Architecture(){

}
Architecture::~Architecture(){

}
Architecture::set_topology(Topology top){
    p.set_topology(top);
}


int main (){
    int sizes[] = {2, 3};
    Topology top;
    top.set_dim(2); // 2D topology
    top.set_sizes(sizes); // 2 rows and 3 columns

    Architecture arch;
    arch.set_topology(top);
    return 0;
}