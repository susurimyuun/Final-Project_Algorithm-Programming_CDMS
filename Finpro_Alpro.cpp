#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <unordered_map>
#include <ctime>
//header files
#include "findNearestDriver.hpp"
#include "Driver.hpp"
#include "PackageTracker.hpp"
#include "DeliveryInfo.hpp"
#include "Zipcode.hpp"
#include "CityMap.hpp"
using namespace std;

int inputChecker(){
    int input = 0;
    while(!(cin >> input)){
        cout << "Not an Integer" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return input;

}

int main(){
    srand(time(0));

    vector<Driver> drivers;

    vector<int> availableZips = {
    // Depok
    16411, 16412, 16413, 16414, 16415,
    // Jakarta Selatan
    12110, 12120, 12130, 12140, 12150,
    // Jakarta Timur
    13110, 13120, 13130, 13140, 13150,
    // Jakarta Barat
    11110, 11120, 11130, 11140, 11150,
    // Jakarta Pusat
    10110, 10120, 10130, 10140, 10150,
    // Cinere
    16514, 16515, 16516, 16517, 16518,
    // Margonda
    16424, 16425, 16426, 16427, 16428,
    // Cibubur
    13720, 13721, 13722, 13723, 13724
    };
    ZipCodeValidator ZippyCodes;
    ZippyCodes.loadZipCodes(availableZips);

    CityGraph JaDe;
    JaDe.addRoad("Jakarta Timur", "Jakarta Selatan");
    JaDe.addRoad("Jakarta Selatan", "Depok");
    JaDe.addRoad("Depok", "Jakarta Barat");
    JaDe.addRoad("Jakarta Selatan", "Cinere");
    JaDe.addRoad("Jakarta Pusat", "Jakarta Selatan");
    JaDe.addRoad("Jakarta Pusat", "Jakarta Timur");
    JaDe.addRoad("Depok", "Margonda");
    JaDe.addRoad("Depok", "Cibubur");
    JaDe.addRoad("Jakarta Timur", "Cibubur");
    JaDe.addRoad("Jakarta Barat", "Margonda");
    JaDe.addRoad("Margonda","Cinere");


    string status_delivered = "Package is being Delivered";
    string status_warehouse = "Package is still in Warehouse";
    vector<string> Cities = {
        "Jakarta Timur",
        "Jakarta Pusat",
        "Jakarta Barat",
        "Jakarta Selatan",
        "Cibubur",
        "Depok",
        "Margonda",
        "Cinere"
    };
    PackageTracker root;
    root.addPackage(880,9,(rand() % 2 == 0)? status_delivered : status_warehouse,Cities[rand() % 8]);
    root.addPackage(207,7,(rand() % 2 == 0)? status_delivered : status_warehouse,Cities[rand() % 8]);
    root.addPackage(88,8,(rand() % 2 == 0)? status_delivered : status_warehouse,Cities[rand() % 8]);
    root.addPackage(118,11,(rand() % 2 == 0)? status_delivered : status_warehouse,Cities[rand() % 8]);
    root.addPackage(123,6,(rand() % 2 == 0)? status_delivered : status_warehouse,Cities[rand() % 8]);
    cout << endl;
    int choice = 1;

    Driver d;

    while (choice == 1){
        cout << "================================" << endl;
        cout << "CDMS : City Delivery Map System" << endl;
        cout << "Are you a Customer or Employee?" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Employee" << endl;
        cout << "0. End" << endl;
        cout << "================================" << endl;
        int choice1 = -1;
        while(choice1 < 0 ||choice1 > 2){
            cout << "Enter choice (1/2/0): ";   
            choice1 = inputChecker();
            
            if (choice1 < 0 || choice1 > 2){
                cout << "Invalid Input!" << endl;
            }
        }
        if (choice1 == 0){
            choice = 0;
        }
        else if (choice1 == 1){
            cout << "What do you wanna do?" << endl;
            cout << "1. Check your Delivery Package Status" << endl;
            cout << "2. Deliver Your Package Now" << endl;
            cout << "3. Check if your area is within our reach (Via Zipcode)" << endl;
            cout << "4. Check our whole Service Reach" << endl;
            int choice2 = 0;
            while(choice2 <= 0 ||choice2 > 4){
            cout << "Enter choice (1-4): ";
            choice2 = inputChecker();
            if (choice1 <= 0 || choice1 > 4){
                cout << "Invalid Input!";
                }
            }
            if (choice2 == 1){
                int choice2_1 = 1;
                while (choice2_1 == 1){
                    int customer_PackageID = 0;
                    cout << "Enter your delivery ID : " ;
                    customer_PackageID = inputChecker();
                    root.trackPackage(customer_PackageID);
                    choice2_1 = -1;

                    while (choice2_1 < 0 || choice2_1 > 1){
                        cout << "Do you wanna search again? (Yes = 1/No = 0): ";
                        choice2_1 = inputChecker();
                        if(choice2_1 < 0 || choice2_1 >1){
                            cout << "Invalid Input!" << endl;
                        }
                    }
                    if (choice2_1 == 1){
                        continue;
                    }
                    else if(choice2_1 == 0){
                        break;
                    }
                } 

            }
            if (choice2 == 2){
                int cus_packageID = 1;
                while(cus_packageID == 1){
                    cout << "Enter your package ID: ";
                    cus_packageID = inputChecker();

                    string PackageLoc = root.getPackageLocation(cus_packageID, status_delivered);
                    if(PackageLoc == "Already Delivered"){
                        cout << "Package Already being Delivered" << endl;
                    }
                    else if (PackageLoc != "Not Found"){
                        int nearest = findNearestDriver(PackageLoc,drivers,JaDe);
                        if ( nearest != -1){
                            JaDe.BFS_route(drivers[nearest].Location,PackageLoc);
                            drivers[nearest].completedDeliveries++;
                            root.delivering(cus_packageID,status_delivered);
                        }
                    }
                    else{
                        cout << "Package Not Found!" << endl;
                    }
                    cus_packageID = 0;
                    
                    while(cus_packageID < 1 || cus_packageID > 1){
                        cout << "Wanna Try Again? (Yes(1)/No(0)): ";
                        cus_packageID = inputChecker();
                        if(cus_packageID == 0){
                            break;
                        }
                        if (cus_packageID < 0 || cus_packageID > 1){
                            cout << "Invalid Input" << endl;
                        }
                    }
                }
                
            }
            if(choice2 == 3){
                int choice3 = 1;
                bool valid = true;
                while(choice3 == 1){
                    int zipcode;
                    cout << "Enter your area ZipCodes: ";
                    zipcode = inputChecker();
                    ZippyCodes.isServiceAvailable(zipcode);
                    choice3 = -1;
                    while(choice3 < 0 || choice3 > 1){
                        cout << "Do you wanna try again? (Yes(1)/No(0)): ";
                        choice3 = inputChecker();
                        if(choice3 < 0 || choice3 > 1){
                            cout << "Invalid Input" << endl;
                        }
                    }
            }
        }
            if(choice2 == 4){
                JaDe.PrintAdjacencyList();
            }

        }
        else if(choice1 == 2){
            cout << "What do you wanna do?" << endl;
            cout << "1. Add new Packages" << endl;
            cout << "2. Track Package" << endl;
            cout << "3. Add new Driver" << endl;
            cout << "4. See Drivers Ranking" << endl;
            cout << "5. See all Package IDs" << endl;
            int choice2_2 = -1;
            while (choice2_2 <= 0 || choice2_2 > 5){
                cout <<"Enter your choice: ";
                choice2_2 = inputChecker();
                if (choice2_2 <= 0 || choice2_2 > 5){
                    cout << "Invalid Input!";
                }
            }
            if(choice2_2 == 1){
                int choice2_2_1 = 1;
                while (choice2_2_1 == 1){
                    int id= 0;
                    int time= 0;
                    string status;
                    string location = "Cibubur";
                    int totalPackages;

                    cout << "\nEnter Total Packages : ";
                    totalPackages = inputChecker();

                    // input package data
                    for (int i = 0; i < totalPackages; i++){
                        cout << "\nPackage " << i + 1 << endl;
                        int temp = 0;
                        bool valid = true;

                        while (valid){
                            cout << "Input Package ID : ";
                            id = inputChecker();
                            valid = root.IDValidater(id);
                            if(valid){
                                cout << "ID Already exist!" << endl;
                            }
                            if (id == 0){
                                cout << "ID can't be 0!" << endl;
                                valid = true;
                            }
                        }
                        cin.ignore();
                        cout << "Input time (15:00 = 15): ";
                        time = inputChecker();
                        cin.ignore();
                        while (temp <= 0 || temp > 2){
                            cout << "Input Package Status (1:Package is being Delivered / 2:Package is still in Warehouse) : ";
                            temp = inputChecker();
                            if (temp == 1){
                                status = status_delivered;
                            }
                            else if(temp == 2){
                                status = status_warehouse;
                            }
                            if(temp <= 0 || temp >2){
                                cout << "Invalid Input";
                            }
                        }

                        root.addPackage(id,time, status,Cities[rand() % 8]);
                    }
                    choice2_2_1 = -1;
                    while (choice2_2_1 < 0 || choice2_2_1 > 1){
                        cout << "Do you wanna add more packages? (yes(1)/no(0)): ";
                        choice2_2_1 = inputChecker();
                        if(choice2_2_1 < 0 || choice2_2_1 > 1){
                            cout << "Invalid Input!" << endl;
                        }
                    }
                }
            }
            if(choice2_2 == 2){
                int choice2_2_2 = 1;
                while (choice2_2_2 == 1){
                    int searchID;

                    cout << "\nEnter Package ID to Track : ";
                    searchID = inputChecker();
                    root.trackPackage(searchID);
                    choice2_2_2 = -1;
                    while (choice2_2_2 < 0 || choice2_2_2 > 1){
                        cout << "Do you wanna Track anymore Packages? (yes(1)/no(0)): ";
                        choice2_2_2 = inputChecker();
                        if(choice2_2_2 < 0 || choice2_2_2 > 1){
                            cout << "Invalid Input!" << endl;
                        }
                    }
                }
            }
            if(choice2_2 == 3){
                int choice2_2_3 = 1;
                while (choice2_2_3 == 1){
                    int totalDrivers;

                    cout << "\nEnter Total Drivers : ";
                    totalDrivers = inputChecker();


                    // input driver data
                    for (int i = 0; i < totalDrivers; i++) {


                        cout << "\nDriver " << i + 1 << endl;

                        cout << "Input Driver Name : ";
                        getline(cin, d.name);

                        d.Location = Cities[rand() % 8];
                        d.completedDeliveries = 0;

                        drivers.push_back(d);
                    }
                    int choice2_2_3_1 = -1;
                    while (choice2_2_3_1 < 0 || choice2_2_3_1 > 1){
                        cout << "Do you want to put anymore Drivers?(yes(1)/no(0)): ";
                        choice2_2_3_1 = inputChecker();
                        if(choice2_2_3_1 == 0){
                            choice2_2_3 = 0;
                        }
                        if (choice2_2_3_1 < 0 || choice2_2_3_1 > 1){
                            cout << "Invalid Input!" << endl;
                        }
                    }
                }
            }
            if (choice2_2 == 4){
                showDriverRanking(drivers);
            }
            if (choice2_2 == 5){
                root.print();
            }

        }
    }

    return 0;
}
