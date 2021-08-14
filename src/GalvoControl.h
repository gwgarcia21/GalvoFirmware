#pragma once

// Galvo Settings
const int FTHETA_F = 254; // distância focal efetiva da lente em mm
const double THETA_RAD = 0.34906585039; // ângulo de deflexão dos galvos de 20º em radianos
//const int OUT_MAX_VALUE = 1023; // 10 bits -> 1024 valores -> máx 1023
const int OUT_MAX_VALUE = 4095; // 10 bits -> 4096 valores -> máx 4095
//const int VIN_MAX = 5; // tensão máxima de entrada
    
class Galvo
{
    private:
        float _pos_x = 0.f; // posição atual de x em mm
        float _pos_y = 0.f; // posição atual de y em mm
        
    public:
        Galvo(float pos_x = 0.f, float pos_y = 0.f);

        void set_pos(float pos_x, float pos_y);
        float get_pos(int axis);
        void move(float x, float y);
        float stepped_move(float new_pos, int axis);
        int output(float pos);
        void line(float *line_x, float *line_y, int *line_len, float x2, float y2);
        //void line( float x1, float y1, float x2, float y2 );
    
        Galvo& add(int value);
        Galvo& sub(int value);
        Galvo& mult(int value);
    
        //int getValue() { return m_value; }
};