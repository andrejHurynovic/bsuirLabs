//
//  Businessman.hpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 29.10.20.
//

#ifndef Businessman_hpp
#define Businessman_hpp

#include "Human.hpp"
#include "PaymentDetail.h"
#include <vector>

class Businessman: public virtual Human {
protected:
    string licenseNumber;
    string address;
    vector<PaymentDetail> paymentDetails;
public:
    Businessman(string licenseNumber = "NULL", string address = "NULL", vector<PaymentDetail> paymentDetails = vector<PaymentDetail>()){
        this->licenseNumber = licenseNumber;
        this->address = address;
        this->paymentDetails = paymentDetails;
    }
    
    void setLicenseNumber(string licenseNumber);
    
    void setAddress(string address);
    
    void addPaymentDetail(PaymentDetail paymentDetail);
    
    string getLicenseNumber();
    
    string getAddress();
    
    PaymentDetail getPaymentDetailForID(int ID);
    
    void printSpreadsheet();
    
    friend ostream& operator << (ostream &outputStream, const Businessman businessman);
    friend istream& operator >> (istream &inputStream, Businessman &Businessman);
    
    ~Businessman(){
        paymentDetails.clear();
    };
    
};

#endif /* Businessman_hpp */
