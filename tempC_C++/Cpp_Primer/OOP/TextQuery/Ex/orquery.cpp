#include "orquery.h"

#include <memory>
#include <set>

#include "queryresult.h"
#include "textquery.h"
#include "query.h"

QueryResult 
OrQuery::eval(const TextQuery &text) const 
{
    auto right = rhs.eval(text);
    auto left = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),right.end());
    return QueryResult(rep(),ret_lines,left.get_file());
}
