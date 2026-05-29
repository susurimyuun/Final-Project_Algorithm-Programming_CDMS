#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "findNearestDriver.hpp"
#include "Driver.hpp"
#include "DeliveryInfo.hpp"
#include "Zipcode.hpp"
#include "CityMap.hpp"

class PackageTracker {

private:
    DeliveryInfo* root = nullptr;

    unordered_map<int, DeliveryInfo*> packageDatabase;

    DeliveryInfo* insertTree(DeliveryInfo* current,DeliveryInfo* newNode){
        if (current == nullptr){
            return newNode;
        }
        if( newNode->TimeStamp < current->TimeStamp){
            current->left = insertTree(current->left,newNode);
        }
        if (newNode->TimeStamp > current->TimeStamp){
            current->right = insertTree(current->right,newNode);
        }
        return current;
    }
    //print packages
    void inorder(DeliveryInfo* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->PackageID << " (Time : " << root->TimeStamp<< " )" << "current status : "<< root->Status << endl;
        inorder(root->right);
    }

public:

    // add package
    void addPackage(int id,int time ,string status, string loc) {

        DeliveryInfo* newNode = new DeliveryInfo(id,time,status, loc);
        root = insertTree(root,newNode);
        packageDatabase[id] = newNode;
    }
    //print packages
    void print(){
        inorder(root);
    }
    string getPackageLocation(int id, string stats) {
        if(!packageDatabase.count(id)){
            return "Not Found";
        }
        if(packageDatabase[id]->Status != stats){
            if (packageDatabase.count(id)) {
                return packageDatabase[id]->Location;
            }
        }
        else if(packageDatabase[id]->Status == stats){
            cout << "Already being Delivered" << endl;
            return "Already Delivered";
        }
        return "Not Found";
    }


    // search package
    void trackPackage(int id) {

        cout << "\nTracking Package #" << id << "...\n";

        if (packageDatabase.count(id)) {

            cout << "Package Found!\n";
            cout << "Current Status : "
                 << packageDatabase[id]->Status
                 << "\nLocation: "
                 << packageDatabase[id]->Location
                 << endl;

        } else {

            cout << "Package Not Found.\n";
        }
    }
    DeliveryInfo* searchTree(DeliveryInfo* current, int id,string changing_status){
        if (current == nullptr){
            return current;
        }
        if (current->PackageID == id){
            return current;
        }
        DeliveryInfo* left = searchTree(current->left,id,changing_status);
        if(left != nullptr){
            current->Status = changing_status;
            return current;
        }
        return searchTree(current->right,id,changing_status);

    }
    void delivering(int id, string stats_changing){
        if(packageDatabase.count(id)){

            if(packageDatabase[id]->Status == stats_changing){
                cout << "Your Package is already being delivered to you!" << endl;
                return;
            }
            else{
                cout << "Package ID found!" << endl;
                        cout << "+++++++++++++++++++++++++++" << endl;
                        for (int cd = 5; cd > 0; cd--){
                            cout << cd << "......Setting your package" <<endl;
                            if (cd == 2){
                                cout << "Giving your package to our closest delivery driver" << endl;
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        cout << "Delivering your package now!" << endl;
                        packageDatabase[id]->Status = stats_changing;
            }
        }
        else{
            cout << "Package ID not found!" << endl;
        }
    }
    bool IDValidater(int id){
        if (packageDatabase.count(id)){
            return true;
        }
        return false;
    }

};