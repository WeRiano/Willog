#pragma once

#include <iostream>
#include <string>

#define __cpp_consteval
#include <source_location>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #error Unsupported platform (only supports windows 32 or 64 (for now!))
#endif

namespace Willog {

    struct LogInfo
    {
        std::string fileName, functionName;
        unsigned int line;
        LogInfo(std::string fen, std::string fnn, unsigned int l)
            : fileName(fen), functionName(fnn), line(l)
        {}
    };

    enum LogColor
    {
        BLACK, WHITE, BLUE, GREEN, CYAN,
        RED, PURPLE, YELLOW, GREY
    };

    enum LogLevel
    {
        OFF = 0, FATAL = 1, ERR = 2, WARN = 3, INFO = 4, DEBUG = 5, TRACE = 6,
        ALL = 7
    };

    class State
    {
    private:
        inline static bool s_ShowFP = false;
        inline static bool s_ShowLine = false;
        inline static bool s_ShowFunc = false;
        inline static LogLevel s_Level = LogLevel::ALL;

    public:
        inline static HANDLE s_Console;

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

        inline static void ShowFunc() { s_ShowFunc = true; }
        inline static void HideFunc() { s_ShowFunc = false; }
        inline static bool IsFuncShowing() { return s_ShowFunc; }
    };

    inline State s_LOG_INST;

    inline void Init()
    {
#if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
#endif
        // Make output faster by ...
        std::ios::sync_with_stdio(false); // toggle on or off the synchronization of all the C++ standard streams with their corresponding standard C streams
        std::cin.tie(NULL); // guarantee the flushing of std::cout before std::cin accepts an input
        std::cout.tie(NULL); // ... and vise-versa

        s_LOG_INST = State();
        State::s_Console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    static inline void LogMsg(LogLevel level, std::string s, LogInfo info)
    {
        if (State::CheckLevel(level))
        {
            if(State::IsFPShowing()) {
                std::cout << "[" << info.fileName << "] ";
            }
            if(State::IsFuncShowing())
            {
                std::cout << "[" << info.functionName << "] ";
            }
            if(State::IsLineShowing()) {
                std::cout << "(Line: " << info.line << ") ";
            }
            std::cout << s << '\n';
        }
    }

    // These exist because I dont want the user to have to use the State class. TODO: Maybe rethink?
    inline void SetLogLevel(LogLevel level) { State::SetLevel(level); }
    inline LogLevel GetLogLevel() { return State::GetLevel(); }
    inline void HideFP() { State::HideFP(); }
    inline void ShowFP() { State::ShowFP(); }
    inline void HideLine() { State::HideLine(); }
    inline void ShowLine() { State::ShowLine(); }
    inline void HideFunc() { State::HideFunc(); }
    inline void ShowFunc() { State::ShowFunc(); }

    static inline int GetColorAttrib(LogColor color) // "GetColorCode"
    {
        switch (color) {
            case BLACK:
                return 0;
            case WHITE:
                return 15;
            case BLUE:
                return 9;
            case GREEN:
                return 10;
            case CYAN:
                return 11;
            case RED:
                return 12;
            case PURPLE:
                return 13;
            case YELLOW:
                return 14;
            case GREY:
                return 8;
        }
    }

    static inline void SetColor(LogColor color)
    {
        SetConsoleTextAttribute(State::s_Console, GetColorAttrib(color));
    }

    inline void Fatal(std::string s, std::source_location sl = std::source_location::current())
    {
        SetColor(RED);
        s = "FATAL: " + s;
        LogMsg(LogLevel::FATAL, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }
    inline void Error(std::string s, std::source_location sl = std::source_location::current()) {
        SetColor(RED);
        s = "ERROR: " + s;
        LogMsg(LogLevel::ERR, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }
    inline void Warning(std::string s, std::source_location sl = std::source_location::current())
    {
        SetColor(YELLOW);
        s = "WARN: " + s;
        LogMsg(LogLevel::WARN, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }
    inline void Info(std::string s, std::source_location sl = std::source_location::current()) {
        SetColor(WHITE);
        s = "INFO: " + s;
        LogMsg(LogLevel::INFO, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }
    inline void Debug(std::string s, std::source_location sl = std::source_location::current()) {
        SetColor(GREEN);
        s = "DEBUG: " + s;
        LogMsg(LogLevel::DEBUG, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }
    inline void Trace(std::string s, std::source_location sl = std::source_location::current()) {
        SetColor(WHITE);
        s = "TRACE: " + s;
        LogMsg(LogLevel::TRACE, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
    }

    inline double Clamp(double v, double max, double min)
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

    inline double RoundOff(double value, unsigned char prec)
    {
        double pow_10 = pow(10.0f, (float)prec);
        return round(value * pow_10) / pow_10;
    }
}