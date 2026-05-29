    #pragma once
#include <bits/stdc++.h>

#include "Driver.hpp"
#include "PackageTracker.hpp"
#include "DeliveryInfo.hpp"
#include "Zipcode.hpp"
#include "CityMap.hpp"
using namespace std;

int findNearestDriver(string packageLocation, vector<Driver>& drivers, CityGraph& cityMap){
    if (drivers.empty()) {
        cout << "No drivers are currently working!" << endl;
        return -1;
    }

    int minDistance = 9999;
    int bestDriverIndex = -1;
    
    

    cout << "\nScanning for nearest driver to " << packageLocation << "..." << endl;

    for (int i = 0; i < drivers.size(); i++) {
        
        int dist = cityMap.BFS_route(drivers[i].Location, packageLocation);
        
        cout << "--> " << drivers[i].name << " is " << dist << " stops away.\n" << endl;

        if (dist < minDistance) {
            minDistance = dist;
            bestDriverIndex = i;
        }
    }

    return bestDriverIndex;
}