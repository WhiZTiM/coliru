class MyObj {
  MyObj(const MyObj& other) = delete;
  MyObj& operator=(const MyObj& other) = delete;
};
 
class MyContainer {
public:
  void push(MyObj&& obj) {
    vec.push_back(std::move(obj));
  }
  
private:
  std::vector<MyObj> vec;
};
 
void func() {
  MyContainer mc;
  MyObj mo;
  mc.push(std::move(mo));
}