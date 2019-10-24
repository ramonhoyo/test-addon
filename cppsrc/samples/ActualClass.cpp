#include "ActualClass.h"

ActualClass::ActualClass(double value):
    m_data(value)
{
}

ActualClass::~ActualClass()
{
}


double ActualClass::getValue(){
    return m_data;
}

double ActualClass::addValue(double value){
    m_data += value;
    return m_data;
}