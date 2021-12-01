#include <iostream>
#include <string>
#include <list>
#include <filesystem>
#include "helperFunctions.hpp"
#include "divastar.hpp"
#include "node.hpp"
#include "entry.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    helperFunctions helpers;
    if(argc != 3)
    {
        cout << "To run the program: './main searchTerm kValue'\n";
        exit(1);
    }
    else
    {
        string query = argv[1];
        int k = stoi(argv[2]);

        cout << "Scoring and determing node edges for all documents in the Reuters dataset...\n";

        helperFunctions help;
        std::map<string, std::map<string, float>> docs_similairity;
        std::map<string, std::map<string, std::vector<float>>> scores = help.calculate_keyword_scores(docs_similairity);

        float similarity_threashold = 0.1;

        std::map<string, std::vector<string>> similar_edges;
        for (const auto &[doc, edges] : docs_similairity) {
            for (const auto &[edge, similairity] : docs_similairity[doc]) {
                if(similairity > similarity_threashold) {
                    similar_edges[doc].push_back(edge);
                }
            }
        }

        for (const auto &[doc, edges] : similar_edges) {
            cout << doc << " : [";
            for (const auto &edge : similar_edges[doc]) {
                cout << edge << ", " ;
            }
            cout << "]" << endl;
        }


        std::map<string, float> relevant_scored_nodes = help.calculate_doc_scores(scores, query);

        for(auto it = relevant_scored_nodes.cbegin(); it != relevant_scored_nodes.cend(); it++)
        {
            cout << it->first << "\t" << it->second << endl;
        }

        //help.topK(filename,query,k);

        vector<node> adj_list;
        string edgesFromPaper[6] = {"10 5 3 4", "8 5 3 4", "7 1 2 6", "7 1 2 6", "6 1 2 6", "1 5 3 4"};
        // make k nodes for the graph (since its a top-k result graph as input for div astar)
        // this will change from k to the # of nodes from the dataset they selected.
        for(int i = 0; i < 6; i++)
        {
            string test = edgesFromPaper[i];
            node temp = node("0",(i+1));
            adj_list.push_back(temp);
            adj_list.at(i).addEdges(test);
        }
        divastar div;
        cout << "We have one single error in div-astar search with regard to the max D.score that is stopping everything from working. To run it you uncomment the below code in main. (it will print the passed sample graph) \n";
        // 
        //auto result = div.doDivAStar(&adj_list,k);
        //auto answer = result.getSolution();
        
        //for(int i = 0; i < answer.size(); i++)
        //{
        //    cout << answer.at(i).getNodeNum() << endl;
        //}
        
        cout << "Showcasing div-astarbound working properly. As shown in the paper in figure 6 it returns the correct upper bound given node3 as the starting node. As seen below \n";
        node s;
        s.setNodeNum(3);
        s.addEdges("7 1 2 6");

        entry node3;
        node3.addSolution(s);
        node3.setScore(7);

        int upperBound = div.astarBound(&adj_list,&node3,3);
        cout << "Upper bound for the third node " << upperBound << endl;
    }
    return 0;
}
