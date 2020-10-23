#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    float get_gravitation_y();
    float get_gravitation_x();
    float get_start_speed_x();
    float get_start_speed_y();
    float get_speed_x();
    float get_speed_y();
    int get_x();
    int get_y();
    int get_factor_metre();
    void set_start_speed_x(int speed_x);
    void set_start_speed_y(int speed_y);
    void set_speed_x(int speed_x);
    void set_speed_y(int speed_y);
    void set_x(int x);
    void set_y(int y);
private:
    float gravitation_y = 9.8;
    float gravitation_x = 0;
    float start_speed_x = 0;
    float start_speed_y = 0;
    float speed_x = 0;
    float speed_y = 0;
    int now_x = 0;
    int now_y = 0;
    int factor_metre = 1;

    QLabel *LabGravitationY;
    QDoubleSpinBox *SpinGravitationY;
    QLabel *LabGravitationX;
    QDoubleSpinBox *SpinGravitationX;
    QLabel *LabStartSpeedX;
    QLabel *LabStartSpeedY;
    QLabel *LabNowSpeedX;
    QLabel *LabNowSpeedY;
    QLabel *LabNowX;
    QLabel *LabNowY;
    QSpinBox *SpinFactorMetre;
    QLabel *LabFactorMetre;

    void set_speed_room(float speed_room);
    void set_gravitation_y(float grav);
    void set_gravitation_x(float grav);
    void set_factor_metre(int factor);

    const int MAX_GRAVITATION = 100;
    const int MIN_GRAVITATION = -100;
    const int MAX_SPEED_ROOM = 3;
    const int MIN_SPEED_ROOM = 0;
    const int MAX_FACTOR_METRE = 100;
};

#endif // CONTROLPANEL_H
