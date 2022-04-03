//
//  PaymentDetail.h
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 29.10.20.
//

#ifndef PaymentDetail_h
#define PaymentDetail_h

#include "Date.hpp"

struct PaymentDetail {
    PaymentDetail(int amount = 0, Date date = Date()){
        this->amount = amount;
        this->date = date;
    }
    float amount;
    Date date;
};

#endif /* PaymentDetail_h */
