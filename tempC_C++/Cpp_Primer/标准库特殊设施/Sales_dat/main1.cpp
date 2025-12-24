#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#include "Sales_data.h"

typedef std::tuple<std::vector<Sales_data>::size_type,
              std::vector<Sales_data>::const_iterator,
              std::vector<Sales_data>::const_iterator> matches;

typedef std::pair<std::vector<Sales_data>::size_type,
              std::pair<std::vector<Sales_data>::const_iterator,
              std::vector<Sales_data>::const_iterator>> matches_pair;

struct matches_struct
{
  std::vector<Sales_data>::size_type st;
  std::vector<Sales_data>::const_iterator first;
  std::vector<Sales_data>::const_iterator last;
  matches_struct(std::vector<Sales_data>::size_type s,
                std::vector<Sales_data>::const_iterator f,
                std::vector<Sales_data>::const_iterator l)
        : st(s),first(f),last(l){}
};

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>>& files,
      const std::string& book)
{
  std::vector<matches> ret;
  
  // for_each 
  for(auto it = files.cbegin();it != files.cend();++it)
  {
    auto found = std::equal_range(it->cbegin(),it->cend(),book,compareIsbn);
    if(found.first != found.second)
      ret.push_back(std::make_tuple(it - files.cbegin(),found.first,found.second));
  }
  return ret;
}

void reportResults(std::istream& in,std::ostream& os,
                const std::vector<std::vector<Sales_data>>& files)
{
  std::string s;
  while(in >> s)
  {
    auto trans = findBook(files,s);
    if(trans.empty())
    {
      std::cout << s << "not found in any stores" << std::endl;
      continue;
    }

    for(const auto& store : trans)
    {
      os << "store " << std::get<0>(store) << " sales: "
        << std::accumulate(std::get<1>(store),std::get<2>(store),Sales_data(s))
        << std::endl;
    }

  }
}

std::vector<matches_pair>
findBook_pair(const std::vector<std::vector<Sales_data>> &files,
            const std::string &book)
{
  std::vector<matches_pair> ret;
  for(auto it = files.cbegin();it != files.cend();it++)
  {
    auto found = std::equal_range(it->cbegin(),it->cend(),book,compareIsbn);
    if(found.first != found.second)
      ret.push_back(std::make_pair(it - files.cbegin(),std::make_pair(found.first,found.second)));
  }
  return ret;
}

std::vector<matches_struct>
findBook_struct(const std::vector<std::vector<Sales_data>> &files,
                const std::string& book)
{
  std::vector<matches_struct> ret;
  for(auto it = files.cbegin();it != files.cend();it++)
  {
    auto found = std::equal_range(it->cbegin(),it->cend(),book,compareIsbn);
    if(found.first != found.second)
      ret.push_back(matches_struct(it - files.cbegin(),found.first,found.second));
  }
  return ret;
}
