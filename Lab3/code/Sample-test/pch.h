//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <conio.h>
#include <map>


class Graph
{
public:
    Graph(std::vector<std::string> words)
    {

        int location = 0;
        for (int i = 0; i < words.size(); i++)
        {
            // std::string word = words[i];
            if (nodes.find(words[i]) == nodes.end())
            {
                nodes[words[i]] = location;
                location++;
            }
        }


        adj.resize(nodes.size());


        for (int i = 0; i < words.size() - 1; i++)
        {
            std::string word1 = words[i];
            int j = i + 1;
            std::string word2 = words[j];
            int w = 1; 
            for (int k = j; k < words.size() - 1; k++)
            {
                if (words[k] == word1 && words[k + 1] == word2)
                    w++;
            }

            int in = 0;
            for (auto& p : adj[nodes[word1]])
            {
                if (p.first == nodes[word2])
                    in = 1;
            }
            if (!in)
                adj[nodes[word1]].push_back({ nodes[word2], w });
        }

    };


    std::vector<std::string> words;
    std::unordered_map<std::string, int> nodes;
    std::vector<std::vector<std::pair<int, int>>> adj;


   


    void try_showDirectedGraph()
    {
        showDirectedGraph();
    }


    void try_queryBridgeWords()
    {
        std::cout << "plz input word1 and word2 toget BridgeWords" << std::endl;
        std::string word1, word2;
        std::cin >> word1 >> word2;
        queryBridgeWords(word1, word2);
    }


    void try_generateNewText()
    {
        getchar();
        std::cout << "plz input a text toget generateNewText" << std::endl;
        std::string text;
        getline(std::cin, text);
        std::string newtext = generateNewText(text);
    }


    void try_calcShortestPath()
    {
        getchar();
        std::cout << "plz input 1 or 2 words toget shortestPath " << std::endl;
        std::string input;
        getline(std::cin, input);
        std::string token = "";
        std::vector<std::string> tokens = {};
        for (char c : input)
        {
            if (c == ' ')
            {
                tokens.push_back(token);
                token = "";
            }
            else
            {
                if (c >= 'a' && c <= 'z')
                    token += c;
                else if (c >= 'A' && c <= 'Z')
                    token += (c + 'a' - 'A');
            }
        }
        tokens.push_back(token);
        if (tokens.size() - 1)
            if (tokens.size() - 2)
                std::cout << "Invalid input." << std::endl;
            else
            {
                std::string start = tokens[0];
                std::string end = tokens[1];
                if ((nodes.find(start) == nodes.end()) &&
                    nodes.find(end) == nodes.end())
                {
                    std::cerr << "No \"" << start << "\" and \"" << end << "\" in the graph!" << std::endl;
                    return;
                }
                else if (nodes.find(start) == nodes.end())
                {
                    std::cerr << "No \"" << start << "\" in the graph!" << std::endl;
                    return;
                }
                else if (nodes.find(end) == nodes.end())
                {
                    std::cerr << "No \"" << end << "\" in the graph!" << std::endl;
                    return;
                }
                std::cout << "Shortest paths from " << tokens[0] << ":" << std::endl;
                calcShortestPath(tokens[0], tokens[1]);
            }
        else
        {
            for (const auto& node : nodes)
            {
                {
                    if (nodes.find(tokens[0]) == nodes.end())
                    {
                        std::cerr << "No \"" << tokens[0] << "\" in the graph!" << std::endl;
                        return;
                    }
                    calcShortestPath(tokens[0], node.first);
                }
            }
        }
    }


    void try_randomWalk()
    {
        std::vector<std::string> randomwalk = randomWalk();
        std::cout << "randomWalk finished" << std::endl;
    }


    void print()
    {
        std::cout << "Nodes:" << std::endl;
        for (auto& p : nodes)
        {
            std::cout << p.first << " ";
        }
        std::cout << std::endl;

        std::cout << "Adjacency List:" << std::endl;
        for (int i = 0; i < adj.size(); ++i)
        {
            std::cout << i << " -> ";
            for (auto& p : adj[i])
            {
                std::cout << "(" << p.first << ", " << p.second << ") ";
            }
            std::cout << std::endl;
        }
    }


    void showDirectedGraph()
    {


        std::ofstream dot_file("graph.dot");
        if (dot_file.is_open())
        {

            dot_file << "digraph G {" << std::endl;


            for (const auto& pair : nodes)
            {
                dot_file << pair.second << " [label=\"" << pair.first << "\"]" << std::endl;
            }
            dot_file << std::endl;

            for (int i = 0; i < adj.size(); ++i)
            {
                for (auto& p : adj[i])
                {
                    dot_file << i << " -> " << p.first << " [label=\"" << p.second << "\"]" << std::endl;
                }
            }

            dot_file << "}" << std::endl;
            dot_file.close();


            std::system("dot -Tpng graph.dot -o graph.png");
            std::cout << "graph.png Saved" << std::endl;
        }
        else
        {
            std::cerr << "failed to write in DOT" << std::endl;
            exit(1);
        }
    }


