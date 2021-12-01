#include <iostream>
#include <vector>
#include "entry.hpp"
using namespace std;

// LOOK AT
entry::entry()
{
    
}

int entry::getUpperBound()
{
    return upperBound;
}

void entry::setUpperBound(int upper)
{
    upperBound = upper;
}

vector<node> entry::getSolution()
{
    return solutionNodes;
}

void entry::addSolution(node nodeToAdd)
{
    solutionNodes.push_back(nodeToAdd);
}

bool entry::checkSolutionNodes(int nodeNum)
{
    for(int i = 0; i < solutionNodes.size(); i++)
    {
        node temp = solutionNodes.at(i);
        if(temp.getNodeNum() == nodeNum)
        {
            return true;
        }
    }
    return false;
}

int entry::getScore()
{
    return currScore;
}


void entry::setScore(int scoreToAdd)
{
    currScore = currScore+scoreToAdd;
}