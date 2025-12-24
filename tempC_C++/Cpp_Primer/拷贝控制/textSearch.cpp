#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include <set>
#include <map>
#include <fstream>

using line_no = std::vector<std::string>::size_type;

class QueryResult; //为了定义函数query的返回类型，这个前向定义是必须的

class TextQuery
{
  public:
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
  private:
    std::shared_ptr<std::vector<std::string>> file; //输入文件
    std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;

};

//构造函数
TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>) //默认初始化
{
  std::string text;
  while(std::getline(is,text)) //获取文件中的每一行字符串
  {
    file->push_back(text);
    int n = file->size() - 1; //当前行号
    std::istringstream line(text); //将行文本分解为单词
    std::string word;
    while(line >> word) //每行中的单词
    {
      //如果单词不在wm中，以之为下标在wm中添加一项
      auto& lines = wm[word];
      if(!lines)
          lines.reset(new std::set<line_no>); //分配一个新set
      lines->insert(n); //将行号保存在set中
    }
  }
}

class QueryResult
{
  friend std::ostream& print(std::ostream&,const QueryResult&);
  public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f)
                : sought(s),lines(p),file(f){}
  private:
    std::string sought; //查询单词
    std::shared_ptr<std::set<line_no>> lines; //出现的行号
    std::shared_ptr<std::vector<std::string>> file; //输入文件
};

QueryResult TextQuery::query(const std::string& sought) const
{
  //如果未找到sought，返回一个指向此set的指针
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
  //如果能找到单词，打印出次数和所有出现的地方
  os << qr.sought << " occurs " << qr.lines->size() << " "
      << make_plural(qr.lines->size(),"time","s") << std::endl;
  //打印出单词出现的每一行
  for(auto num : *qr.lines)
  {
    //避免行号给用户带来困扰
    os << "\t(line " << num + 1 << ") "
        << *(qr.file->begin() + num) << std::endl;
  }
  return os;

}

void runQuery(std::ifstream& infile)
{
  TextQuery tq(infile);
  //与用户交互：提示用户输入要查询的单词，完成查询并打印结果
  while(true)
  {
    std::cout << "enter word to look for,or q to quit: ";
    std::string s;
    //若是遇到文件尾或q结束查询
    if(!(std::cin >> s) || s == "q")
      break;
    print(std::cout,tq.query(s)) << std::endl;
    
  }
}

int main(void)
{
  std::ifstream ifs;
  ifs.open("new.txt");
  runQuery(ifs);
  ifs.close();
  return EXIT_SUCCESS;
}
