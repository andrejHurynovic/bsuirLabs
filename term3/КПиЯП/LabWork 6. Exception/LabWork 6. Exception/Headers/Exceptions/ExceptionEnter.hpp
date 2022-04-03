//
//  ExceptionEnter.hpp
//  LabWork 6. Exception
//
//  Created by Андрэй Гурыновіч on 10.11.20.
//

#ifndef ExceptionEnter_hpp
#define ExceptionEnter_hpp

#include "ExceptionTypes.h"

class ExceptionEnter:public ExceptionTypes {
public:
    static int EnterIntWithCheck(enum ErrorType type, int minimal, int maximal);
    static string EnterStringWithCheck(enum ErrorType type, int maximalLenght);
};

#endif /* ExceptionEnter_hpp */
