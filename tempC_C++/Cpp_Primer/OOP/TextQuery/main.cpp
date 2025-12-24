#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

#include "TextQuery.h"

//QueryResult::QueryResult(const std::string& s,std::shared_ptr<std::set<StrBlob::size_type>> set,
//                        const StrBlob& f);

//抽象基类
class Query_base
{
    friend class Query;
  protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
  private:
    //eval 返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    //rep 是表示查询的一个string
    virtual std::string rep() const = 0;

};

//管理Query_base 继承体系的接口类
class Query
{
    //这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
public:
    Query(const std::string&); //构建一个新的WordQuery
    //接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery& t) const
        { return q->eval(t); }
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};

/*
    因为我们不希望用户或者派生类直接使用Query_base,所以
    它没有public成员
    因为Query要调用Query_base 的虚函数，
    所以我们将QueryResult声明成Query_base的友元

*/

//WordQuery类
/*
    一个WordQuery 查找一个给定的string，它是在给定的TextQuery对象上实际
    执行查询的唯一一个操作

    和Query_base 一样，WordQuery 没有公有成员
    同时，Query必须作为WordQuery的友元，这样Query 才能访问WordQuery 的构造函数
*/
class WordQuery : public Query_base
{
  friend class Query; //Query 使用WordQuery的构造函数
  WordQuery(const std::string &s) : query_word(s){}
  //具体的类：WordQuery将定义所有继承而来的纯虚函数
  QueryResult eval(const TextQuery& t) const
               { return t.query(query_word); }

  std::string rep() const { return query_word; }
  std::string query_word;
};

//接受WordQuery类之后，我们就能定义接受string的Query构造函数了
inline 
Query::Query(const std::string &s) : q(new WordQuery(s)){}


//NotQuery类 及 ~运算符
/*
    ~运算符生成一个NotQuery,其中保存着一个需要对其取反的Query

*/

class NotQuery : public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}
    //具体的类：NotQuery 将定义所有继承而来的纯虚函数
    std::string rep() const { return "~(" + query.rep() + ")"; } //对query的rep调用是一个虚调用
    QueryResult eval(const TextQuery&) const;
    Query query;
};


inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand)); //隐式接受一个
                                                                //shared_ptr<Query_base>的构造函数
}

//BinaryQuery类
/*
    BinaryQuery 类也是一个抽象基类，它保存操作两个运算对象的查询类型所需的数据
*/

class BinaryQuery : public Query_base 
{
  protected:
    BinaryQuery(const Query &l,const Query &r,std::string s) : lhs(l),rhs(r),opSym(s) {}
    //抽象类：BinaryQuery不定义eval
    std::string rep() const { return "()" + lhs.rep() + " "
                              + opSym + " " 
                              + rhs.rep() + ")";}
    Query lhs,rhs; //左侧和右侧运算对象
    std::string opSym; //运算符的名字
};

//AndQuery类
class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query&,const Query&);
    AndQuery(const Query &left,const Query &right) :
                              BinaryQuery(left,right,"&"){}
    //具体的类：AndQuery继承了rep并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs,const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

//OrQuery类
class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query &left,const Query &right) : 
                              BinaryQuery(left,right,"|"){}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const
{
    //通过Query成员lhs和rhs进行的虚调用
    //调用eval返回每个运算对象的QueryResult
    auto right = rhs.eval(text),left = lhs.eval(text);
    //将左侧运算对象的行号拷贝到结果set中
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(),left.end());
    //插入右侧对象所得的行号
    ret_lines->insert(right.begin(),right.end());
    //返回一个新的QueryResult,它表示lhs和rhs的并集
    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const
{
    //通过Query运算对象进行的虚调用以获得运算对象的查询结果set
    auto left = lhs.eval(text),right = rhs.eval(text);
    //保存left和right的交集set
    auto ret_lines = std::make_shared<std::set<line_no>>();
    //将两个范围的交集写入一个目的迭代器中
    std::set_intersection(left.begin(),left.end(),
                          right.begin(),right.end(),
                          std::inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const
{
    //通过Query运算对象对eval进行虚调用
    auto result = query.eval(text);
    //开始时结果set为空
    auto ret_lines = std::make_shared<std::set<line_no>>();
    //我们必须在运算对象出现的所有行中进行迭代
    auto beg = result.begin(),end = result.end();
    //对于输入文件的每一行，如果该行不在result中，则将其添加到ret_lines
    auto sz = result.get_file()->size();
    for(size_t n = 0;n != sz;++n)
    {
      //如果我们还没有处理完result的所有行
      //检查当前行是否存在
      if(beg == end || *beg != n)
        ret_lines->insert(n); //如果不在result当中，添加这一行
      else if(beg != end)
        ++beg; //否则在到达最后一行之前继续获取下一行
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}




