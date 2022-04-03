//
//  TouristBusinessman.hpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 30.10.20.
//

#ifndef TouristBusinessman_hpp
#define TouristBusinessman_hpp

#include "Tourist.hpp"
#include "Businessman.hpp"
#include <vector>


class TouristBusinessman: public Tourist, public Businessman {
protected:
    vector<string> purchaseAddresses;
public:
    TouristBusinessman(vector<string> purchaseAddresses = vector<string>()){
        this->purchaseAddresses = purchaseAddresses;
    }
        
    void addPurchaseAddress(string purchaseAddress);
        
    string getPurchaseAddressForID(int ID);
    
    void printSpreadsheet();
    
    friend ostream& operator << (ostream &outputStream, TouristBusinessman touristBusinessman);
    friend istream& operator >> (istream &inputStream, TouristBusinessman &touristBusinessman);
    
    ~TouristBusinessman(){
        purchaseAddresses.clear();
    };
};


#endif /* TouristBusinessman_hpp */
