#include <iostream>
#include <memory>
#include <vector>
#include <string>

/*
	shared_ptr 的拷贝和赋值
	当进行拷贝或赋值操作的时候，每个shared_ptr都会记录有多少个其他shared_ptr指向相同的对象
	auto p = std::make_shared<int>(42); p指向的对象只有p一个引用
	auto q(p); //p和q指向相同对象，此对象有两个引用者

	可以认为每个shared_ptr都有一个关联的计数器，，通常称其为引用计数(reference count)
	

	使用了动态生存期的资源的类
		程序使用动态内存出于以下三种原因之一
		1.程序不知道自己需要使用多少对象
		2.程序不知道所需对象的准确类型
		3.程序需要在多个对象间共享数据
	使用动态内存的一个常见原因是允许多个对象共享相同的状态


	//直接管理内存
	new运算符和delete运算符
*/

void Memory_manage()
{
	//使用new动态分配和初始化对象
	//在自由空间分配的内存是无名的，因此new无法为其分配的对象命名
	//(传递给ptr的为动态分配对象的指针，为右值)
	int* ptr = new int; //默认初始化
	int* ptr1 = new int(); //值初始化
	//使用构造函数初始化的类类型可以用在动态分配内存上
	std::string* str = new std::string(10,'9'); 

	//对于定义了自己构造函数的类类型来说，值初始化和默认初始化没有区别
	//但是对于内置类型对象来说默认初始化和值初始化之间是有区别的
	//内置类型对象默认初始化的值是未定义的
	//在类中依赖于编译器合成的默认构造函数的内置类型成员如果未在
	//类内被初始化，那么他们的值也是未定义的

	std::string obj = "hello world";
	auto p1 = new auto(obj); //通过auto自动推导出obj的类型
	//只能对单一初始化器执行
	//auto p2 = new auto(a,b,c); //错误，括号中只能有单个初始化器


	//动态分配const对象
	const int* pci = new const int(1024); //值初始化
	const std::string* pcs = new const std::string; //默认初始化
	
	//类似于其他const对象，一个动态分配的const对象必须进行初始化
	
	//内存耗尽(当前基本不可能)
	//如果计算机内存耗尽 new表达式就会失败
	//分配失败会抛出一个类型为bad_alloc的异常
	//可以改变使用new的方式来阻止它抛出异常

	int *p3 = new int;
	int* p4 = new (std::nothrow) int; //如果分配失败，new返回一个空指针

	//为了防止内存耗尽，在动态内存使用完毕后
	//必须将其归还给系统

	delete ptr1;
	//1.销毁给定指针指向的对象 2.释放对应的内存

	//释放一块非new分配的内存或将相同的指针释放多次，其行为是未定义的
	
	
	/*
		对于一个由内置指针管理的动态对象，直到它被显式释放前它都是存在的

		与类类型不同，内置类型的对象被销毁时什么也不会发生。特别是当一个指针离开其作用域时
		它所指向的对象什么也不会发生，如果这个指针指向的是动态内存，那么内存将不会被
		释放
	*/

	/*动态内存的管理非常容易出错*/
	/*
		使用new和delete管理动态内存存在三个常见问题
		1.忘记delete内存
		2.使用已经释放掉的内存
		3.同一块内存释放两次
	*/

	//delete之后重置指针值

	//shared_ptr和new结合使用
	//可以使用new返回指针来初始化智能指针

	std::shared_ptr<double> p10; //初始化一个空指针
	std::shared_ptr<int> p20(new int(1024)); //使用new为智能指针分配内存
	//接受指针参数的智能指针构造函数是explicit的，我们不能将一个内置指针隐式转换为智能指针，必须使用直接初始化形式
	//shared_ptr<int> p1 = new int(1024); //错误：必须使用直接初始化形式
	std::shared_ptr<int> p30(new int()); //正确：使用了直接初始化形式
	
		

}

class StrBlob{
	public:
		typedef std::vector<std::string>::size_type size_type;
		StrBlob();
		StrBlob(std::initializer_list<std::string> il);
		size_type size() const {return data->size();}
		bool empty() const {return data->empty();}
		//添加和删除元素1
		void push_back(const std::string &t) {data->push_back(t);}
		void pop_back();
		//元素访问
		std::string& front();
		const std::string& front_const();
		std::string& back();
		const std::string& back_const();
	private:
		void check(size_type i,const std::string &msg) const;
		std::shared_ptr<std::vector<std::string>> data;
		//如果data[i]不合法，抛出一个异常
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {} //initializer_list
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {} //initializer_list

void StrBlob::check(size_type i,const std::string &msg) const
{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
	check(0,"front on empty StrBlob");
	return data->front();
}

const std::string& StrBlob::front_const()
{
	check(0,"front_const on empty StrBlob");
	return const_cast<const std::string&>(data->front());
}

std::string& StrBlob::back()
{
	check(0,"back on empty StrBlob");
	return data->back();
}

const std::string& StrBlob::back_const()
{
	check(0,"back_const on empty Strblob");
	return const_cast<const std::string&>(data->back());
}


void StrBlob::pop_back()
{
	check(0,"pop_back on empty StrBlob");
	data->pop_back();
}


int main()
{
	StrBlob sb = {"hey","hello","ciallo"}; //strblob类里面构造函数支持接收initializer_list类型
	std::cout << "保存的第一个字符串: " << sb.front() << std::endl;
	
	std::cout << "保存的最后一个字符串: " << sb.back() << std::endl;
	//
	
	
	return 0;
}
