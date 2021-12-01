#ifndef DIVDP_HPP
#define DIVDP_HPP

#include "node.hpp"
#include <iostream>
#include <vector>
using namespace std;

class divdp
{
    private:

    public:
        divdp();
        vector<node> doDivDp(vector<node> *graph, int k);
};

#endif
