#include "calculator.h"
#include <cmath>

Calculator::Calculator()
{

}

float Calculator::get_speed_x(float speed_x, float elastic) {
    return -speed_x*elastic;
}

float Calculator::get_speed_y(float speed_y, float elastic) {
    return -speed_y*elastic;
}

QPointF Calculator::get_speed(float speed_x, float speed_y, float acceleration_x, float acceleration_y, float time) {
    float spdx = speed_x + acceleration_x * time;
    float spdy = speed_y + acceleration_y * time;
    return QPointF(spdx, spdy);
}

QPointF Calculator::get_coordinates(float start_x, float start_y, float speed_x, float speed_y, float acceleration_x, float acceleration_y, float time) {
    float newx = start_x + speed_x * time + (acceleration_x * pow(time, 2)) / 2;
    float newy = start_y + speed_y * time + (acceleration_y * pow(time, 2)) / 2;
    return QPointF(newx, newy);
}
QPointF Calculator::get_start_speed(float start_x, float start_y, float end_x, float end_y) {
    return QPointF(START_SPEED_LOSS*(end_x-start_x), START_SPEED_LOSS*(end_y-start_y));
}
