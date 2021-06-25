#pragma once

#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #error Unsupported platform (only supports windows 32 or 64 (for now!))
#endif

namespace Willog {

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
        static bool s_ShowFP;
        static bool s_ShowLine;
        static LogLevel s_Level;

    public:
        static HANDLE s_Console;

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

    inline LogLevel State::s_Level = LogLevel::ALL;
    inline HANDLE State::s_Console;
    inline bool State::s_ShowFP = true;
    inline bool State::s_ShowLine = true;

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

    static inline void LogMsg(LogLevel level, std::string s)
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

    static inline int GetColorAttrib(LogColor color) // Get Color code?
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

    inline void SetColor(LogColor color)
    {
        SetConsoleTextAttribute(State::s_Console, GetColorAttrib(color));
    }

    inline void Fatal(std::string s)
    {
        SetColor(RED);
        s = "FATAL: " + s;
        LogMsg(LogLevel::FATAL, s);
    }
    inline void Error(std::string s) {
        SetColor(RED);
        s = "ERROR: " + s;
        LogMsg(LogLevel::ERR, s);
    }
    inline void Warning(std::string s)
    {
        SetColor(YELLOW);
        s = "WARN: " + s;
        LogMsg(LogLevel::WARN, s);
    }
    inline void Info(std::string s) {
        SetColor(WHITE);
        s = "INFO: " + s;
        LogMsg(LogLevel::INFO, s);
    }
    inline void Debug(std::string s) {
        SetColor(GREEN);
        s = "DEBUG: " + s;
        LogMsg(LogLevel::DEBUG, s);
    }
    inline void Trace(std::string s) {
        SetColor(WHITE);
        s = "TRACE: " + s;
        LogMsg(LogLevel::TRACE, s);
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