#pragma once
// https://www.learncpp.com/cpp-tutorial/class-code-and-header-files/
class Calc
{
    private:
        int m_value = 0;
    
    public:
        Calc(int value=0);
    
        Calc& add(int value);
        Calc& sub(int value);
        Calc& mult(int value);
    
        int getValue() { return m_value; }
};