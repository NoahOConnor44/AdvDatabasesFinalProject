#include "helperFunctions.hpp"
#include "node.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include<stdlib.h>
#include <string>
#include <list>
#include <cmath>
#include <exception>

using namespace std;
namespace fs = std::filesystem;
//namespace fs = std::__fs::filesystem; // <======================

// filename must have extension in it.
void helperFunctions::topK(string filename, string query, int k)
{
    ifstream fin;
    fin.open(filename.c_str());
    string content = "";
    double termFreq = 0;
    double idf = 0;
    double score = 0;

    // each node is a document with a the term frequency score for the query in it.
    // edges are determined via the jaccard similairity function between documents if they are similair then they are connected edges.
    if(fin.is_open())
    {
        int count = 0;
        while(getline(fin,content))
        {
            if(query == content)
            {
                termFreq++;
            }
            //node temp(content); // temp for now, use better name
            //cout << temp.getValue() << endl;
            // with each node we need to score them based off of the query term and file.
            count++;
        }
        cout << termFreq << " " << count << endl;
        idf = log((1/termFreq+1));
        termFreq = termFreq/count;
        cout << termFreq << " " << idf << endl;

        score = (termFreq * idf)/(sqrt(count));
        cout << score << endl;
    }

    // open file
    // read contents
    // build heap from file contents for use in getting top-k elements

}

void helperFunctions::read_words_frequency_from_files(fstream &file, string file_path, std::map<string, std::map<string, std::vector<int>>> &m, std::map<string, int> &term_count) {
    int index = 0;
    string word;
    while (file >> word) {

        /* cleaning data */
        word.erase(std::remove_if(word.begin(), word.end(), []( auto const& c ) -> bool { return !std::isalnum(c); } ), word.end());

        // check if word exists already in hashmap
        if (m[file_path].find(word) == m[file_path].end()) {
            std::vector<int> occurrences;
            occurrences.push_back(index);
            m[file_path][word] = occurrences;
        } else {
            m[file_path][word].push_back(index);
        }

        index++;
    }
    index++;
    term_count[file_path] = index;
}

int helperFunctions::count_files(string directory, string ext) {
	fs::path Path(directory);
	int Nb_ext = 0;
	fs::directory_iterator end_iter;

	for (fs::directory_iterator iter(Path); iter != end_iter; ++iter)
		if (iter->path().extension() == ext)
			++Nb_ext;

	return Nb_ext;
}

std::vector<std::string> keys_intersection(std::vector<std::string> &v1,
                                      std::vector<std::string> &v2){
    std::vector<std::string> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

std::vector<std::string> keys_union(std::vector<std::string> &v1,
                                      std::vector<std::string> &v2){
    std::vector<std::string> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_union(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

std::map<string, std::map<string, std::vector<float>>> helperFunctions::calculate_keyword_scores(std::map<string, std::map<string, float>> &docs_similairity) {
    std::map<string, std::map<string, std::vector<float>>> scores;
    std::map<string, std::map<string, std::vector<int>>> docs;
    try {
        string path = "./dataset/";
        /* remove existing meta data files to write new ones */
        system("rm ./dataset/*.md");

        int total_docs = count_files("./dataset/", ".txt");
        for (auto & p : fs::recursive_directory_iterator(path)) {

            fstream file;
            file.open(p.path());

            // std::map<string, std::map<string, float>> docs_similairity;
            std::map<string, int> term_count;

            auto testPath = p.path().string(); // <============ change

            read_words_frequency_from_files(file, testPath, docs, term_count);

            for (const auto &[doc, keywords] : docs) {
                ofstream metadata_file;
                metadata_file.open(doc+".md");
                for (const auto &[word, occurrences] : keywords) {
                    metadata_file << word << "," << occurrences.size() << endl;

                    float tf = ((float)docs[doc][word].size())/((float)term_count[doc]);

                    scores[doc][word].push_back(tf);

                    float idf = log(((float)total_docs)/(tf+1));

                    float score = (tf*idf)/(sqrt((float)docs[doc][word].size()));

                    scores[doc][word].push_back(idf);
                    scores[doc][word].push_back(score);
                    // cout << doc << " word: " << word << " score: " << score << endl;
                }

                metadata_file.close();
            }
        }

        for (const auto &[doc, keywords] : docs) {
            for (const auto &[edge, keywordss] : docs) {
                if(doc != edge) {

                    std::vector<string> doc_keywords;

                    doc_keywords.reserve(docs[doc].size());
                    for( auto &[key, value] : docs[doc]) {
                        doc_keywords.push_back(key);
                    }

                    std::vector<string> edge_keywords;

                    edge_keywords.reserve(docs[edge].size());
                    for( auto &[key, value] : docs[edge]) {
                        edge_keywords.push_back(key);
                    }

                    std::vector<std::string> intersection_keywords = keys_intersection(doc_keywords, edge_keywords);
                    std::vector<std::string> union_keywords = keys_union(doc_keywords, edge_keywords);

                    float similairity = ((float)intersection_keywords.size()/(float)union_keywords.size());

                    docs_similairity[doc][edge] = similairity;

                    cout << "similairity " << doc << " with " << edge << " : " << similairity << endl;
                }
            }
        }
        return scores;

    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    return scores;
}

void helperFunctions::score(node infoToBeScored, string query, string filename)
{
    int tf = 0;
    int idf = 0;
    int totalWordsInDoc = 0;


}

int helperFunctions::idf(string filename, string query)
{
    return 0;
}

void helperFunctions::addEdge(list<int> adj_list[], int u, int v)
{
   //add v into the list u, and u into list v
   adj_list[u].push_back(v);
   adj_list[v].push_back(u);
}

void helperFunctions::displayAdjList(list<int> adj_list[], int v)
{
   for(int i = 0; i<v; i++) {
      cout << i << "--->";
      list<int>::iterator it;
      for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
      {
          // print the value of the edge at the iterator.
          cout << *it << " ";
      }
      cout << endl;
   }
}

node helperFunctions::returnNodeNum(vector<node> *graph, int nodeNum)
{
    for(int i = 0; i < graph->size(); i++)
    {
        if(graph->at(i).getNodeNum() == nodeNum)
        {
            return graph->at(i);
        }
    }
    return graph->at(0);
}

std::map<string, float> helperFunctions::calculate_doc_scores(std::map<string, std::map<string, std::vector<float>>> keyword_scores, string query) {
    std::map<string, float> doc_scores;
    for (const auto &[doc, keywords] : keyword_scores) {
        if (keyword_scores[doc].find(query) != keyword_scores[doc].end()) {
            cout << "Score in " << doc << " for query " << query << " : " << keyword_scores[doc][query].back() << endl;
            doc_scores[doc] = keyword_scores[doc][query].back();
        }
    }
    return doc_scores;
}

vector<node> helperFunctions::plusOperator(vector<node> searchResult1,vector<node> searchResult2)
{
    
}

vector<node> helperFunctions::crossOperator(vector<node> searchResult1,vector<node> searchResult2)
{

}
