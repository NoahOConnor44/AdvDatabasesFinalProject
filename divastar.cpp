#include "divastar.hpp"
#include "entry.hpp"
#include <iostream>
#include <vector>

using namespace std;

// adds a vector of a single node to the results list so its not empty to start and doesnt throw an out of bounds error.
divastar::divastar()
{

}

// Pass the graph and the top k value they want from the graph.
entry divastar::doDivAStar(vector<node> *graph, int k)
{
    for(int i = 0; i < graph->size(); i++)
    {
        node temp = graph->at(i);
        temp.printEdges();
    }
    
    vector<node> result; // Stores the nodes, their score, upper bound  // this may be useless. probably will just pop the heap at the end I think.
    vector<entry> allEntries; // stores all entries as it grows.
    
    entry start; // starting entry point for the heap (empty values)
    entriesQueue.push(start); // to start the max heap is empty with no values    
    for(int i = k; i >= 1; i--)
    {
        astarSearch(graph,i);
        for(int j = 0; j < entriesQueue.size(); j++)
        {
            allEntries.push_back(entriesQueue.top()); // store the entries in a vector since can iterate through max heap natively.
            entry currEntry = entriesQueue.top(); // store the current entry so its easy to pass
            int newUpperBound = astarBound(graph,&currEntry,i); // calculate the new upper bound of this entry in the graph.
            currEntry.setUpperBound(newUpperBound); // update the new bound
            entriesQueue.pop(); // pop the "old" entry  off the heap.
            entriesQueue.push(currEntry); // add the "updated" entry back to the heap
        }
    }
    return results; // the highest scoring entry with non adjacent nodes.
}

void divastar::astarSearch(vector<node> *graph, int currentVal)
{
    bool isFirstRun = true;
    while (((entriesQueue.empty() == false) && (entriesQueue.top().upperBound > results.getScore())) || isFirstRun == true)
    {
        entry curr = entriesQueue.top(); // pop the entry with the highest upper bound (top() is used since pop() doesnt return anything);
        entriesQueue.pop(); // Once we have the top entry, pop it.
        node position; // Grab the last added node in the solution for the entry. (if its first run first node is returned)
        
        if(curr.getSolution().empty())
        {
            position = graph->at(0);
        }
        else
        {
            position = curr.getSolution().back();
        }

        int newPosition = position.getNodeNum()+1;

        for(int i = newPosition; i <= graph->size(); i++)
        {
            node checking = graph->at(i-1);
            bool isAdjacent = true;

            vector<node> currSolutions = curr.getSolution(); // return node #'s that are part of the entry's solution i.e.: "1,4,5"
            // check the current solutions and make sure the new node isnt part of it already
            for(int j = 0; j < currSolutions.size(); j++)
            {
                node oneAnswerNode = currSolutions.at(j);
                isAdjacent = oneAnswerNode.isInEdges(checking.getNodeNum());
                if(isAdjacent) break;
            }

            if(!isAdjacent)
            {
                curr.addSolution(checking); // add the new node to the current entry solution 
                curr.setScore(checking.getScore()); // add the nodes score to the current entries solution score.
                int newBound = astarBound(graph, &curr, currentVal);
                curr.setUpperBound(newBound);
                entriesQueue.push(curr); // add the "new" solution to the heap

                if((results.getScore() < curr.getScore()) || isFirstRun == true)
                {
                    results = curr;
                }
            }
        }
        isFirstRun = false;
    }
}

/*
Newly added nodes should at least satisfy the following two conditions: 
    - 1) they can not be one of e.solution
    - 2) they are not adjacent to any node in e.solution. 
Under such conditions, we can just add the set of nodes with largest scores, and after adding the nodes, the total number of nodes is no larger than k'.
*/
int divastar::astarBound(vector<node> *graph, entry *entryToWorkOn, int currentVal)
{ 
    vector<node> solutionsForEntry = entryToWorkOn->getSolution(); 
    int solSize = solutionsForEntry.size(); // get the cardinality of the solution set for the current entry
    cout << "current solution size: " << solSize << endl;
    
    node lastVisitedNode = solutionsForEntry.back(); // return the last visited node so we know where to continue from
    int i = lastVisitedNode.getNodeNum()+1; // new starting position to explore to find new upper bound for the entry.
    cout << "next position: " << i << endl;

    int bound = entryToWorkOn->getScore(); // store the current upper bound for the entry.
    
    bool isAdjacent = true;

    while((solSize < currentVal) && (i <= graph->size()))
    {
        node checking = graph->at(i-1); // node number so -1 to get index.

        vector<node> currSolutions = entryToWorkOn->getSolution();
        // check the current solutions and make sure the new node isnt part of it already
        for(int a = 0; a < currSolutions.size(); a++)
        {
            node oneAnswerNode = currSolutions.at(a);
            isAdjacent = oneAnswerNode.isInEdges(checking.getNodeNum());
            if(isAdjacent) break;
        }
        // if it breaks from the above loop because one of the nodes is adjacent to one in the solution then this wont run and it will move on to the next node in the graph. only way this runs is if isAdjacent is false the whole time.
        if(!isAdjacent)
        {
            cout << "upper bound if node(s) was added to the current solution \n";
            bound = bound + checking.getScore(); // update the bound by adding  the score of the new node.
            solSize = solSize+1;
        }
        i = i+1;
    }
    return bound;
}