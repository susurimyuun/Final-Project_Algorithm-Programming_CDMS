#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "findNearestDriver.hpp"
#include "Driver.hpp"
#include "PackageTracker.hpp"
#include "DeliveryInfo.hpp"
#include "CityMap.hpp"

class CityGraph {
private:
    map<string,list<string>> adj; 

public:

    void addRoad(string from,string to) {
        adj[from].push_back({to});
        adj[to].push_back({from});
    }


    int BFS_route(string startLoc, string endLoc){
        queue<string> q;
        set<string> visited;
        map<string,string> parentNode;

        q.push(startLoc);
        visited.insert(startLoc);
        bool found = false;

        while(!q.empty()){
            string curr = q.front();
            q.pop();

            if(curr == endLoc){
                found = true;
                break;
            }
            for(string neighbor: adj[curr]){
                if(visited.find(neighbor) == visited.end()){
                    visited.insert(neighbor);
                    parentNode[neighbor] = curr;
                    q.push(neighbor);
                }
            }
        }
        if (found){
            vector<string> path;
            string step = endLoc;
            while (step != startLoc){
                path.push_back(step);
                step = parentNode[step];
            }
            path.push_back(startLoc);
            reverse(path.begin(),path.end());

            cout << "Fastest Route Found!: ";
            for (int i = 0; i < path.size();i++){
                cout << path[i] << (i == path.size() - 1? " " : " -> ");
            }   
            cout << endl;
            return path.size()-1;

        }
        return 9999;

    }
    void PrintAdjacencyList() {
    cout << "\n=== Current City Map (Adjacency List) ===" << endl;
    
    for (const auto& cityPair : adj) {
        
        string city = cityPair.first; 
        
        list<string> neighbors = cityPair.second; 

        cout << city << " -> [ ";
        
        for (const string& neighbor : neighbors) {
            cout << neighbor << " ";
        }
        
        cout << "]" << endl;
    }
    cout << "=========================================\n" << endl;
    }
};