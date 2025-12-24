#include "textquery.h"
#include <iterator>
#include <algorithm>
#include <sstream>

// Constructor
TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>)
{
  // each line 
  std::string line;
  while(std::getline(is,line))
  {
    file->push_back(line);
    // current line index 
    int index = file->size() - 1;
    
    // for each word 
    std::istringstream lineStream(line);
    std::string word;
    while(lineStream >> word)
    {
        // fetch the smart pointer which is null when the word first time seen 
        std::shared_ptr<std::set<index_Tp>> sp_lineIndex = wm[word];

        // if null, allocate a new set to contain line indices
        if(!sp_lineIndex)
          sp_lineIndex.reset(new std::set<index_Tp>);
        
        // insert 
        sp_lineIndex->insert(index);
    }
  }
}

TextQuery::result_tuple TextQuery::query_return_tuple(const std::string& sought)
{
  // dynamically allocated set used for the word does not appear 
  static std::shared_ptr<std::set<index_Tp>> noData(new std::set<index_Tp>);

  // fetch the iterator to the matching element in the map<word,lines>
  auto iter = wm.find(sought);
  if(iter == wm.end())
    return result_tuple(sought,noData,file);
  else 
    return result_tuple(sought,iter->second,file);
}
