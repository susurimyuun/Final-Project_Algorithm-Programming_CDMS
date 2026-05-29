#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "findNearestDriver.hpp"
#include "PackageTracker.hpp"
#include "DeliveryInfo.hpp"
#include "Zipcode.hpp"
#include "CityMap.hpp"
struct Driver {

    string name;
    int completedDeliveries;
    string Location;
};

// compare deliveries
bool compareDriver(Driver a, Driver b) {

    return a.completedDeliveries > b.completedDeliveries;
}

// display ranking
void showDriverRanking(vector<Driver>& drivers) {

    sort(drivers.begin(), drivers.end(), compareDriver);

    cout << "\n========== DRIVER RANKING ==========\n";

    for (int i = 0; i < drivers.size(); i++) {

        cout << i + 1 << ". "
             << drivers[i].name
             << " - Completed Deliveries : "
             << drivers[i].completedDeliveries
             << endl;
    }
}