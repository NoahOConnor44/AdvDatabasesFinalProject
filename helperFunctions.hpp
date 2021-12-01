#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <iostream>
#include <list>
#include "node.hpp"
#include <filesystem>
#include <vector>
#include <map>
#include<stdlib.h>
#include <string>
#include <exception>
using namespace std;

class helperFunctions
{
    private:

    public:
    void topK(string filename,string query, int k);
    void score(node infoToBeScored,string query, string filename);
    void read_words_frequency_from_files(fstream &file, string file_name, std::map<string, std::map<string, std::vector<int>>> &m, std::map<std::string, int> &term_count);
    std::map<string, std::map<string, std::vector<float>>> calculate_keyword_scores(std::map<string, std::map<string, float>> &docs_similairity);
    int idf(string filename, string query);
    int count_files(string directory, string ext);
    void addEdge(list<int> adj_list[], int u, int v);
    void displayAdjList(list<int> adj_list[], int v);
    node returnNodeNum(vector<node> *graph, int nodeNum);
    vector<node> plusOperator(vector<node> searchResult1,vector<node> searchResult2);
    vector<node> crossOperator(vector<node> searchResult1,vector<node> searchResult2);
    std::map<string, float> calculate_doc_scores(std::map<string, std::map<string, std::vector<float>>> keyword_scores, string query);
};

#endif
