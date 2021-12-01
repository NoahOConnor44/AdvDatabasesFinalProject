#ifndef DIVCUT_HPP
#define DIVCUT_HPP

#include "node.hpp"
#include <iostream>
#include <vector>
using namespace std;

class divcut
{
    private:

    public:
        divcut();
        vector<node> doDivCut(vector<node> *graph, int k);
};

#endif
