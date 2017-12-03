#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/time.h>
#include <vector>
#include "searcher.h"

using namespace std;

void usage(const char *arg) {
    cout << "Usage: " << arg << " inputfile outputfile" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return -1;
    }

    // read input 
    ifstream in(argv[1]);
    if (!in) {
        cout << "Could not open input file " << argv[1] << endl;
        return -1;
    }

    ofstream out(argv[2]);
    if (!out) {
        cout << "Could not open output file " << argv[2] << endl;
        return -1;
    }
    out << fixed << setprecision(6);

    // edge num
    int edgeNum;
    in >> edgeNum;
    if (!in) {
        cout << "Edge num format error" << endl;
        return -1;
    }

    // edges
    vector<Edge> edges;
    Edge edge;
    for (int i = 0; i < edgeNum; i++) {
        in >> edge;
        if (!in) {
            cout << "Edges format error" << endl;
            return -1;
        }
        edges.push_back(edge);
    }

    timeval beginTime, endTime;
    uint64_t totalTime = 0;

    Searcher inst;

    // invoke user's init
    gettimeofday(&beginTime, NULL);
    inst.init(edges);
    gettimeofday(&endTime, NULL);
    totalTime += ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec));
    uint64_t temp_time = totalTime;
    cout<<"init_time-->"<<temp_time<<endl;

    // query num
    int queryNum;
    in >> queryNum;
    if (!in) {
        cout << "Query num format error" << endl;
        return -1;
    }

    // result num
    out << queryNum << endl;

    // queries
    Point start, end;
    for (int i = 0; i < queryNum; i++) {
        in >> start >> end;
        if (!in) {
            cout << "Query format error" << endl;
            return -1;
        }
        gettimeofday(&beginTime, NULL);
        // invoke user's check
        Result result = inst.search(start, end);
        // calculate time
        gettimeofday(&endTime, NULL);
        uint64_t search_time = ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec));
        cout<<i<<"\t"<<search_time<<"\t["<<start<<"\t"<<end<<"]"<<endl;
        totalTime += search_time;

        // write result
        out << result << endl;
    }

    cout<<"total_search_time-->"<<totalTime-temp_time<<endl;
    // write total time
    out << totalTime << endl;

    in.close();
    out.close();
//    cout<<totalTime<<endl;

    return 0;
}


