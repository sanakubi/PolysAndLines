#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>


struct obj_point {
    double x, y;

    friend bool operator==(obj_point& A, obj_point& B) {
        return( (A.x == B.x) && (A.y == B.y) );
    }

    friend std::ostream& operator<<(std::ostream& out, obj_point& X) {
        out << X.x << ";" << X.y;
        return out;
    }

};


struct obj_line_vec {
    obj_point start, end;
};

typedef enum { NOT, ITRS, OVRL, OVRL_OS, OVRL_FULL } action;    // Intersection, Overlay, Overlay one side, Overlay all line, No, 

struct cls_act {
    action type;
    obj_point point;
};

struct report_act {
    int intersections;
    action type;
};

obj_point get_obj_point(int x_, int y_);
obj_line_vec get_obj_line(obj_point start_, obj_point end_);


class object {
public:

    int poly_count = 0;

    std::vector<obj_line_vec> lines;
    std::vector<obj_point> points;

    object();
    object(int count);
    ~object();

    cls_act line_intersection(obj_line_vec& a, obj_line_vec& b);

    report_act collision(obj_line_vec& a);
    double inline_check(obj_point& intr, cls_act& act, double a1, double b1, double a2, double b2);

    void add_line(obj_line_vec line);
    void add_line(obj_point start_pt, obj_point end_pt);
    void add_point(obj_point pnt);

    void calcalte_object();

    int get_size();

    int report(obj_line_vec& line);

};


