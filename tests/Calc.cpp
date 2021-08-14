#include "Calc.h" // header in local directory
 
Calc::Calc(int value): m_value(value)
{
}
 
Calc& Calc::add(int value)
{
    m_value += value;
    return *this;
}
 
Calc& Calc::sub(int value) 
{
    m_value -= value;
    return *this;
}
 
Calc& Calc::mult(int value)
{
    m_value *= value;
    return *this;
}