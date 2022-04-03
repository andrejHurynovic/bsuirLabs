//
//  main.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include <iostream>
#include <iomanip>

#include "Human.hpp"
#include "Tourist.hpp"
#include "Businessman.hpp"
#include "TouristBusinessman.hpp"


#include "ExceptionTypes.h"
#include "ExceptionEnter.hpp"

int main(int argc, const char * argv[]) {
    
    cout << "0 – Use tourist-businessman template" << endl << "1 – Enter human" << endl << "2 – Enter tourist" << endl << "3 – Enter businessman" << endl << "3 – Enter tourist-businessman" <<  endl;
    
    int temp;
    
    cin >> temp;
    
    switch (temp) {
        case 0:{
            TouristBusinessman touristBusinessman;
            
            touristBusinessman.setName("Andrey");
            touristBusinessman.setSurname("Gourinovich");
            touristBusinessman.setDate(Date(14,02,2002));
            
            touristBusinessman.setPasportNumber("MP3891398");
            touristBusinessman.addBorderCrossing(BorderCrossing("Belarus", Date(15,9,2019)));
            touristBusinessman.addBorderCrossing(BorderCrossing("Belarus", Date(15,9,2019)));
            touristBusinessman.addBorderCrossing(BorderCrossing("Belarus", Date(15,9,2019)));
            
            touristBusinessman.setLicenseNumber("GF9983");
            touristBusinessman.setAddress("Minsk");
            touristBusinessman.addPaymentDetail(PaymentDetail(192.4, Date(28,4,2020)));
            touristBusinessman.addPaymentDetail(PaymentDetail(192.4, Date(28,4,2020)));
            touristBusinessman.addPaymentDetail(PaymentDetail(192.4, Date(28,4,2020)));
            touristBusinessman.addPaymentDetail(PaymentDetail(192.4, Date(28,4,2020)));
            
            touristBusinessman.addPurchaseAddress("Azgura");
            touristBusinessman.addPurchaseAddress("Azgura");
            touristBusinessman.addPurchaseAddress("Azgura");
            
            touristBusinessman.printSpreadsheet();
            cout << touristBusinessman;
            
            break;
        }
        case 1:{
            Human human;
            cin >> human;
            human.printSpreadsheet();
            cout << human;
            break;
        }
        case 2:{
            Tourist tourist[2];
            for(int i = 0; i < 2; i++){
                cin >> tourist[i];
            }
            tourist[0].printSpreadsheet();
            for(int i = 0; i < 2; i++){
                cout << tourist[i];
            }
            break;
        }
        case 3:{
            Businessman businessman;
            cin >> businessman;
            businessman.printSpreadsheet();
            cout << businessman;
            break;
        }
        case 4:{
            TouristBusinessman touristBusinessman;
            cin >> touristBusinessman;
            touristBusinessman.printSpreadsheet();
            cout << touristBusinessman;
            break;
        }
        default:
            break;
    }
}
