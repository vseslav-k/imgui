#include "Timer.h"
#include <algorithm>

long long int Timer::microPassed(const time_point& start, const time_point& end){
    return std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
}
double Timer::milliPassed(const time_point& start, const time_point& end){
    return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end-start).count();
}

void Timer::setTimePoint(const std::string& name){
    time_records.push_back(TimeRecord{ name, std::chrono::steady_clock::now()});
}
void Timer::clearTimePoints(){
    time_records.clear();
    time_records.shrink_to_fit();
}

int Timer::deleteTimePoint(const std::string& name){
    for(size_t i = 0; i < time_records.size(); ++i){
        if(time_records[i].name == name){
            time_records.erase(time_records.begin() + i);
            return 1;
        }
    }
    return 0;
}
int Timer::deleteTimePoints(const time_point& start, const time_point& end){
    const size_t before = time_records.size();

    time_records.erase(
        std::remove_if(time_records.begin(), time_records.end(),
            [&](const auto& r) {
                return r.time >= start && r.time <= end;
            }),
        time_records.end()
    );

    return static_cast<int>(before - time_records.size());
}
int Timer::deleteTimePoints(int startIdx, int endIdx){
    if(time_records.empty()) return 0;
    if(startIdx > endIdx) std::swap(startIdx, endIdx);
    if(startIdx < 0 ) startIdx = 0;
    if(endIdx >= static_cast<int>(time_records.size())) endIdx = static_cast<int>(time_records.size()) - 1; 

    time_records.erase(time_records.begin() + startIdx, time_records.begin() + endIdx + 1);
    return endIdx - startIdx + 1;
}
bool Timer::timePointExists(const std::string& name){
    for(const TimeRecord& record : time_records)
        if(record.name == name)
            return true;

    return false;
}
const time_point& Timer::getTimePoint(const std::string & name){
    for(const TimeRecord& record : time_records)
        if(record.name == name)
            return record.time;

    throw std::runtime_error("Timer::getTimePoint: Time point with name '" + name + "' does not exist!");
}
const time_point& Timer::getTimePoint(int idx){
    if(idx < 0 || idx >= static_cast<int>(time_records.size()))
        throw std::runtime_error("Timer::getTimePoint: Time point index is out of range!");
    return time_records[idx].time;
}