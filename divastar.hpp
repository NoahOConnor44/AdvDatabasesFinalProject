#include <iostream>
#include "node.hpp"
#include "entry.hpp"
#include "helperFunctions.hpp"
#include <vector>
// #include<bits/stdc++.h> <=== change for mac
#include <queue>
using namespace std;

#ifndef DIVASTAR_HPP
#define DIVASTAR_HPP


// Used for the max heap of entries to rank them based off the upper bound
struct CompareEntries 
{
    bool operator()(const entry& entry1,const entry& entry2) 
    {
        return entry1.upperBound < entry2.upperBound;
    }
};

class divastar
{
private:
    helperFunctions help;
    entry results;
    priority_queue<entry,vector<entry>,CompareEntries> entriesQueue; // use the priority queue STL since its the same as a max heap.
public:
    divastar();
    entry doDivAStar(vector<node> *graph, int k);
    void astarSearch(vector<node> *graph, int currentVal);
    int astarBound(vector<node> *graph, entry *entryToWorkOn, int currentVal);
};

#endif
