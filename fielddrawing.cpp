#include "fielddrawing.h"
#include <QPainter>
#include <cmath>

FieldDrawing::FieldDrawing(QWidget *parent) : QWidget(parent)
{
    int RADIUS = 20;
    this->set_circle_color(Qt::red);
    this->set_circle_radius(RADIUS);
    this->setMinimumSize(2*RADIUS, 2*RADIUS);


    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->show();

}

void FieldDrawing::paintEvent(QPaintEvent *e) {

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

    painter.setBrush(QBrush(this->circle_color, Qt::SolidPattern));

    QPointF qp;
     for (int i = 0; i < objects.size(); i++) {
         qp = objects.at(i);
         if (selected_obj != -1 and i == selected_obj) {
             painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
             painter.drawEllipse(qp.x()-circle_radius, qp.y()-circle_radius, 2*circle_radius, 2*circle_radius);
             painter.setBrush(QBrush(this->circle_color, Qt::SolidPattern));
         }
         else {
             painter.drawEllipse(qp.x()-circle_radius, qp.y()-circle_radius, 2*circle_radius, 2*circle_radius);
         }
     }

     if (draw_path_fly) {
         qp = polylines[0];
         painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
         painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
         painter.drawEllipse(qp.x()-circle_radius, qp.y()-circle_radius, 2*circle_radius, 2*circle_radius);
         painter.drawPolyline(polylines, COUNT_POLYLINES);
     }
}

void FieldDrawing::set_circle_color(Qt::GlobalColor clr) {
    this->circle_color = clr;
}

void FieldDrawing::set_circle_radius(int radius) {
    this->circle_radius = radius;
}

void FieldDrawing::set_object_x(int index, float x) {
    const QPointF *qp = &(objects.at(index));
    objects[index] = QPointF(x, (*qp).y());
    qp = nullptr;
}

void FieldDrawing::set_object_y(int index, float y) {
    const QPointF *qp = &(objects.at(index));
    objects[index] = QPointF((*qp).x(), y);
    qp = nullptr;
}

void FieldDrawing::add_object(float x, float y) {
    QPointF qp(x, y);
    this->objects.append(qp);
}

void FieldDrawing::pop_object(int index) {
    this->objects.removeAt(index);
}

float FieldDrawing::get_object_x(int index) {
    QPointF qp = objects.at(index);
    return qp.x();
}

float FieldDrawing::get_object_y(int index) {
    QPointF qp = objects.at(index);
    return qp.y();
}

int FieldDrawing::get_object_index(int x, int y) {
    QPointF qp;
    for (int i = objects.size()-1; i >= 0 ; i--) {
        qp = objects.at(i);
        if (pow((x - qp.x()), 2) + pow((y - qp.y()), 2) <= pow(circle_radius, 2)) {
            return i;
        }
    }
    return -1;
}

void FieldDrawing::set_select_obj(int index) {
    this->selected_obj = index;
}

int FieldDrawing::get_select_obj() {
    return this->selected_obj;
}

int FieldDrawing::get_circle_radius() {
    return this->circle_radius;
}

void FieldDrawing::set_draw_path_fly(bool flag) {
    this->draw_path_fly = flag;
}

bool FieldDrawing::get_draw_path_fly() {
    return this->draw_path_fly;
}