    std::vector<std::string> queryBridgeWords(std::string word1, std::string word2, int if_print = 1)
    {
        std::vector<std::string> bridgewords = {};
        if (if_print)
            if ((nodes.find(word1) == nodes.end()) &&
                nodes.find(word2) == nodes.end())
            {
                std::cerr << "No \"" << word1 << "\" and \"" << word2 << "\" in the graph!" << std::endl;
                return bridgewords;
            }
            else if (nodes.find(word1) == nodes.end())
            {
                std::cerr << "No \"" << word1 << "\" in the graph!" << std::endl;
                return bridgewords;
            }
            else if (nodes.find(word2) == nodes.end())
            {
                std::cerr << "No \"" << word2 << "\" in the graph!" << std::endl;
                return bridgewords;
            }
        for (auto& w1 : nodes)
        {
            if (word1 == w1.first)
            {
                for (auto& w2 : adj[w1.second])
                    for (auto& w3 : adj[w2.first])
                        if (nodes[word2] == w3.first)
                            for (auto& bridge : nodes)
                                if (bridge.second == w2.first)
                                    bridgewords.push_back(bridge.first);
            }
        }
        if (if_print)
            if (bridgewords.size() == 0)
            {
                std::cerr << "No bridge words from \"" << word1 << "\" to \"" << word2 << "\"!" << std::endl;
                return bridgewords;
            }
            else if (bridgewords.size() == 1)
            {
                std::cout << "The bridge words from \"" << word1 << "\" to \"" << word2 << "\" is:" << bridgewords[0] << std::endl;
            }
            else
            {
                std::cout << "The bridge words from \"" << word1 << "\" to \"" << word2 << "\" are:" << bridgewords[0] << std::endl;
                for (auto first = bridgewords.begin() + 1; first != bridgewords.end() - 1; first++)
                {
                    std::cout << " , " << *first;
                }
                std::cout << " and " << bridgewords[bridgewords.size() - 1] << std::endl;
            }
        return bridgewords;
    }


    std::string generateNewText(std::string inputText)
    {
        std::string text2word = "";
        std::vector<std::string> text2words = {};
        for (char c : inputText)
        {
            if (c == ' ')
            {
                text2words.push_back(text2word);
                text2word = "";
            }
            else
                text2word += c;
        }
        text2words.push_back(text2word);
        std::vector<std::string> lowers(text2words);
        for (auto it = lowers.begin(); it != lowers.end() && !it->empty(); ++it)
        {
            for (auto t2 = it->begin(); t2 != it->end(); t2++)
            {
                *t2 = tolower(*t2);
            }
        }
        int if_print = 0;
        std::string newtext;
        for (int i = 0; i < text2words.size() - 1; i++)
        {
            newtext += text2words[i] + " ";
            if (queryBridgeWords(lowers[i], lowers[i + 1], if_print).size() != 0)
                newtext += queryBridgeWords(lowers[i], lowers[i + 1], if_print)[0] + " ";
        }
        newtext += text2words[text2words.size() - 1];
        std::cout << newtext << std::endl;
        return newtext;
    }


    std::vector<std::string> calcShortestPath(std::string start, std::string end)
    {
        if ((nodes.find(start) == nodes.end()) &&
            nodes.find(end) == nodes.end())
        {
            std::cerr << "No \"" << start << "\" and \"" << end << "\" in the graph!" << std::endl;
            return {};
        }
        else if (nodes.find(start) == nodes.end())
        {
            std::cerr << "No \"" << start << "\" in the graph!" << std::endl;
            return {};
        }
        else if (nodes.find(end) == nodes.end())
        {
            std::cerr << "No \"" << end << "\" in the graph!" << std::endl;
            return {};
        }


        std::vector<int> dist(adj.size(), INT_MAX);

        std::vector<std::string> prev(adj.size(), "");

        std::priority_queue<std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<std::pair<int, std::string>>>
            pq;



        dist[nodes[start]] = 0;

        pq.push({ 0, start });
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();


            if (d > dist[nodes[u]])
                continue;


            for (auto [v, w] : adj[nodes[u]])
            {

                for (auto& p : nodes)
                    if (d + w < dist[v])
                    {
                        dist[v] = d + w;
                        prev[v] = u;
                        std::string word;
                        for (auto& p : nodes)
                            if (p.second == v)
                                word = p.first;
                        pq.push({ dist[v], word });
                    }
            }
        }


