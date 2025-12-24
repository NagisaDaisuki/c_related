#ifndef _NOTQUERY_H
#define _NOTQUERY_H

#include <memory>
#include <string>

#include "query.h"
#include "query_base.h"
#include "textquery.h"

class QueryResult;
class TextQuery;

class NotQuery : public Query_base
{
  friend Query operator~(const Query&);
  NotQuery(const Query &q) : query(q){}
  std::string rep() const { return "~(" + query.rep() + ")"; }
  QueryResult eval(const TextQuery&) const;

  Query query;
};

inline Query operator~(const Query& operand)
{
  return std::shared_ptr<Query_base>(new NotQuery(operand));
}

#endif
