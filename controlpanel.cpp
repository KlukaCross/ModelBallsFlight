#include "controlpanel.h"
#include <QFormLayout>


ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);

    LabGravitationY = new QLabel(QString("gravitation y: %1 m/s^2").arg(gravitation_y), this);
    SpinGravitationY = new QDoubleSpinBox(this);
    SpinGravitationY->setRange(MIN_GRAVITATION, MAX_GRAVITATION);
    SpinGravitationY->setSingleStep(0.1);
    SpinGravitationY->setValue(gravitation_y);
    connect(SpinGravitationY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &ControlPanel::set_gravitation_y);

    LabGravitationX = new QLabel(QString("gravitation x: %1 m/s^2").arg(gravitation_x), this);
    SpinGravitationX = new QDoubleSpinBox(this);
    SpinGravitationX->setRange(MIN_GRAVITATION, MAX_GRAVITATION);
    SpinGravitationX->setSingleStep(0.1);
    SpinGravitationX->setValue(gravitation_x);
    connect(SpinGravitationX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &ControlPanel::set_gravitation_x);

    LabFactorMetre = new QLabel(QString("1 metre = %1 pixels").arg(factor_metre), this);
    SpinFactorMetre = new QSpinBox(this);
    SpinFactorMetre->setRange(1, MAX_FACTOR_METRE);
    SpinFactorMetre->setValue(1);
    connect(SpinFactorMetre, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ControlPanel::set_factor_metre);

    LabStartSpeedX = new QLabel(QString("start speed x: %1 m/s").arg(start_speed_x), this);
    LabStartSpeedY = new QLabel(QString("start speed y: %1 m/s").arg(start_speed_y), this);
    LabNowSpeedX = new QLabel(QString("speed x: %1 m/s").arg(speed_x), this);
    LabNowSpeedY = new QLabel(QString("speed y: %1 m/s").arg(speed_y), this);
    LabNowX = new QLabel(QString("x: %1 m").arg(now_x), this);
    LabNowY = new QLabel(QString("y: %1 m").arg(now_y), this);

    grid->addWidget(LabGravitationY, 1, 0);
    grid->addWidget(SpinGravitationY, 1, 1);
    grid->addWidget(LabGravitationX, 2, 0);
    grid->addWidget(SpinGravitationX, 2, 1);
    grid->addWidget(LabFactorMetre, 3, 0);
    grid->addWidget(SpinFactorMetre, 3, 1);
    grid->addWidget(LabStartSpeedX, 4, 0);
    grid->addWidget(LabStartSpeedY, 5, 0);
    grid->addWidget(LabNowSpeedX, 6, 0);
    grid->addWidget(LabNowSpeedY, 7, 0);
    grid->addWidget(LabNowX, 8, 0);
    grid->addWidget(LabNowY, 9, 0);

    setLayout(grid);
}

void ControlPanel::set_gravitation_y(float grav) {
    QString st = "gravitation y: %1 m/s^2";
    LabGravitationY->setText(st.arg(grav));
    this->gravitation_y = grav;
}

void ControlPanel::set_gravitation_x(float grav) {
    QString st = "gravitation x: %1 m/s^2";
    LabGravitationX->setText(st.arg(grav));
    this->gravitation_x = grav;
}

float ControlPanel::get_gravitation_y() {
    return this->gravitation_y;
}

float ControlPanel::get_gravitation_x() {
    return this->gravitation_x;
}

void ControlPanel::set_start_speed_x(int speed_x) {
    QString st = "start speed x: %1 m/s";
    LabStartSpeedX ->setText(st.arg(speed_x/factor_metre));
    this->start_speed_x = speed_x;
}

void ControlPanel::set_start_speed_y(int speed_y) {
    QString st = "start speed y: %1 m/s";
    LabStartSpeedY ->setText(st.arg(speed_y/factor_metre));
    this->start_speed_y = speed_y;
}

float ControlPanel::get_start_speed_x() {
    return this->start_speed_x;
}

float ControlPanel::get_start_speed_y() {
    return this->start_speed_y;
}

void ControlPanel::set_speed_x(int speed_x) {
    QString st = "speed x: %1 m/s";
    LabNowSpeedX->setText(st.arg(speed_x/factor_metre));
    this->speed_x = speed_x;
}

float ControlPanel::get_speed_x() {
    return this->speed_x;
}

void ControlPanel::set_speed_y(int speed_y) {
    QString st = "speed y: %1 m/s";
    LabNowSpeedY->setText(st.arg(speed_y/factor_metre));
    this->speed_y = speed_y;
}

float ControlPanel::get_speed_y() {
    return this->speed_y;
}

void ControlPanel::set_x(int x) {
    QString st = "x: %1 m";
    LabNowX->setText(st.arg(x/factor_metre));
    this->now_x = x;
}

int ControlPanel::get_x() {
    return this->now_x;
}

void ControlPanel::set_y(int y) {
    QString st = "y: %1 m";
    LabNowY->setText(st.arg(y/factor_metre));
    this->now_y = y;
}

int ControlPanel::get_y() {
    return this->now_y;
}

void ControlPanel::set_factor_metre(int factor) {
    QString st = "1 metre = %1 pixels";
    LabFactorMetre->setText(st.arg(factor));
    this->factor_metre = factor;
}

int ControlPanel::get_factor_metre() {
    return this->factor_metre;
}
