#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    this->fieldDraw = new FieldDrawing(this);
    this->controlPanel = new ControlPanel(this);
    this->calculator = new Calculator();

    //fieldDraw->setMinimumSize(1000, 1000);
    fieldDraw->installEventFilter(this);
    //areaDraw = new QScrollArea;
    //areaDraw->setWidget(fieldDraw);

    hbox->addWidget(controlPanel);
    hbox->addWidget(fieldDraw, 1);

    setLayout(hbox);

   tmr = new QTimer(this);
   tmr->singleShot(1000/this->FPS, this, SLOT(update_all()));
}

void MainWindow::update_all() {
    float x, y, speed_x, speed_y;
    QPointF new_coor, new_speed;
    int factor_metre = controlPanel->get_factor_metre();
    float grav_y = controlPanel->get_gravitation_y() * factor_metre;
    float grav_x = controlPanel->get_gravitation_x() * factor_metre;
    int width_room = this->get_width_fieldDraw();
    int height_room = this->get_height_fieldDraw();
    int circle_radius = fieldDraw->get_circle_radius();
    float time = 1./float(FPS);
    for (int i = 0; i < objects.size(); ++i) {
        x = fieldDraw->get_object_x(i);
        y = fieldDraw->get_object_y(i);
        speed_x = this->get_object_speed_x(i);
        speed_y = this->get_object_speed_y(i);
        new_speed = calculator->get_speed(speed_x, speed_y, grav_x, grav_y, time);
        new_coor = calculator->get_coordinates(x, y, new_speed.x(), new_speed.y(), grav_x, grav_y, time);

        if (new_coor.x() + circle_radius >= width_room) {
            new_speed.setX(calculator->get_speed_x(new_speed.x(), ELASTIC));
            this->set_object_x(i, width_room - circle_radius);
            if (abs(new_speed.x()) < MIN_LIMIT_SPEED) {
                new_speed.setX(0);
            }
        }
        else if (new_coor.x() - circle_radius <= 0) {
            new_speed.setX(calculator->get_speed_x(new_speed.x(), ELASTIC));
            this->set_object_x(i, 0 + circle_radius);
            if (abs(new_speed.x()) < MIN_LIMIT_SPEED) {
                new_speed.setX(0);
            }
        }
        else {
            this->set_object_x(i, new_coor.x());
        }

        this->set_object_speed_x(i, new_speed.x());

        if (new_coor.y() + circle_radius >= height_room) {
            new_speed.setY(calculator->get_speed_y(new_speed.y(), ELASTIC));
            this->set_object_y(i, height_room - circle_radius);
            if (abs(new_speed.y()) < MIN_LIMIT_SPEED) {
                new_speed.setY(0);
            }
        }
        else if (new_coor.y() - circle_radius <= 0) {
            new_speed.setY(calculator->get_speed_y(new_speed.y(), ELASTIC));
            this->set_object_y(i, 0 + circle_radius);
            if (abs(new_speed.y()) < MIN_LIMIT_SPEED) {
                new_speed.setY(0);
            }
        }
        else {
            this->set_object_y(i, new_coor.y());
        }

        this->set_object_speed_y(i, new_speed.y());
    }
    this->update_panel();
    fieldDraw->update();
    tmr->singleShot(1000/this->FPS, this, SLOT(update_all()));
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == fieldDraw) {
        int ind;
        QMouseEvent* mouseEvent;
        if (event->type() == QEvent::MouseButtonPress) {
            mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if(mouseEvent != 0)
            {
                if (mouseEvent->button() == Qt::LeftButton) {
                    ind = fieldDraw->get_object_index(mouseEvent->x(), mouseEvent->y());
                    if (ind != -1) {
                        this->select_obj(ind);
                    }
                    else {
                        this->end_pos.setX(mouseEvent->x());
                        this->end_pos.setY(mouseEvent->y());
                        fieldDraw->set_draw_path_fly(true);
                        this->create_path_fly(mouseEvent->x(), mouseEvent->y());
                    }
                }
                else if (mouseEvent->button() == Qt::RightButton) {
                    ind = fieldDraw->get_object_index(mouseEvent->x(), mouseEvent->y());
                    if (ind != -1) {
                        this->pop_object(ind);
                    }
                }
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton && fieldDraw->get_draw_path_fly()) {
                QPointF start_speed = calculator->get_start_speed(mouseEvent->x(), mouseEvent->y(), end_pos.x(), end_pos.y());
                controlPanel->set_start_speed_x(start_speed.x());
                controlPanel->set_start_speed_y(start_speed.y());
                this->add_object(mouseEvent->x(), mouseEvent->y(), start_speed.x(), start_speed.y());
                ind = objects.size()-1;
                this->select_obj(ind);
                fieldDraw->set_draw_path_fly(false);
            }
        }
        else if (event->type() == QEvent::MouseMove && fieldDraw->get_draw_path_fly()) {
            mouseEvent = dynamic_cast<QMouseEvent*>(event);
            QPointF start_speed = calculator->get_start_speed(mouseEvent->x(), mouseEvent->y(), end_pos.x(), end_pos.y());
            controlPanel->set_start_speed_x(start_speed.x());
            controlPanel->set_start_speed_y(start_speed.y());
            this->create_path_fly(mouseEvent->x(), mouseEvent->y());
        }
    }
    return false;
}

