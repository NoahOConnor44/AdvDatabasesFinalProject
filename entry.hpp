#ifndef ENTRY_HPP
#define ENTRY_HPP
#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

class entry
{
private:
    vector<node> solutionNodes; // nodes it used for its current solution.
    int currPos = 0; // current Node its at
public:
    entry();
    int upperBound = 0; // highest score it can get from its position.
    int currScore = 0; // current score for its position
    int getUpperBound();
    void setUpperBound(int upper);
    vector<node> getSolution();
    void addSolution(node nodeToAdd);
    bool checkSolutionNodes(int nodeNum);
    int getScore();
    void setScore(int scoreToAdd);
};

#endif