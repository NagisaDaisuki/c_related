#ifndef _ANDQUERY_H
#define _ANDQUERY_H

#include <memory>

#include "query.h"
#include "binaryquery.h"

class QueryResult;
class TextQuery;

class AndQuery : public BinaryQuery
{
  friend Query operator&(const Query&,const Query&);
  AndQuery(const Query& left,const Query& right) : BinaryQuery(left,right,"&"){}
  QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

#endif
