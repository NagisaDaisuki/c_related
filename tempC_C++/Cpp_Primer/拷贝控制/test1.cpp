#include <iostream>
#include <string>
#include <vector>


class Employee{
  friend void test();
  public:
    Employee() : Name(std::string("Anonymous"))
    {
      incId();
    }

    Employee(std::string name) : Name(name){
      incId();
    }
    Employee(const Employee& e) = delete;
    Employee& operator=(const Employee&) = default;
    ~Employee() = default;
    int incId()
    {
      hireId = ++counter;
      return hireId;
    }
  private:
    int hireId;
    std::string Name;
    static int counter;   

};

int Employee::counter = 0;

void test()
{
  Employee one("BOSS");
  Employee latter;
  std::cout << "员工ID: " << one.hireId << ",员工名称: " << one.Name << std::endl;
  std::cout << "员工ID: " << latter.hireId << ",员工名称: " << latter.Name << std::endl;

}

class BadDestructorExample{
  public:
    BadDestructorExample(int size)
    {
      data = new int[size]; //动态数组分配
      dataSize = size;
    } //普通的用户自定义构造函数

    //错误的析构函数,没有释放动态分配的内存
    ~BadDestructorExample()
    {
      //没有delete[] data;
      //delete[] data;
      std::cout << "BadDestructorExample Destructor called." << std::endl;

    }
  private:
    int* data;
    int dataSize;
};

int main()
{
    test();
    BadDestructorExample* example = new BadDestructorExample(10);
    return 0;
}
