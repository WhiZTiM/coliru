
class Pair{
public:
    Pair(Pair && other){};

    Pair(const Pair & other){};
};

class IROList{
public:
    virtual const Pair get(const char *key) const = 0;

    inline const Pair operator[](const char *key) const{
        return this->get(key);
        // error: binding ‘const Pair’ to reference of type ‘Pair&&’ discards qualifiers
    }
};

int main()
{

}