#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric> 

#include "Sales_data.h"

// for ex17.4
typedef std::tuple<std::vector<Sales_data>::size_type,
                  std::vector<Sales_data>::const_iterator,
                  std::vector<Sales_data>::const_iterator> matches;
// for ex17.5 
// return a pair that holds an index and a pair of iterators
typedef std::pair<std::vector<Sales_data>::size_type,
                  std::pair<std::vector<Sales_data>::const_iterator,
                    std::vector<Sales_data>::const_iterator>> matches_pair;

// for ex17.6

struct matches_struct 
{
  typedef std::vector<Sales_data>::size_type m_st;
  typedef std::vector<Sales_data>::const_iterator m_c_iter;
  m_st st;
  m_c_iter first;
  m_c_iter last;
  matches_struct(m_st s,m_c_iter f,m_c_iter l):
                st(s),first(f),last(l){}
};

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>>& files,
          const std::string& book);

// print the result using the given iostream 
void reportResults(std::istream& in,std::ostream& os,
                const std::vector<std::vector<Sales_data>>& files);

// for ex17.5 
// return a vector with an entry for each store that sold the given book 
std::vector<matches_pair>
findBook_Pair(const std::vector<std::vector<Sales_data>>& files,
              const std::string &book);


// for ex17.6
// return a vector with an entry for each store that sold the given book 
std::vector<matches_struct>
findBook_struct(const std::vector<std::vector<Sales_data>>& files,
                const std::string& book);

int main()
{
  return 0;
}

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>>& files,
          const std::string& book)
{
  std::vector<matches> ret;
  for(auto it = files.cbegin();it != files.cend();it++)
  {
    // find the range of Sales_data that have the same ISBN 
    auto found = std::equal_range(it->cbegin(),it->cend(),book,compareIsbn);
    if(found.first != found.second)
      ret.push_back(std::make_tuple(it - files.cbegin(),found.first,found.second));
  }
  return ret;
}

// for ex17.4 
void reportResults(std::istream& in,std::ostream& os,
                const std::vector<std::vector<Sales_data>>& files)
{
  std::string s;
  while(in >> s)
  {
    auto trans = findBook(files,s);
    if(trans.empty())
    {
      std::cout << s << " not found in any stores" << std::endl;
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

// for ex17.5 
// return a vector with an entry for each store that sold the given book
std::vector<matches_pair>
findBook_pair(const std::vector<std::vector<Sales_data>>& files,
              const std::string& book)
{
  std::vector<matches_pair> result;
  
  for(auto it = files.cbegin();it != files.cend();it++)
  {
    auto found = std::equal_range(it->cbegin(),it->cend(),book,compareIsbn);
    if(found.first != found.second)
      result.push_back(std::make_pair(it - files.cbegin(),
            std::make_pair(found.first,found.second)));
  }
  return result;
}

// for ex17.6
// return a vector with an entry for each store that sold the given book 
std::vector<matches_struct>
findBook_struct(const std::vector<std::vector<Sales_data>>& files,
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







