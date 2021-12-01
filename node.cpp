#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "node.hpp"
using namespace std;

node::node()
{
    score = 0;
    nodeNum = 0;
}

node::node(int score, int nodeNum)
{
    this->score = score;
    this->nodeNum = nodeNum;
}

// NEED TO ADD NODE SCORE
node::node(string info, int nodeNum)
{
    value = info;
    this->nodeNum = nodeNum;
}

string node::getValue()
{
    return value;
}

void node::setScore(int score)
{
    this->score = score;
}

void node::setNodeNum(int nodeNum)
{
    this->nodeNum = nodeNum;
}

void node::setValue(string val)
{
    value = val;
}

void node::addEdges(string nodeEdges)
{
    int scoreSpaceLoc = nodeEdges.find(" "); // find the location of the first space since the score can be more than a single digit.
    string nodeScore = nodeEdges.substr(0,scoreSpaceLoc); // grab the score, its listed before the edges its connected to.
    score = stoi(nodeScore);

    nodeEdges = nodeEdges.substr(scoreSpaceLoc); // remove the score (first component) and just store the edges to be used below.

    istringstream mystream(nodeEdges);
    string connectingNode;
    while(mystream >> connectingNode) // split the connecting nodes using a space as the delimiter. (substring used because first val is its score)
    {
        edges.push_back(stoi(connectingNode)); // add the node number that it has an connection to.
    }
}

void node::printEdges()
{
    cout << "Node #" << nodeNum << " score = " << score << " edges => ";
    for(int i = 0; i < edges.size(); i++)
    {
        cout << edges.at(i) << " ";
    }
    cout << endl;
}

bool node::isInEdges(int nodeNum)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges.at(i) == nodeNum)
        {
            return true;
        }
    }
    return false;
}

int node::getNodeNum()
{
    return this->nodeNum;
}

int node::getScore()
{
    return score;
}