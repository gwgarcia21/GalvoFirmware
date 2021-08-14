#include "GalvoControl.h" // header in local directory
#include <math.h>
//#define DEBUG_WINDOWS
#ifdef DEBUG_WINDOWS
    #include <iostream> // header in standard library
    using namespace std;
    #include <iomanip>
#endif

// Constructor
Galvo::Galvo(float pos_x, float pos_y)
{
    set_pos(pos_x, pos_y);
}

// Set new values
void Galvo::set_pos(float pos_x, float pos_y)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
}

float Galvo::get_pos(int axis)
{
    if (axis == 0)
        return _pos_x;
    else
        return _pos_y;
}

void Galvo::move(float x, float y)
{
    float max_step = 0.5f; // tamanho da linha máximo a cada atualização do output em mm
    float step_x = 0.f; // step x
    float step_y = 0.f; // step y
    int dir_x = 1; // 1: up / -1: down
    //int dir_y = 1; // 1: up / -1: down

    //while (_pos_x != x && _pos_y != y)
    while (_pos_x != x)
    {
        if (_pos_x < x)
            dir_x = 1;
        else
            dir_x = -1;
        step_x = (x - _pos_x) * dir_x;
        if (step_x > max_step)
            step_x = max_step;
        _pos_x += step_x * dir_x;
        int out_x = output(_pos_x);
        #ifdef DEBUG_WINDOWS
            cout << out_x << endl;
        #endif
        //spi_add_to_buffer(_pos_x);
    }   
}

float Galvo::stepped_move(float new_pos, int axis)
{
    float max_step = 0.5f; // tamanho da linha máximo a cada atualização do output em mm
    float step = 0.f; // step
    int dir = 1; // 1: up / -1: down

    float pos = get_pos(axis);

    if (pos != new_pos)
    {
        if (pos < new_pos)
            dir = 1;
        else
            dir = -1;
        step = (new_pos - pos) * dir;
        if (step > max_step)
            step = max_step;
        pos += step * dir;
        if (axis == 0)
            _pos_x = pos;
        else
            _pos_y = pos;
        /*#ifdef DEBUG_WINDOWS
            cout << new_pos << endl;
        #endif*/
        return pos;
    }
    else
    {
        return pos;
    }
}

int Galvo::output(float pos)
{
    float theta_pos_rad = pos / FTHETA_F;
    int pos_value = int((theta_pos_rad * OUT_MAX_VALUE) / THETA_RAD); // OUTPUT: regra de três simples para descobrir o valor de tensão representado
    return pos_value;
}

void Galvo::line(float *line_x, float *line_y, int *line_size, float x2, float y2)
{
    // Bresenham's line algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    // http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B

    int line_len = *line_size;
    float x1 = get_pos(0);
    float y1 = get_pos(1);
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    //const bool steep = false;
    float aux;
    if(steep)
    {
        //std::swap(x1, y1);
        aux = x1;
        x1 = y1;
        y1 = aux;
        //std::swap(x2, y2);
        aux = x2;
        x2 = y2;
        y2 = aux;
    }
    
    bool swapped = false;
    if(x1 > x2)
    {
        swapped = true;
        //std::swap(x1, x2);
        aux = x1;
        x1 = x2;
        x2 = aux;
        //std::swap(y1, y2);
        aux = y1;
        y1 = y2;
        y2 = aux;
    }
    #ifdef DEBUG_WINDOWS
        cout << swapped << endl;
    #endif

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);
    //const float dy = 86.0f;
    float error = dx / 2.0f;
    const float ystep = (y1 < y2) ? 0.1f : -0.1f;
    float y = y1;
    for(float x=x1; x<=x2; x=x+0.1f)
    {
        if(steep)
        {
            #ifdef DEBUG_WINDOWS
                cout << std::fixed << std::setprecision(2);
                //cout << "A " << y << " | " << x << endl;
            #endif
            line_x[line_len] = y;
            line_y[line_len] = x;
            line_len++;
        }
        else
        {
            #ifdef DEBUG_WINDOWS
                cout << std::fixed << std::setprecision(2);
                //cout << "B " << x << " | " << y << endl;
            #endif
            line_x[line_len] = x;
            line_y[line_len] = y;
            line_len++;
        }
    
        error -= dy;
        if(error < 0.1f)
        {
            y += ystep;
            error += dx;
        }
    }
    if (swapped)
    {
        int k = 0;
        float temp_x[line_len];
        float temp_y[line_len];
        for(int i = line_len-1; i >= 0; i--) 
        {
            temp_x[k] = line_x[i];
            temp_y[k] = line_y[i];
            k++;
        }
        for (int i=0; i < line_len; i++)
        {
            line_x[i] = temp_x[i];
            line_y[i] = temp_y[i];
        }
    }
    *line_size = line_len;
    /*for (int i=0; i < line_len; i++)
    {
        cout << "C " << line_x[i] << " | " << line_y[i]  << endl;
    }*/
}

/*void Galvo::line( float x1, float y1, float x2, float y2 )
{
    float line_x[1000] = { };
    float line_y[1000] = { };
    int line_len = 0;
    // Bresenham's line algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    // http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    float aux;
    if(steep)
    {
        //std::swap(x1, y1);
        aux = x1;
        x1 = y1;
        y1 = aux;
        //std::swap(x2, y2);
        aux = x2;
        x2 = y2;
        y2 = aux;
    }
    
    bool swapped = false;
    if(x1 > x2)
    {
        swapped = true;
        //std::swap(x1, x2);
        aux = x1;
        x1 = x2;
        x2 = aux;
        //std::swap(y1, y2);
        aux = y1;
        y1 = y2;
        y2 = aux;
    }
    cout << swapped << endl;
    
    // Positivo
    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);
    float error = dx / 2.0f;
    const float ystep = (y1 < y2) ? 0.1f : -0.1f;
    float y = y1;
    for(float x=x1; x<=x2; x=x+0.1f)
    {
        if(steep)
        {
            #ifdef DEBUG_WINDOWS
                cout << std::fixed << std::setprecision(2);
                //cout << "A " << y << " | " << x << endl;
            #endif
            line_x[line_len] = y;
            line_y[line_len] = x;
            line_len++;
        }
        else
        {
            #ifdef DEBUG_WINDOWS
                cout << std::fixed << std::setprecision(2);
                //cout << "B " << x << " | " << y << endl;
            #endif
            line_x[line_len] = x;
            line_y[line_len] = y;
            line_len++;
        }
    
        error -= dy;
        if(error < 0.1f)
        {
            y += ystep;
            error += dx;
        }
    }
    if (swapped)
    {
        int k = 0;
        float temp_x[line_len];
        float temp_y[line_len];
        for(int i = line_len-1; i >= 0; i--) 
        {
            temp_x[k] = line_x[i];
            temp_y[k] = line_y[i];
            k++;
        }
        for (int i=0; i < line_len; i++)
        {
            line_x[i] = temp_x[i];
            line_y[i] = temp_y[i];
        }
    }

    for (int i=0; i < line_len; i++)
    {
        cout << "C " << line_x[i] << " | " << line_y[i]  << endl;
    }
}*/
 
Galvo& Galvo::add(int value)
{
    _pos_x += value;
    return *this;
}
 
Galvo& Galvo::sub(int value) 
{
    _pos_x -= value;
    return *this;
}
 
Galvo& Galvo::mult(int value)
{
    _pos_x *= value;
    return *this;
}