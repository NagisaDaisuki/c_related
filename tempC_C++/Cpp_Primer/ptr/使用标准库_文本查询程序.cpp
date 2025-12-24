#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
#include <numeric>
#include <set>
#include <map>
#include <fstream>

/*
    文本查询程序
        -实现功能：允许用户在一个给定文件中查询单词（std::ifstream）
        -查询结果(std::set std::map) 快速查找的数据结构，且不包含重复的结果
            1.单词在文件中出现的次数
            2.单词所在行的列表
        （如果一个单词在一行中出现多次，此行只列出一次）
        行会按照升序输出(例如第七行会在第九行之前)
    
    ----->开始一个程序的设计的一种好方法是列出程序的操作
    了解需要哪些操作会帮助我们分析出我们需要那样的数据结构

    ----->任务:
        1.当程序读取输入文件时，它必须记住单词出现的每一行。因此，程序需要
        逐行读取输入文件，并将每一行分解为独立的单词
        2.当程序生成输出时
            -- 它必须是能够读取每个单词所关联的行号
            -- 行号必须升序且无重复
            -- 它必须能打印给定行号中的文本

    ----->解决方案:
        1.使用一个vector<string>来保存整个输入文件的一份拷贝，输入文件中的
        每行保存为vector中的一个元素，当需要打印一行时，可以用行号作为下标来提取文文本
        (std::shared_ptr<std::vector<std::string>>)
        2.使用一个istringstream来将每一行分解为单词
        3.使用一个set来保存每个单词在输入文本中出现的行号。保证每行只出现一次且行号按升序排序
        4.使用一个map来将每个单词与它出现的行号set关联起来
        这样就可以方便地提取任意单词的set


        
*/

/*
    两个类之间进行数据共享--->shared_ptr
*/
using line_no = std::vector<std::string>::size_type;

class QueryResult; //为了定义函数query的返回类型，这个定义是必须的

class TextQuery
{
    public:
        TextQuery(std::ifstream&);
        QueryResult query(const std::string&) const;
    
    private:
        std::shared_ptr<std::vector<std::string>> file; //输入文件
        //每个单词到它所在的行号的映射
        std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;  
};

//构造函数
TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>)
{
    std::string text;
    while(std::getline(is,text)) //获取文件中的每一行字符串
    {
        file->push_back(text);  //保存此行文本
        int n = file->size() - 1; //当前行号
        std::istringstream line(text); //将行文本分解为单词
        std::string word;
        
        while(line >> word) //每行中的单词
        {
            //如果单词不在wm中，以之为下标在wm中添加一项
            auto& lines = wm[word];
            if(!lines)
                lines.reset(new std::set<line_no>); //分配一个新set
            lines->insert(n); //将此行号保存在set中
        }
    }
}

class QueryResult
{
    friend std::ostream& print(std::ostream&,const QueryResult&);
    public:
        QueryResult(std::string s,
                    std::shared_ptr<std::set<line_no>> p,
                    std::shared_ptr<std::vector<std::string>> f) : 
                    sought(s),lines(p),file(f){}
    private:
        std::string sought; //查询单词
        std::shared_ptr<std::set<line_no>> lines; //出现的行号
        std::shared_ptr<std::vector<std::string>> file; //输入文件
};

//query函数
QueryResult TextQuery::query(const std::string& sought) const 
{
    //如果未找到sought,返回一个指向此set的指针
    static std::shared_ptr<std::set<line_no>> no_data(new std::set<line_no>); 
    //使用find而不是下标运算符来查找单词，避免将单词添加到wm中
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought,no_data,file);  
    else
        return QueryResult(sought,loc->second,file);
}

std::string make_plural(size_t ctr,const std::string& words,const std::string& ending)
{
    return (ctr > 1) ? words + ending : words;
}

//打印结果
std::ostream& print(std::ostream& os,const QueryResult& qr)
{
    //如果找到单词，打印出现次数和所有出现的位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural(qr.lines->size(),"time","s") << std::endl;
    //打印单词出现的每一行
    for(auto num : *qr.lines) //对set中的每个单词
    {
        //避免行号给用户带来误扰
        os << "\t(line " << num + 1 << ") "
            << *(qr.file->begin() + num) << std::endl;
        
    }
    return os; //链式编程
}


void runQueries(std::ifstream& infile)
{
    //infile是一个ifstream 指向我们要处理的文件
    TextQuery tq(infile);
    //与用户交互：提示用户输入要查询的单词，完成查询并打印结果
    while(true)
    {
        std::cout << "enter word to look for,or q to quit: ";
        std::string s;
        //若是遇到文件尾或是用户输入了'q'结束查询
        if(!(std::cin >> s) || s == "q")
            break;
        print(std::cout,tq.query(s)) << std::endl;
    }   
}
int main()
{
    std::ifstream ifs;
    ifs.open("new.txt");
    runQueries(ifs);
    ifs.close();
    return 0;
}
