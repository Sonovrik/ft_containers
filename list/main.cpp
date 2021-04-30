#include "list.hpp"
#include <unistd.h>
//#include "../utils/utils.hpp"
//#include "../utils/iterators.hpp"
#include <list>

int main() {
    ft::list<int> list(10, 1234);
    list.push_back(-1);

    ft::list<int>::const_iterator it2 = list.begin();
}