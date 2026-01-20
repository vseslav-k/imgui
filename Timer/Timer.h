#pragma once
#include <chrono>
#include <vector>
#include <string>

typedef std::chrono::steady_clock::time_point time_point;



class Timer{
    
    public:
    struct TimeRecord{
        std::string name;
        time_point time;
    };




    std::vector<TimeRecord> time_records;
    
    static long long int microPassed(const time_point& start, const time_point& end);
    static double milliPassed(const time_point& start, const time_point& end);

    void setTimePoint(const std::string& name);
    void clearTimePoints();
    int deleteTimePoint(const std::string& name);
    int deleteTimePoints(const time_point& start, const time_point& end);
    int deleteTimePoints(int startIdx, int endIdx);
    bool timePointExists(const std::string& name);
    const time_point& getTimePoint(const std::string & name) ;
    const time_point& getTimePoint(int idx);

    Timer() = default;
    ~Timer() = default;
};