//
//  Businessman.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 29.10.20.
//

#include "Businessman.hpp"


void Businessman::setLicenseNumber(string licenseNumber){
    this->licenseNumber = licenseNumber;
}

void Businessman::setAddress(string address){
    this->address = address;
}

void Businessman::addPaymentDetail(PaymentDetail paymentDetail){
    this->paymentDetails.push_back(paymentDetail);
}

string Businessman::getLicenseNumber(){
    return this->licenseNumber;
}

string Businessman::getAddress(){
    return this->address;
}

PaymentDetail Businessman::getPaymentDetailForID(int ID){
    if(paymentDetails.size() < ID){
        return paymentDetails[ID];
    }else{
        return PaymentDetail(0, Date(0,0,0));
    }
}

void Businessman::printSpreadsheet(){
    cout << "|  Surname  |" << "|   Name   |" << "| Birthday |" << "|License number|" << "|  Address  |" << "|Amount|" << "|   Date   |" << endl;
}


ostream& operator << (ostream &outputStream, Businessman businessman){
    
    Human *human;
    human = &businessman;
    
    cout << *dynamic_cast<Human*>(&businessman);
    
    cout << '|' << setw(14) << businessman.licenseNumber << '|' <<  '|' << setw(11) << businessman.address << '|';
    
    for(int i = 0; i < businessman.paymentDetails.size(); i++){
        if(i){
            cout << setw(67);
        }
        cout << '|' << setw(6)<< businessman.paymentDetails[i].amount << businessman.paymentDetails[i].date;
    }
    return outputStream;
}

istream& operator >> (istream &inputStream, Businessman &businessman){
    
    Human *human;
    human = &businessman;
    
    cin >> *dynamic_cast<Human*>(human);
    
    cout << "License number(max 14 symbols): ";
    businessman.licenseNumber = ExceptionEnter::EnterStringWithCheck(licenseNumber, 14); 
    cout << "Address(max 11 symbols): ";
    businessman.address = ExceptionEnter::EnterStringWithCheck(address, 11);

    PaymentDetail paymentDetail;
    int temp;
    
    do{
        cout << "Enter payment detail? (0/1)" << endl;
        cin >> temp;
        
        if(temp){
            cout << "Payment detail: " << endl << "Amount:";
            paymentDetail.amount = ExceptionEnter::EnterIntWithCheck(amount, 1, 999999);
            cout << "Date:" << endl;
            cin >> paymentDetail.date;
            
            businessman.paymentDetails.push_back(paymentDetail);
        }
        
    }while(temp);
    
    return inputStream;
}
