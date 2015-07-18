#include <iterator>
#include <list>
#include <string>
#include <iostream>

struct Piece {
    std::string name;
};

class PieceList
{
    public:
        PieceList(){}
        PieceList(PieceList const& rhs){pieces = rhs.pieces;}
        PieceList(std::list<Piece> const& rhs){pieces = rhs;}

        friend std::ifstream& operator>>(std::ifstream&,PieceList&);
        friend std::istream& operator>>(std::istream&,PieceList&);

        class iterator
        {
            public:
                friend class PieceList;

                iterator(){}
                iterator(iterator const& rhs) : data(rhs.data) {}
                iterator(std::list<Piece>::iterator rhs) : data(rhs) {}

                Piece operator*(){return *data;}
                iterator& operator=(iterator& rhs){data=rhs.data;return *this;}
                iterator& operator=(std::list<Piece>::iterator& rhs){data = rhs;return *this;}
                bool operator==(iterator& rhs){return data==rhs.data;}
                bool operator==(const iterator& rhs) const{return data==rhs.data;}
                bool operator!=(iterator rhs){return data != rhs.data;}
                iterator& operator++(){++data;return *this;}
                iterator& operator--(){--data;return *this;}
            private:
                std::list<Piece>::iterator data;
        };

        iterator first(){iterator i;i.data=pieces.begin();return i;}
        iterator last(){iterator i;i.data=pieces.end();return i;}

    private:
        std::list<Piece> pieces;
};

int main() {
    PieceList pl { {
        { "aap" },
        { "noot" },
        { "mies" },
    } };
    for(auto it=pl.first(); it!=pl.last(); ++it) {
        std::cout << (*it).name << "\n";
    }
}
