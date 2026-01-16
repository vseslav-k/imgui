#pragma once
#include <string>
#include <vector>
#include <array>
#include "fstream"

enum LogLevel : int {Debug, Info, Warn, Error, Critical };
static bool log_to_file = true;
static bool log_to_cout = true;
static bool show_log_window = true;

static std::string log_file_path = "C:\\Users\\vsesl\\OneDrive\\Documents\\log.txt";
static std::ofstream log_file(log_file_path);
static std::vector<std::pair<std::string, LogLevel>> log_lines;
static int lastIdx = 0;
static std::array<bool, 5> log_level_enabled = { true, true, true, true, true };
const static std::array<std::string, 5> log_level_names = { "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL" };

const static std::array<ImVec4, 5> log_level_colors = { ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 
                                                  ImVec4(0.5f, 0.5f, 0.5f, 1.0f), 
                                                  ImVec4(1.0f, 1.0f, 0.0f, 1.0f), 
                                                  ImVec4(1.0f, 0.3f, 0.3f, 1.0f), 
                                                  ImVec4(0.7f, 0.0f, 0.0f, 1.0f) };

void DrawLogWindow();

template <class num>
std::string numToStr(num n, int precision = -1);

template <class num>
std::string numToStrBin(num n, int precision = -1);


template <class flt>
std::string fltToStrSci(flt n, int precision = 4);

template <class flt>
std::string fltToStr(flt n, int precision = 4);

template <class typ>
std::string ptrToStr(typ* p, int size = 1, std::string (*logger)(typ, int) = nullptr, const std::string& seperator = ", ", int precision = 4);


void log(const LogLevel lvl, const std::string& item, const std::string& seperator = "\n");
void logToCout(const LogLevel lvl, const std::string& item, const std::string& seperator = "\\endl");
void logToFile(const LogLevel lvl, const std::string& item, const std::string& seperator = "\\endl");


#include "logger.tpp"