#include <iostream>
#include <memory>
#include <set>

template <class T>
class Subject;

template <class T>
class Observor
{
  public :
  virtual void update(const T& t) = 0;
  virtual ~Observor(){}

  void setSubject(Subject<T>* subjectPtr)
  {
    _subject = subjectPtr;
  }

   private:
   Subject<T>* _subject;
};

template<class T>
class Subject
{
  public :
  virtual void registerObservor(std::shared_ptr< Observor<T> > obv) = 0;
  virtual ~Subject(){}
};

template<class T>
class WeatherStation : public Subject<T>
{
  public :
  void registerObservor(std::shared_ptr< Observor<T> > obv)
  {
    obv->setSubject(this);
    _observors.insert(obv);
  }

  private :
  std::set< std::shared_ptr< Observor<T> > > _observors;
};

class StatisticsDisplay : public Observor<int>
{
  public :
  void update(const int& data) { std::cout<<"Statistics Display"; }
};

int main()
{
  WeatherStation<int> wStation;
  auto sDisplay = std::make_shared<StatisticsDisplay>();
}