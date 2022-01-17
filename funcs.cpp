//https://contest.yandex.ru/contest/27883/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

static const short int LineStart = 0;
static const short int Point = 1;
static const short int LineEnd = 2;
typedef short int EventType;

void parseFile(std::istream & input, std::ostream & output){

    unsigned long nLines, mPoints;
    input >> nLines >> mPoints;

    //! @brief coordinate, eventType, point index
    std::vector<std::tuple<int,EventType,int>> events(nLines*2 + mPoints);
    std::vector<int> points(mPoints);

    int start, end;
    for(unsigned long i = 0; i<nLines; ++i){
        input >> start >> end;
        events[i*2] = {start, LineStart, -1};
        events[i*2 + 1] = {end, LineEnd, -1};
    }

    for(unsigned long i = 0; i<mPoints; ++i){
        input >> start;
        events[i+nLines*2] = {start,Point,i};
    }

    std::sort(events.begin(), events.end());
    int lines = 0;
    for(const auto & event : events){
        switch(std::get<1>(event)){
            case LineStart:{
                ++lines;
                break;
            }
            case Point:{
                points[std::get<2>(event)] = lines;
                break;
            }
            case LineEnd:{
                --lines;
                break;
            }
        }
    }

    std::copy(points.begin(), points.end(), std::ostream_iterator<int>(output, " "));
}