        if (dist[nodes[end]] == INT_MAX)
        {
            std::cout << "The two nodes are not reachable." << std::endl;
            return {};
        }

        std::vector<std::string> path;
        std::string current = end;

        int length = INT_MAX;
        if (start == end)
        {
            for (int i = 0; i < nodes.size(); i++)
                for (auto& p : adj[i])
                {
                    if (p.first == nodes[start])
                        length = std::min(length, p.second + dist[i]);
                }

            dist[nodes[start]] = INT_MAX;
            for (auto& p : adj[nodes[start]])
            {
                // std::cout << "{" << p.first << "," << p.second << "}" << std::endl;
                if (p.first == nodes[start])
                {
                    dist[nodes[start]] = std::min(p.second, dist[nodes[start]]);
                    // std::cout<<dist[nodes[start]]<<std::endl;
                }
            }
            // std::cout<<dist[nodes[start]]<<std::endl;
            if (length == INT_MAX && dist[nodes[start]] == INT_MAX)
            {
                std::cout << "The two nodes are not reachable." << std::endl;
                return {};
            }

            // std::cout << length << "," << dist[nodes[start]] << std::endl;

            if (length <= dist[nodes[start]])
            {
                int count;
                for (int i = 0; i < nodes.size(); i++)
                    for (auto& p : adj[i])
                        if (p.first == nodes[start] && (p.second + dist[i]) == length)
                            count = i;
                for (auto& p : nodes)
                    if (p.second == count)
                        current = p.first;
                std::cout << current << std::endl;
                while (current != "")
                {
                    path.push_back(current);
                    // std::cout << path[0] << std::endl;
                    current = prev[nodes[current]];
                    // std::cout << current << std::endl;
                }
                reverse(path.begin(), path.end());
                // std::cout << path[1] << std::endl;
                dist[nodes[start]] = length;

                std::cout << "Shortest path: ";
                for (auto p = path.begin(); p != path.end(); p++)
                {
                    std::cout << *p << "->";
                }
                std::cout << end << std::endl;
                std::cout << "Length: " << dist[nodes[end]] << std::endl;
            }
            else
            {
                path.push_back(start);
                length = dist[nodes[start]];
                std::cout << "Shortest path: ";
                for (auto p = path.begin(); p != path.end() - 1; p++)
                {
                    std::cout << *p << "->";
                }
                std::cout << end << std::endl;
                std::cout << "Length: " << dist[nodes[end]] << std::endl;
            }
            // path.push_back(start);
        }
        else
        {
            while (current != "")
            {
                path.push_back(current);
                current = prev[nodes[current]];
            }
            reverse(path.begin(), path.end());
            std::cout << "Shortest path: ";
            for (auto p = path.begin(); p != path.end() - 1; p++)
            {
                std::cout << *p << "->";
            }
            std::cout << end << std::endl;
            std::cout << "Length: " << dist[nodes[end]] << std::endl;
        }



        return path;
    }


    std::vector<std::string> randomWalk()
    {
        srand(0);
        std::vector<std::string> path = {};
        std::string start;
        int randnum = rand() % nodes.size();
        for (auto& p : nodes)
            if (p.second == randnum)
                start = p.first;
        int prve = nodes[start];
        int next;
        std::vector<std::vector<int>> mark(nodes.size(), std::vector<int>(nodes.size(), 0));
        std::cout << "Func has run \"" << path.size() + 1 << "\" times" << std::endl;
        std::cout << "press 'ESC' to break this Func or press any other key to continue" << std::endl;
        while (_getch() != 27)
        {
            if (adj[prve].size() == 0)
            {
                break;
            }
            else
            {
                next = adj[prve][rand() % adj[prve].size()].first;
                if (!mark[prve][next])
                {
                    mark[prve][next] = 1;
                    for (auto& p : nodes)
                        if (p.second == prve)
                            path.push_back(p.first);
                    prve = next;
                }
                else
                {
                    for (auto& p : nodes)
                        if (p.second == prve)
                            path.push_back(p.first);
                    prve = next;
                    break;
                }
            }
            std::cout << "Func has run \"" << path.size() + 1 << "\" times" << std::endl;
        }

        for (auto& p : nodes)
            if (p.second == prve)
                path.push_back(p.first);

        std::ofstream output("output.txt");
        if (output.is_open())
        {
            for (int i = 0; i < path.size() - 1; i++)
            {
                output << path[i] << " ";
            }
            output << path[path.size() - 1];
        }
        return path;
    }
};
