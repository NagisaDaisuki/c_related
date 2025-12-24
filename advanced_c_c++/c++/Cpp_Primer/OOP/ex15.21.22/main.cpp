#include <iostream>
#include <string>
#include <utility>

// just for 2D shape

class Shape{
  
public:
  typedef std::pair<double,double> Coordinate;
  
  Shape() = default;
  Shape(const std::string& n) : name(n){}
  
  virtual double area() const = 0;
  virtual double perimeter() const = 0;

  virtual ~Shape() = default;
  /*
      在C++中，如果一个类含有虚函数（包括虚析构函数），
      那么它的析构函数就应该声明为虚析构函
      数。虚析构函数的作用包括以下几个方面：

      1.多态行为的保证： 当使用基类指针或引用指向派生类对象并进行删除操作时，
      如果基类的析构函数不是虚函数，可能会导致只调用基类的析构函数而不调用派生
      类的析构函数，从而造成资源泄漏或不正确的行为。通过将基类的析构函数声明为
      虚函数，可以确保在销毁派生类对象时调用派生类的析构函数。
  
      2.确保正确的资源释放: 如果派生类拥有动态分配的资源(如堆内存、打开的文件等)
      ，则虚析构函数确保在销毁派生类对象时正确释放这些资源

      3.向后兼容性: 在设计基类时，如果预期后续可能会有派生类继承这个基类，将析构
      函数声明为虚函数是一种良好的做法。这样做可以确保后续派生类的扩展不会破坏基类
      的行为
*/
private:
  std::string name;
};

class Rectangle : public Shape{

public:
    Rectangle() = default;
    Rectangle(const std::string& n,
              const Coordinate& a,
              const Coordinate& b,
              const Coordinate& c,
              const Coordinate& d) :
          Shape(n),a(a),b(b),c(c),d(d){}
    ~Rectangle() = default;
private:
          Coordinate a;
          Coordinate b;
          Coordinate c;
          Coordinate d;
  
};

class Square : public Rectangle{
  public:
    Square() = default;
    Square(const std::string& n,
           const Coordinate& a,
           const Coordinate& b,
           const Coordinate& c,
           const Coordinate& d)
      : Rectangle(n,a,b,c,d){}
    ~Square() = default;
};

int main()
{
    return 0;
}
