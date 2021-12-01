#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <vector>
using namespace std;

class node
{
private:
    string value = "";
    int nodeNum = 0;
    int score = 0;
    vector<int> edges;
public:
    node();
    node(int score, int nodeNum);
    node(string value, int nodeNum);
    string getValue();
    void setValue(string val);
    void setScore(int score);
    void setNodeNum(int nodeNum);
    void addEdges(string edgeNodes);
    void printEdges();
    bool isInEdges(int nodeNum);
    int getNodeNum();
    int getScore();
};

#endif