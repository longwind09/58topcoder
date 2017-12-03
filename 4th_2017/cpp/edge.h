#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream>
#include <vector>

typedef struct {
    int x;
    int y;
} Point;

std::ostream& operator<< (std::ostream& out, const Point& p) {
    out << p.x << "," << p.y;
    return out;
}

std::istream& operator>> (std::istream& in, Point& p) {
    char c;
    in >> p.x >> c >> p.y;
    return in;
}

typedef struct {
    Point start;
    Point end;
    int speed;
} Edge;

std::istream& operator>> (std::istream& in, Edge& e) {
    in >> e.start >> e.end >> e.speed;
    return in;
}


typedef struct {
    double time;
    std::vector<Point> path;
} Result;

std::ostream& operator<< (std::ostream& out, const Result& r) {
    out << r.time << "\t" << r.path.size();
	
    std::vector<Point>::const_iterator it;
    for (it=r.path.begin(); it!=r.path.end(); ++it) {
        out<<"\t"<<*it;
    }

    return out;
}

#endif

