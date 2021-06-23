#pragma once

#include <iostream>
#include <sstream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define SET_BLACK() SetConsoleTextAttribute(hConsole, 0);
#define SET_WHITE() SetConsoleTextAttribute(hConsole, 15);
#define SET_BLUE() SetConsoleTextAttribute(hConsole, 9);
#define SET_GREEN() SetConsoleTextAttribute(hConsole, 10);
#define SET_CYAN() SetConsoleTextAttribute(hConsole, 11);
#define SET_RED() SetConsoleTextAttribute(hConsole, 12);
#define SET_PURPLE() SetConsoleTextAttribute(hConsole, 13);
#define SET_YELLOW() SetConsoleTextAttribute(hConsole, 14);
#define SET_GREY() SetConsoleTextAttribute(hConsole, 8);
#else
#error Unsupported platform (only supports windows 32 or 64 (for now!))
#endif

namespace Willog {

    enum LogLevel
    {
        OFF = 0,
        FATAL = 1,
        ERR = 2,
        WARN = 3,
        INFO = 4,
        DEBUG = 5,
        TRACE = 6,
        ALL = 7
    };

    class State
    {
    private:
        static bool s_ShowFP;
        static bool s_ShowLine;
        static LogLevel s_Level;

    public:
        inline static bool CheckLevel(LogLevel l)
        {
            return l <= s_Level;
        }

        inline static LogLevel GetLevel() { return s_Level; }
        inline static void SetLevel(LogLevel level) { s_Level = level; }

        inline static void ShowFP() { s_ShowFP = true; }
        inline static void HideFP() { s_ShowFP = false; }
        inline static bool IsFPShowing() { return s_ShowFP; }

        inline static void ShowLine() { s_ShowLine = true; }
        inline static void HideLine() { s_ShowLine = false; }
        inline static bool IsLineShowing() { return s_ShowLine; }
    };

    LogLevel State::s_Level = LogLevel::ALL;
    bool State::s_ShowFP = true;
    bool State::s_ShowLine = true;

    State s_LOG_INST;

    void Init()
    {
#if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
#endif

        // Make output faster by ...

        std::ios::sync_with_stdio(false); // toggle on or off the synchronization of all the C++ standard streams with their corresponding standard C streams
        std::cin.tie(NULL); // guarantee the flushing of std::cout before std::cin accepts an input
        std::cout.tie(NULL); // ... and vise-versa

        s_LOG_INST = State();
    }

    void LogMsg(LogLevel level, std::string s)
    {
        if (State::CheckLevel(level))
        {
            if(State::IsFPShowing()) {
                std::cout << "[" << __FILE__ << "] ";
            }
            if(State::IsLineShowing()) {
                std::cout << "(Line: " << __LINE__ << ") ";
            }
            std::cout << s << '\n';
        }
    }

    inline void SetLogLevel(LogLevel level) { State::SetLevel(level); }
    inline LogLevel GetLogLevel() { return State::GetLevel(); }
    inline void HideFP() { State::HideFP(); }
    inline void ShowFP() { State::ShowFP(); }
    inline void HideLine() { State::HideLine(); }
    inline void ShowLine() { State::ShowLine(); }

    void Fatal(std::string s)
    {
        SET_RED();
        s = "FATAL: " + s;
        LogMsg(LogLevel::FATAL, s);
    }
    void Error(std::string s) {
        SET_RED();
        s = "ERROR: " + s;
        LogMsg(LogLevel::ERR, s);
    }
    void Warning(std::string s)
    {
        SET_YELLOW();
        s = "WARN: " + s;
        LogMsg(LogLevel::WARN, s);
    }
    void Info(std::string s) {
        SET_WHITE();
        s = "INFO: " + s;
        LogMsg(LogLevel::INFO, s);
    }
    void Debug(std::string s) {
        SET_GREEN();
        s = "DEBUG: " + s;
        LogMsg(LogLevel::DEBUG, s);
    }
    void Trace(std::string s) {
        SET_WHITE();
        s = "TRACE: " + s;
        LogMsg(LogLevel::TRACE, s);
    }

    double Clamp(double v, double max, double min)
    {
        if(v > max)
        {
            return max;
        } else if (v < min)
        {
            return min;
        } else {
            return v;
        }
    }

    double RoundOff(double value, unsigned char prec)
    {
        double pow_10 = pow(10.0f, (float)prec);
        return round(value * pow_10) / pow_10;
    }
}