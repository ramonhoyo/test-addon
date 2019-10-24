#ifndef __ACTUAL_CLASS__
#define __ACTUAL_CLASS__

class ActualClass
{
private:
    /* data */
    double m_data;
public:
    ActualClass(double value);
    ~ActualClass();

    double getValue();
    double addValue(double value);
};


#endif