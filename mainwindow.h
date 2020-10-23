#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "fielddrawing.h"
#include "controlpanel.h"
#include "calculator.h"
#include <QEvent>
#include <QTimer>
#include <QList>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void update_all();

protected:
    void set_coor_circle(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    FieldDrawing *fieldDraw;
    ControlPanel *controlPanel;
    Calculator *calculator;
    QList<QList<float>> objects;
    const int OBJ_SPEED_X = 0;
    const int OBJ_SPEED_Y = 1;
    const int FPS = 60;
    const float ELASTIC = 0.8;
    QTimer *tmr;

    QPoint end_pos;

    void add_object(float x, float y, float speed_x, float speed_y);
    void pop_object(int index);
    void select_obj(int x, int y);
    void select_obj(int index);
    void set_object_speed_x(int index, float speed);
    void set_object_speed_y(int index, float speed);
    void set_object_x(int index, float x);
    void set_object_y(int index, float y);
    void deselect_object();
    float get_object_speed_x(int index);
    float get_object_speed_y(int index);
    int get_width_fieldDraw();
    int get_height_fieldDraw();
    void update_panel();
    void create_path_fly(int start_x, int start_y);

    const float MIN_LIMIT_SPEED = 2;
};
#endif // MAINWINDOW_H
