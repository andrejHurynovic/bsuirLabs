//
//  TouristBusinessman.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 30.10.20.
//

#include "TouristBusinessman.hpp"


void TouristBusinessman::addPurchaseAddress(string purchaseAddress){
    this->purchaseAddresses.push_back(purchaseAddress);
}


string TouristBusinessman::getPurchaseAddressForID(int ID){
    if(purchaseAddresses.size() < ID){
        return purchaseAddresses[ID];
    }else{
        return "NULL";
    }
}

void TouristBusinessman::printSpreadsheet(){
    cout << setw(13) << "|  Surname  |" << setw(12) << "|   Name   |" << setw(12) << "| Birthday |" << setw(16)  << "|Pasport number|" << setw(15) << "|   Country   |" << setw(12) << "|   Date   |" << "|License number|" << setw(13) << "|  Address  |" << setw(8) << "|Amount|" << setw(12) << "|   Date   |" << "|Purchase address|" << endl;
}

ostream& operator << (ostream &outputStream, TouristBusinessman touristBusinessman){
    
    cout << *dynamic_cast<Human*>(&touristBusinessman);
    
    
    
    cout << '|' << setw(14) << touristBusinessman.pasportNumber << '|';
    
    if(touristBusinessman.borderCrossings.size()){
        cout << '|' << setw(13) << touristBusinessman.borderCrossings[0].country << touristBusinessman.borderCrossings[0].date;
    }else{
        cout << setw(28);
    }
    
    
    cout << '|' << setw(14) << touristBusinessman.licenseNumber << '|' <<  '|' << setw(11) << touristBusinessman.address << '|';
    
    if(touristBusinessman.paymentDetails.size()){
        cout << '|' << setw(6)<< touristBusinessman.paymentDetails[0].amount << touristBusinessman.paymentDetails[0].date;
    }else{
        cout << setw(21);
    }
    
    if(touristBusinessman.purchaseAddresses.size()){
        cout << '|' << setw(16) << touristBusinessman.purchaseAddresses[0] << '|';
    }
    
    cout << endl;
    
    int numberOfBorderCrossings = 1, numberOfPaymentDetails = 1, numberOfPurchaseAddresses = 1;
    
    do{
        if(numberOfBorderCrossings < touristBusinessman.borderCrossings.size()){
            cout << setw(54) << '|' << setw(13) << touristBusinessman.borderCrossings[numberOfBorderCrossings].country << touristBusinessman.borderCrossings[numberOfBorderCrossings].date;
            numberOfBorderCrossings++;
        }
        
        if(numberOfPaymentDetails < touristBusinessman.paymentDetails.size()){
            if(numberOfBorderCrossings > numberOfPaymentDetails){
                cout << setw(30);
            }else{
                cout << setw(110);
            }
            cout << '|' << setw(6) << touristBusinessman.paymentDetails[numberOfPaymentDetails].amount << touristBusinessman.paymentDetails[numberOfPaymentDetails].date;
            numberOfPaymentDetails++;
        }
        
        if(numberOfPurchaseAddresses < touristBusinessman.purchaseAddresses.size()){
            if(numberOfPaymentDetails > numberOfPurchaseAddresses){
                
            }else{
                if(numberOfBorderCrossings > numberOfPurchaseAddresses){
                    cout << setw(50);
                }else{
                    cout << setw(130);
                }
            }
            cout << '|' << setw(16) << touristBusinessman.purchaseAddresses[numberOfPurchaseAddresses] << '|';
            numberOfPurchaseAddresses++;
        }
        cout << endl;
        
    }while(numberOfBorderCrossings < touristBusinessman.borderCrossings.size() || numberOfPaymentDetails < touristBusinessman.paymentDetails.size() || numberOfPurchaseAddresses < touristBusinessman.purchaseAddresses.size());
    
    return outputStream;
}

istream& operator >> (istream &inputStream, TouristBusinessman &touristBusinessman){
    
    Businessman *businessman;
    businessman = &touristBusinessman;
    
    cin >> *dynamic_cast<Businessman*>(businessman);
    
    
    cout << "Pasport number:" << endl;
    cin >> touristBusinessman.pasportNumber;
    
    BorderCrossing borderCrossing;
    int temp;
    
    do{
        cout << "Enter border crossing? (0/1)";
        cin >> temp;
        
        if(temp){
            cout << "Border crossing:" << endl << "Country:";
            cin >> borderCrossing.country;
            cout << "Date:" << endl;
            cin >> borderCrossing.date;
            
            touristBusinessman.borderCrossings.push_back(borderCrossing);
        }
        
    }while(temp);
    
    
    
    string purchaseAddress;
    do{
        cout << "Enter purchase address? (0/1)";
        cin >> temp;
        
        if(temp){
            cin >> purchaseAddress;
            
            touristBusinessman.purchaseAddresses.push_back(purchaseAddress);
        }
        
    }while(temp);
    
    return inputStream;
}
