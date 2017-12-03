#ifndef __CHECK_H__
#define __CHECK_H__

#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <list>
#include <hash_map>
#include <queue>


#include "edge.h"
//#define DEBUG

//#ifdef DEBUG
//#include "showtime.h"
//#endif


#define MAX_POINT_COUNT 1100000

typedef double distype;

inline uint64_t point_id(const Point &p) {
    return *reinterpret_cast<const uint64_t *>(&p);
}

namespace __gnu_cxx {
    template<>
    struct hash<Point> : public hash<uint64_t> {
        size_t operator()(const Point &p) const {
            return hash<uint64_t>::operator()(point_id(p));
        }
    };
}


namespace std {
    using namespace __gnu_cxx;
}

bool operator==(const Point &p1, const Point &p2) {
    return 0 == memcmp(&p1, &p2, 8);
}

struct neighbor_type {
    neighbor_type(int num, distype ds) : no(num), dis(ds), next(NULL) {}

    neighbor_type() : next(NULL) {}

    int no;
    distype dis;
    neighbor_type *next;
};


struct node_property {
    distype g;
    distype h;
    distype f;
    int parent;
};

typedef std::hash_map<Point, int> point_node_map_type;

//这里把预先分配内存的操作放到init外是否合法?
node_property property_arr[MAX_POINT_COUNT];
Point point_arr[MAX_POINT_COUNT];
//neighbor array
neighbor_type node_arr[MAX_POINT_COUNT];
//0:raw 1:closed 2:opened
int state_arr[MAX_POINT_COUNT];
point_node_map_type point2Nodes(MAX_POINT_COUNT);
//这里把预先分配内存的操作放到init外是否合法?

int node_count = 0;
double expected_speed = 0;
//

struct NodeCmp {
    bool operator()(int p1, int p2) const {
        return property_arr[p1].f > property_arr[p2].f;
    }

};


class Searcher {
public:

    void init(const std::vector<Edge> &map);

    Result search(const Point &start, const Point &end);

};


void Searcher::init(const std::vector<Edge> &map) {
    //init_1
    int min_speed = 100;
    int max_speed = 10;

    std::vector<Edge>::const_iterator edge_it = map.begin();
    std::vector<Edge>::const_iterator edge_end = map.end();
    point_node_map_type::const_iterator pn_end = point2Nodes.end();
    point_node_map_type::const_iterator pn_it;
    for (; edge_it != edge_end; ++edge_it) {
        // init nodes
        int no1;
        Point start = edge_it->start;
        pn_it = point2Nodes.find(start);
        if (pn_it == pn_end) {
            point_arr[node_count] = start;
            point2Nodes[start] = node_count;
            no1 = node_count;
            node_count++;
            pn_end = point2Nodes.end();
        } else {
            no1 = pn_it->second;
        }

        Point end = edge_it->end;
        pn_it = point2Nodes.find(end);
        int no2;
        if (pn_it == pn_end) {
            point_arr[node_count] = end;
            point2Nodes[end] = node_count;
            no2 = node_count;
            node_count++;
            pn_end = point2Nodes.end();
        } else {
            no2 = pn_it->second;
        }
        //================ init edges ========================

        int deltax = start.x - end.x;
        int deltay = start.y - end.y;
        int speed = edge_it->speed;
        if (speed > max_speed)max_speed = speed;
        if (speed < min_speed)min_speed = speed;

        distype dis = sqrt(deltax * deltax + deltay * deltay) / speed;

        neighbor_type *t1 = new neighbor_type(no2, dis);
        t1->next = node_arr[no1].next;
        node_arr[no1].next = t1;

        t1 = new neighbor_type(no1, dis);
        t1->next = node_arr[no2].next;
        node_arr[no2].next = t1;

    }
    //init_2
    expected_speed = min_speed + (max_speed - min_speed) * 0.75;
//    expected_speed = max_speed;
//    std::cout << min_speed << "<" << max_speed << std::endl;
//    expected_speed = (max_speed + min_speed) / 2.0;
//    std::cout << expected_speed << std::endl;

//    node_count *= 4;
//    expected_speed *= 5;//27.194000

}


Result Searcher::search(const Point &start, const Point &end) {
//    int manhaton_dis = abs(start.x - end.x) + abs(start.y - end.y);
//    double param = manhaton_dis/20000.0;
//    expected_speed =
//    std::cout<<param<<std::endl;
    memset(state_arr, 0, node_count * 4);
    std::priority_queue<int, std::vector<int>, NodeCmp> open_list;
//    uint64_t heap_time = 0;
    // reverse search so that output positive path
    int start_no = point2Nodes[start];
    int end_no = point2Nodes[end];

    int curent_no = end_no;
    property_arr[curent_no].g = 0;
    open_list.push(curent_no);
    while (start_no != (curent_no = open_list.top())) {
        open_list.pop();
        if (state_arr[curent_no] == 1)continue;
        state_arr[curent_no] = 1;
        neighbor_type *it = node_arr[curent_no].next;
        while (NULL != it) {
            int next_no = it->no;
            if (state_arr[next_no] == 1) {
                it = it->next;
                continue;
            }
            distype tg = property_arr[curent_no].g + it->dis;
            if (state_arr[next_no] == 0) {
                state_arr[next_no] = 2;
                int deltax = start.x - point_arr[next_no].x;
                int deltay = start.y - point_arr[next_no].y;
                distype dis = sqrt(deltax * deltax + deltay * deltay) / expected_speed;
                property_arr[next_no].g = tg;
                property_arr[next_no].h = dis;
                property_arr[next_no].f = tg + dis;
                property_arr[next_no].parent = curent_no;
//                uint64_t t_1 = get_time();
                open_list.push(next_no);
//                heap_time += (get_time() - t_1);
            } else if (tg < property_arr[next_no].g) {

                property_arr[next_no].g = tg;
                property_arr[next_no].f = tg + property_arr[next_no].h;
                property_arr[next_no].parent = curent_no;
//                uint64_t t_1 = get_time();
                open_list.push(next_no);
//                heap_time += (get_time() - t_1);
            }
            it = it->next;
        }
    }

//    std::cout << heap_time << std::endl;
    Result result;
    result.time = property_arr[curent_no].g;
    while (curent_no != end_no) {
        result.path.push_back(point_arr[curent_no]);
        curent_no = property_arr[curent_no].parent;
    }
    result.path.push_back(point_arr[curent_no]);

    return result;
}

#endif


