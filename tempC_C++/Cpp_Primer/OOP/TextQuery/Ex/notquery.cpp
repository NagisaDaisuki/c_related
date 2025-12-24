#include "notquery.h"

#include <memory>
#include <set>

#include "queryresult.h"
#include "textquery.h"
#include "query.h"

QueryResult NotQuery::eval(const TextQuery& text) const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    auto beg = result.begin();
    auto end = result.end();
    auto sz = result.get_file()->size();
    
    for(size_t n = 0;n != sz;++n)
    {
      if(beg == end || *beg != n)
        ret_lines->insert(n);
      else if(beg != end)
        ++beg;
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}
