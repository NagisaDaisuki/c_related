#include "queryhistory.h"

size_t QueryHistory::add_query(const Query& q)
{
    std::shared_ptr<Query> p = std::make_shared<Query>(q);
    query_vec.push_back(p);
    return query_vec.size() - 1;
}
