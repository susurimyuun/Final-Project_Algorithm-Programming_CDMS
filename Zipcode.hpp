#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "findNearestDriver.hpp"
#include "Driver.hpp"
#include "PackageTracker.hpp"
#include "DeliveryInfo.hpp"
#include "CityMap.hpp"
class ZipCodeValidator {
private:
    vector<int> servicedZips;

public:
    void loadZipCodes(vector<int> zips) {
        servicedZips = zips;
        sort(servicedZips.begin(), servicedZips.end()); 
    }

    bool isServiceAvailable(int zip) {
        int left = 0, right = servicedZips.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (servicedZips[mid] == zip){
                cout << "Service is Ready!" << endl;
                return true;
            }
            else if (servicedZips[mid] < zip)
                left = mid + 1;
            else
                right = mid - 1;
        }
        cout << "Service is Not Ready" << endl;
        return false;
    }
};