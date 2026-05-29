#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "findNearestDriver.hpp"
#include "Driver.hpp"
#include "PackageTracker.hpp"
#include "Zipcode.hpp"
#include "CityMap.hpp"
struct DeliveryInfo{
    int PackageID;
    int TimeStamp;
    string Status;
    string Location;

    DeliveryInfo* left;
    DeliveryInfo* right;

    DeliveryInfo(int iD, int time, string status, string Loc){
        PackageID = iD;
        TimeStamp = time;
        Location = Loc;
        Status = status;
        left = nullptr;
        right = nullptr;
    }

};