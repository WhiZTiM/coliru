class Header
{
public:

};

class CanData : protected Header
{
public:
  
};

int main() {
  Header *pt = new CanData();
  //delete pt;
}