int MainWindow::get_width_fieldDraw() {
    return fieldDraw->width();
}

int MainWindow::get_height_fieldDraw() {
    return fieldDraw->height();
}

void MainWindow::add_object(float x, float y, float speed_x, float speed_y) {
    QList<float> lst = {speed_x, speed_y};
    objects.append(lst);
    fieldDraw->add_object(x, y);
}

void MainWindow::pop_object(int index) {
    int sel_obj = fieldDraw->get_select_obj();
    if (sel_obj != -1) {
        if (sel_obj == index) {
            this->deselect_object();
        }
        else if (sel_obj > index) {
            fieldDraw->set_select_obj(sel_obj-1);
        }
    }
    objects.removeAt(index);
    fieldDraw->pop_object(index);
}

void MainWindow::set_object_speed_x(int index, float speed) {
    const QList<float> *lst = &objects.at(index);
    QList<float> new_lst = {speed, (*lst)[1]};
    objects[index] = new_lst;
    lst = nullptr;
}

void MainWindow::set_object_speed_y(int index, float speed) {
    const QList<float> *lst = &objects.at(index);
    QList<float> new_lst = {(*lst)[0], speed};
    objects[index] = new_lst;
    lst = nullptr;
}

void MainWindow::set_object_x(int index, float x) {
    fieldDraw->set_object_x(index, x);
}

void MainWindow::set_object_y(int index, float y) {
    fieldDraw->set_object_y(index, y);
}

void MainWindow::select_obj(int x, int y) {
    int ind = fieldDraw->get_object_index(x, y);
    if (ind != -1) {
        controlPanel->set_x(fieldDraw->get_object_x(ind));
        controlPanel->set_y(fieldDraw->get_object_y(ind));
        fieldDraw->set_select_obj(ind);
    }
}

void MainWindow::select_obj(int index) {
    if (index != -1) {
        controlPanel->set_x(fieldDraw->get_object_x(index));
        controlPanel->set_y(fieldDraw->get_object_y(index));
        fieldDraw->set_select_obj(index);
    }
}

void MainWindow::deselect_object() {
    fieldDraw->set_select_obj(-1);

    controlPanel->set_x(0);
    controlPanel->set_y(0);
    controlPanel->set_speed_x(0);
    controlPanel->set_speed_y(0);
    //controlPanel->set_start_speed_x(0);
    //controlPanel->set_start_speed_y(0);
}

float MainWindow::get_object_speed_x(int index) {
    return objects.at(index)[OBJ_SPEED_X];
}

float MainWindow::get_object_speed_y(int index) {
    return objects.at(index)[OBJ_SPEED_Y];
}

void MainWindow::update_panel() {
    int sel_obj = fieldDraw->get_select_obj();
    if (sel_obj != -1) {
        controlPanel->set_x(fieldDraw->get_object_x(sel_obj));
        controlPanel->set_y(fieldDraw->get_object_y(sel_obj));
        controlPanel->set_speed_x(this->get_object_speed_x(sel_obj));
        controlPanel->set_speed_y(this->get_object_speed_y(sel_obj));
    }
}

void MainWindow::create_path_fly(int start_x, int start_y) {
    if (fieldDraw->polylines != nullptr) {
        delete fieldDraw->polylines;
        fieldDraw->polylines = nullptr;
    }
    fieldDraw->polylines = new QPointF[fieldDraw->COUNT_POLYLINES];
    float interval = 1./float(FPS);
    QPointF speed = calculator->get_start_speed(start_x, start_y, end_pos.x(), end_pos.y());
    int factor_metre = controlPanel->get_factor_metre();
    float grav_y = controlPanel->get_gravitation_y() * factor_metre;
    float grav_x = controlPanel->get_gravitation_x() * factor_metre;
    for (int i = 0; i < fieldDraw->COUNT_POLYLINES; i++) {
        //speed = calculator->get_speed(speed.x(), speed.y(), grav_x, grav_y, interval);
        fieldDraw->polylines[i] = calculator->get_coordinates(start_x, start_y, speed.x(), speed.y(), grav_x, grav_y, interval*i);
    }
}
