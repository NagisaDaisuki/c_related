#include "textquery.h"
#include "queryresult.h"
#include <sstream>

TextQuery::TextQuery(std::ifstream& ifs) : file(new std::vector<std::string>())
{
    std::string text;
    while(std::getline(ifs,text))
    {
      file->push_back(text);
      int n = file->size() - 1;
      std::string word;
      std::istringstream iss(text);
      while(iss >> word)
      {
          auto p = handlePunct(word); //处理word中的标点,以标点分割成几个word
          for(auto &w : *p)
          {
              auto& result = wm[w];
              if(!result)
                result.reset(new std::set<line_no>());
              result->insert(n);
          }
      }
    }
}

QueryResult TextQuery::query(const std::string &s) const 
{
    static std::shared_ptr<std::set<line_no>> no_date(new std::set<line_no>());

    auto res = wm.find(s);
    if(res == wm.end())
      return QueryResult(s,no_date,file);
    else 
      return QueryResult(s,res->second,file);

}


std::shared_ptr<std::vector<std::string>> TextQuery::handlePunct(const std::string& s)
{
  std::shared_ptr<std::vector<std::string>> p = 
    std::make_shared<std::vector<std::string>>();
  size_t first = 0,index = 0;
  while(index != s.size())
  {
    if(ispunct(s[index]))
    {
      std::string word = s.substr(first,index - first);
      if(!word.empty())
        p->push_back(word);
      ++index;
      first = index;
    }
    else
      ++index;
  }
  std::string trail = s.substr(first);
  if(!trail.empty())
    p->push_back(trail);

  return p;

}

