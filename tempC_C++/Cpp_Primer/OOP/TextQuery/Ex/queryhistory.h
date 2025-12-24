#ifndef _QUERYHISTORY_H
#define _QUERYHISTORY_H

#include <memory>
#include <vector>

#include "query.h"

class QueryHistory 
{
  public:
    Query& operator[](size_t n){ return *(query_vec[n]); }
    Query& at(size_t n) { return *(query_vec[n]); }

    size_t add_query(const Query&);

  private:
    std::vector<std::shared_ptr<Query>> query_vec;
};

#endif
