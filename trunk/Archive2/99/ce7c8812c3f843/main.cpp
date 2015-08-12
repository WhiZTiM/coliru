
template <typename R, typename... Args>                                     
class RunnableAdapter{
    //<R(*)(Args...)>
 public:
  typedef R (RunType)(Args...);

  explicit RunnableAdapter(R(*function)(Args...))   
      : function_(function) {
  }

  R Run(Args... args) {
    return function_(args...);
  }

 private:
  R (*function_)(Args...);
};

 void myFunction(int i){  // 
 }
        
int main()
{
  void(*fun)(int) = myFunction;
 //std::function<void(*fn)(int)> p = * myFunction;
 RunnableAdapter<decltype(fun),int> ra;
 ra.Run(1);    //which calls myFunction(1)? how?
 }