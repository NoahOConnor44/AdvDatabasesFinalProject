#include <iostream>
#include "divcut.hpp"
#include "divastar.hpp"
#include "helperFunctions.hpp"

divcut::divcut()
{
    
}

vector<node> divcut::doDivCut(vector<node> *graph, int k)
{
    /*
    helperFunctions help;
    divastar astar;
    vector<node> result;
    vector<vector <node>> connectedComponents;

    for(int i = 0; i < connectedComponents.size(); i++)
    {
        vector<node> temp = connectedComponents.at(i);
        cpCompress(temp);
         if(cutPoints(temp) == NULL)
         {
            vector<int> result2 = astar.doDivAStar(&temp,k);
         }
         else
         {
            auto o = cpTreeConstruct(temp, cutPoints(temp));
            cpSearch(temp,o,k);
            vector<int> result2 = help.crossOperator(o.getResultZero(),o.getResultOne());
         }
         result = help.plusOperator(result,result2);
        
        return result;
        
    }
    */
}