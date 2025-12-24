#include "query.h"

#include <ostream>

std::ostream& 
operator<<(std::ostream &os,const Query &query)
{
    return os << query.rep();
}
