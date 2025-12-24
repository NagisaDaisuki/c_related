#ifndef _TEXT_QUERY__
#define _TEXT_QUERY__

#include "StrBlob.h"

#include <iostream>
#include <fstream>
#include <map>
#include <set>

class QueryResult;

class TextQuery
{
public:
  using line_no = StrBlob::size_type;
  TextQuery(std::ifstream &);
  QueryResult query(const std::string&) const;
private:
  StrBlob file; //创建一个vector<string>类
  std::map<std::string,std::shared_ptr<std::set<StrBlob::size_type>>> result;

};

class QueryResult
{
public:
  using ResultIter = std::set<StrBlob::size_type>::iterator;
  friend std::ostream& print(std::ostream&,const QueryResult&);
public:
  QueryResult(const std::string& s,std::shared_ptr<std::set<StrBlob::size_type>> set,
              const StrBlob& f)
              : word(s),nos(set),file(f){}
  ResultIter begin() const { return nos->begin(); }
  ResultIter end() const { return nos->end(); }
  std::shared_ptr<StrBlob> get_file() const { return std::make_shared<StrBlob>(file); }
private:
  std::string word;
  std::shared_ptr<std::set<StrBlob::size_type>> nos;
  StrBlob file;
};

std::ostream& print(std::ostream& ,const QueryResult&);

#endif
