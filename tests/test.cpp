/* Compile:
*       g++ -o test test.cpp Calc.cpp ..\src\GalvoControl.cpp
*  Run:
*       test.exe
*/


#include "Calc.h"
#include "..\src\GalvoControl.h"
#include <iostream> // header in standard library
using namespace std;

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Galvo galvo;
float line_x[1000] = { };
float line_y[1000] = { };

// Declarações
void move_to_pos(float new_x, float new_y);
void hspiTransfer(uint16_t out_x, uint16_t out_y);

// Open G-Code file
// Read line
// Clean line
int main()
{
    move_to_pos(80.0f, 80.0f);
    move_to_pos(0.0f, 0.0f);
    //move_to_pos(0.0f, 6.7f);

    cout << galvo.get_pos(0) << endl;
    cout << galvo.get_pos(1) << endl;
    return 0;
}

void move_to_pos(float new_x, float new_y)
{
    int line_len = 0;
    galvo.line(line_x, line_y, &line_len, new_x, new_y);
    for (int i=0; i < line_len; i++)
    {
        cout << "X " << line_x[i] << " | Y " << line_y[i]  << endl;
        galvo.set_pos(line_x[i], line_y[i]);
        uint16_t out_x = galvo.output(line_x[i]);
        uint16_t out_y = galvo.output(line_y[i]);
        //cout << "X " << out_x << " | Y " << out_y << endl;
        //SPI
        hspiTransfer(out_x, out_y);
    }
}

void hspiTransfer(uint16_t out_x, uint16_t out_y) {
    static const uint16_t x_axis = 0x1000;
    static const uint16_t y_axis = 0x9000;
    //uint16_t output_data;
    uint16_t output_data_x = x_axis | out_x;
    uint16_t output_data_y = y_axis | out_y;
    //cout << "X " << output_data_x << " | Y " << output_data_y << endl;
    /*hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(15, LOW);
    hspi->transfer16(output_data_x);
    hspi->transfer16(output_data_y);
    digitalWrite(15, HIGH);
    hspi->endTransaction();*/
}

//int axis; // x: 0 / y: 1
//float new_pos; // posição desejada
//float pos_x; // posição atual de x
//float pos_y; // posição atual de y
//float line_xy[1000][1000] = {};
//galvo.line(2.0f,3.0f,0.1f,1.0f); // swapped true OK
//galvo.line(0.1f,1.0f,2.0f,3.0f); // swapped false OK
//galvo.line(2.0f,1.0f,0.1f,3.0f); // swapped false OK
//galvo.line(0.1f,1.0f,2.0f,3.0f); // swapped false OK