#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "queryhistory.h"
#include "queryresult.h"
#include "textquery.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"
#include "notquery.h"

int main()
{
    std::ifstream fin("test.txt");
    TextQuery text(fin);
    QueryHistory history;
    Query q0("Alice");
    Query q1("hair");
    Query q2("Daddy");

    history.add_query(q0);
    history.add_query(q1);
    history[0] = history.at(0) | q2;

    auto result = history.at(0).eval(text);
    print(std::cout,result);
    fin.close();
    return 0;
}
