#include <iostream>
#include <string>
#include <vector>

class Person
{
  public:
    Person(const std::string& n,const std::string& h,const std::size_t age) : Name(new std::string(n)),Habit(new std::string(h)),
                                                        Counter(new std::size_t(1)),Age(age){}
    Person(const Person& p) : Name(p.Name),Habit(p.Habit),Counter(p.Counter),Age(p.Age){ ++*Counter;}
    Person& operator=(const Person&);
    ~Person();
  private:
    std::string* Name;
    std::string* Habit;
    std::size_t* Counter;
    std::size_t Age;
};

Person::~Person()
{
    if(--*Counter == 0)
    {
      delete Name;
      delete Habit;
      delete Counter;
    }
}

Person& Person::operator=(const Person& p)
{
  ++*p.Counter;
  if(--*Counter == 0)
  {
    delete Name;
    delete Habit;
    delete Counter;
  }
  Name = p.Name;
  Habit = p.Habit;
  Counter = p.Counter;
  Age = p.Age;
  return *this;

}

int main()
{
    
    return 0;
}


