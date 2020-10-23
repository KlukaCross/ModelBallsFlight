#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QPointF>

class Calculator
{
public:
    Calculator();
    float get_speed_x(float speed_x, float elastic);
    float get_speed_y(float speed_y, float elastic);
    QPointF get_speed(float speed_x, float speed_y, float acceleration_x, float acceleration_y, float time);
    QPointF get_coordinates(float start_x, float start_y, float speed_x, float speed_y, float acceleration_x, float acceleration_y, float time);
    QPointF get_start_speed(float start_x, float start_y, float end_x, float end_y);
    const float START_SPEED_LOSS = 1;
};

#endif // CALCULATOR_H
