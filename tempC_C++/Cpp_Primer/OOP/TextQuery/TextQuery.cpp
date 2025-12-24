#include "TextQuery.h"
#include "StrBlob.h"
#include <cctype>
#include <sstream>
#include <algorithm>

TextQuery::TextQuery(std::ifstream& ifs)
{
    StrBlob::size_type lineNo{0};
    for(std::string line;std::getline(ifs,line);++lineNo)
    {
      file.push_back(line); //为file添加string
      std::istringstream line_stream(line);
      for(std::string text,word;line_stream >> text;word.clear())
      {
        //avoid read a word followed by punctuation(such as : word)
        std::remove_copy_if(text.begin(),text.end(),std::back_inserter(word),ispunct);
        // unary_predicator
        // use reference avoid count of shared_ptr add
        auto &nos = result[word];
        if(!nos) nos.reset(new std::set<StrBlob::size_type>);
        nos->insert(lineNo);
      }
    }
}

QueryResult TextQuery::query(const std::string& str) const
{
    //use static just allocate once 
    static std::shared_ptr<std::set<StrBlob::size_type>> nodate(new std::set<StrBlob::size_type>);
    auto found = result.find(str);
    if(found == result.end()) return QueryResult(str,nodate,file);
    else return QueryResult(str,found->second,file);
}

std::ostream& print(std::ostream &out, const QueryResult& qr)
{
    out << qr.word << " occurs " << qr.nos->size() <<
      (qr.nos->size() > 1 ? " times" : " time") << std::endl; 
    for(auto it = qr.begin();it != qr.end();++it)
    {
        ConstStrBlobPtr p(*qr.get_file(),*it);
        out << "\t(line " << *it + 1 << ") " << p.deref() << std::endl;
    }
    return out;
}
