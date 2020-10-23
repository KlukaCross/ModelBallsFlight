#ifndef FIELDDRAWING_H
#define FIELDDRAWING_H

#include <QWidget>
#include <QList>

class FieldDrawing : public QWidget
{
public:
    explicit FieldDrawing(QWidget *parent = nullptr);
    void set_object_x(int index, float x);
    void set_object_y(int index, float y);
    void set_circle_color(Qt::GlobalColor clr);
    void set_circle_radius(int radius);
    void add_object(float x, float y);
    void pop_object(int index);
    int get_object_index(int x, int y);
    float get_object_x(int index);
    float get_object_y(int index);
    void set_select_obj(int index);
    int get_select_obj();
    int get_circle_radius();
    void set_draw_path_fly(bool flag);
    bool get_draw_path_fly();
    static const int COUNT_POLYLINES = 100;
    QPointF *polylines = nullptr;

protected:
    void paintEvent(QPaintEvent *e);

private:
    int circle_radius = 0;
    int selected_obj = -1;
    QColor circle_color;
    QList<QPointF> objects;
    bool draw_path_fly = false;
};

#endif // FIELDDRAWING_H
