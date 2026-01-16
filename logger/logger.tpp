#pragma once
#include "logger.h"
#include <charconv>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <iostream>


template <class num>
std::string numToStr(num n, int precision){
    static_assert(std::is_integral_v<num>, "numToStr requires an integral type");

    char buf[sizeof(num) * 8];
    std::to_chars_result r = std::to_chars(buf, buf + sizeof(num)* 8, n);
    return std::string(buf, r.ptr);
}

template <class num>
std::string numToStrBin(num n, int precision){
    static_assert((std::is_integral_v<num>), "numToStrBin requires an integral or floating-point type");
    using unum = std::make_unsigned_t<num>;
    unum v = static_cast<unum>(n);

    std::string result;
    result.reserve(sizeof(num)* 8);
    unum one = unum(1);
    for (int i = sizeof(num)* 8 - 1; i >= 0; --i) {
        result.push_back((v & (one << i)) ? '1' : '0');
    }

    return result;
}

template <class flt>
std::string fltToStr(flt n, int precision) {
    static_assert((std::is_floating_point_v<flt>), "fltToStr requires a floating-point type");

    std::ostringstream oss;
    oss.setf(std::ios::fixed, std::ios::floatfield);
    oss << std::setprecision(precision) << n;
    return oss.str();
}

template <class flt>
std::string fltToStrSci(flt n, int precision) {
    static_assert((std::is_floating_point_v<flt>), "fltToStrSci requires a floating-point type");

    std::ostringstream oss;
    oss.setf(std::ios::scientific, std::ios::floatfield);
    oss << std::setprecision(precision) << n;
    return oss.str();
}

std::string simpleStr(const std::string& s, int precision = -1){
    return s;
}



template <class typ>
std::string ptrToStr(typ* p, int size, std::string (*logger)(typ, int), const std::string& seperator, int precision){

    constexpr bool is_flt = std::is_floating_point_v<typ>;

    if (logger == nullptr){
        if constexpr (std::is_floating_point_v<typ>) 
            logger = fltToStr<typ>;
        else if constexpr (std::is_integral_v<typ>) 
            logger = numToStr<typ>;
        else if constexpr (std::is_same_v<std::decay_t<typ>, std::string>) 
            logger = simpleStr;
        else{
            std::string err = "ptrToStr: No default logger for this type. Please provide a custom logger function.";
            log(err, "\n", Error);
            std::cerr << err << std::endl;
            return err;
        }
    }



    std::string result;
    result.reserve(sizeof(typ) * size + seperator.length() * size); 

    for(int i = 0; i < size; ++i)
        result += logger(p[i], precision) + seperator;
    

    return result;
}

void log(const std::string& item, const LogLevel lvl){
    log_lines.push_back(std::make_pair(item + "\n", lvl));
}

void log(const std::string& item, const std::string& seperator, const LogLevel lvl){
    log_lines.push_back(std::make_pair(item + seperator, lvl));
}


void layoutButtons(){
    if (ImGui::Button("Clear")) {
        log_lines.clear();
    }

    ImGui::SameLine();
    if (ImGui::Button("Scroll to Bottom")) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::SameLine();
    if (ImGui::Button(log_level_enabled[0] ? "Debug: ON" : "Debug: OFF"))log_level_enabled[0] = !log_level_enabled[0];

    ImGui::SameLine();
    if (ImGui::Button(log_level_enabled[1] ? "Info: ON" : "Info: OFF"))log_level_enabled[1] = !log_level_enabled[1];

    ImGui::SameLine();
    if (ImGui::Button(log_level_enabled[2] ? "Warn: ON" : "Warn: OFF"))log_level_enabled[2] = !log_level_enabled[2];

    ImGui::SameLine();
    if (ImGui::Button(log_level_enabled[3] ? "Error: ON" : "Error: OFF"))log_level_enabled[3] = !log_level_enabled[3];

    ImGui::SameLine();
    if (ImGui::Button(log_level_enabled[4] ? "Critical: ON" : "Critical: OFF"))log_level_enabled[4] = !log_level_enabled[4];
}

void DrawLogWindow(){
    if (!show_log_window) return;
    
    ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);
    ImGui::Begin("Log", &show_log_window); 
    layoutButtons();


    ImGui::Separator();

    ImGui::BeginChild("LogScroll", ImVec2(0, 0), false,
                      ImGuiWindowFlags_HorizontalScrollbar);

  
    for (const std::pair<std::string, LogLevel>& line : log_lines) {
        if (log_level_enabled[line.second])
            ImGui::TextColored(log_level_colors[line.second], "%s", line.first.c_str());
    }
    // Auto-scroll to bottom
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();

    ImGui::End();
}