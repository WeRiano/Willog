#pragma once

#include <iostream>
#include <string>
#include <format>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #error Unsupported platform (only supports windows 32 or 64 (for now!))
#endif

namespace Willog {

    struct LogInfo
    {
        std::string fileName, functionName, filePath;
        unsigned int line;
        LogInfo(const std::string& fileNameAndPath, std::string funcName,
                unsigned int line)
            : functionName(std::move(funcName)), line(line)
        {
            SplitFilePathAndName(fileNameAndPath);
        }

        void SplitFilePathAndName(const std::string& fileNameAndPath) {
            std::size_t fileNameStart = fileNameAndPath.find_last_of('\\') + 1;
            filePath = fileNameAndPath.substr(0, fileNameStart - 1);
            fileName = fileNameAndPath.substr(fileNameStart);
        };
    };

    enum LogColor
    {
        BLACK, WHITE,  BLUE,   GREEN, CYAN,
        RED,   PURPLE, YELLOW, GREY
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
        inline static bool s_ShowFN = false;
        inline static bool s_ShowLine = false;
        inline static bool s_ShowFunc = false;
        inline static LogLevel s_Level = LogLevel::ALL;

    public:
        #if defined(_WIN32) || defined(_WIN64)
        inline static HANDLE s_Console;
        #endif

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

        inline static void ShowFN() { s_ShowFN = true; }
        inline static void HideFN() { s_ShowFN = false; }
        inline static bool IsFNShowing() { return s_ShowFN; }

        inline static void ShowLine() { s_ShowLine = true; }
        inline static void HideLine() { s_ShowLine = false; }
        inline static bool IsLineShowing() { return s_ShowLine; }

        inline static void ShowFunc() { s_ShowFunc = true; }
        inline static void HideFunc() { s_ShowFunc = false; }
        inline static bool IsFuncShowing() { return s_ShowFunc; }
    };

    inline void Init()
    {
        #if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
        #endif
        // Make output faster by ...
        std::ios::sync_with_stdio(false); // toggle on or off the synchronization of all the C++ standard streams with their corresponding standard C streams
        std::cin.tie(NULL); // guarantee the flushing of std::cout before std::cin accepts an input
        std::cout.tie(NULL); // ... and vise-versa

        #if defined(_WIN32) || defined(_WIN64)
        State::s_Console = GetStdHandle(STD_OUTPUT_HANDLE);
        #endif
    }

    // These exist because I don't want the user to have to use the State class.
    inline void SetLogLevel(LogLevel level) { State::SetLevel(level); }
    inline LogLevel GetLogLevel() { return State::GetLevel(); }
    inline void HideFP() { State::HideFP(); }
    inline void ShowFP() { State::ShowFP(); }
    inline void HideFN() { State::HideFN(); }
    inline void ShowFN() { State::ShowFN(); }
    inline void HideLine() { State::HideLine(); }
    inline void ShowLine() { State::ShowLine(); }
    inline void HideFunc() { State::HideFunc(); }
    inline void ShowFunc() { State::ShowFunc(); }

    #if defined(_WIN32) || defined(_WIN64)
    static inline int GetColorAttrib(const LogColor& color) // "GetColorCode"
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
            default:
                return 15; // White is default for now
        }
    }
    #endif

    #if defined(_WIN32) || defined(_WIN64)
    static inline short SetColor(const LogColor& color)
    {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(State::s_Console, &info); // TODO: Error handling
            SetConsoleTextAttribute(State::s_Console, GetColorAttrib(color));
            return info.wAttributes;
    }

    static inline short SetColor(unsigned int colorAttrib)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(State::s_Console, &info); // TODO: Error handling
        SetConsoleTextAttribute(State::s_Console, colorAttrib);
        return info.wAttributes;
    }
    #endif

    // TODO: Misleading function name! Message is being printed here as well
    template <typename... Args>
    static inline void PrepareMsg(const char* fileName,
                                  unsigned int line,
                                  const char* funcName,
                                  const LogColor& color,
                                  const LogLevel& level,
                                  const std::string& prefix,
                                  const std::string& msg, Args... args)
    {
        auto oldColor = SetColor(color);
        const LogInfo info = LogInfo(std::string(fileName), std::string(funcName), line);
        LogMsg(level, info, prefix + msg, args...);
        SetColor(oldColor);
    }

    template <typename... Args>
    static inline void LogMsg(const LogLevel& level,
                              const LogInfo& info,
                              const std::string& msg, Args... args)
    {
        if (State::CheckLevel(level))
        {
            std::string logInfoOutput;
            if(State::IsFPShowing()) {
                logInfoOutput = "[" + info.filePath + "] ";
            }
            if(State::IsFNShowing()) {
                logInfoOutput += "[" + info.fileName + "] ";
            }
            if(State::IsFuncShowing())
            {
                logInfoOutput += "[" + info.functionName + "] ";
            }
            if(State::IsLineShowing()) {
                logInfoOutput += "(" + std::to_string(info.line) + ") ";
            }
            std::cout << std::vformat(logInfoOutput +
                         msg, std::make_format_args(args...)) << std::endl;
        }
    }

    /*
     * Deprecated, saving for the future when we can avoid macros perhaps ...
     *
    inline void Fatal(std::string s, std::source_location sl = std::source_location::current())
    {
        auto oldColor = SetColor(RED);
        s = "FATAL: " + s;
        LogMsg(LogLevel::FATAL, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }

    inline void Error(std::string s, std::source_location sl = std::source_location::current()) {
        auto oldColor = SetColor(RED);
        s = "ERROR: " + s;
        LogMsg(LogLevel::ERR, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }
    inline void Warning(std::string s, std::source_location sl = std::source_location::current())
    {
        auto oldColor = SetColor(YELLOW);
        s = "WARN: " + s;
        LogMsg(LogLevel::WARN, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }
    inline void Info(std::string s, std::source_location sl = std::source_location::current()) {
        auto oldColor = SetColor(WHITE);
        s = "INFO: " + s;
        LogMsg(LogLevel::INFO, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }
    inline void Debug(std::string s, std::source_location sl = std::source_location::current()) {
        auto oldColor = SetColor(GREEN);
        s = "DEBUG: " + s;
        LogMsg(LogLevel::DEBUG, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }
    inline void Trace(std::string s, std::source_location sl = std::source_location::current()) {
        auto oldColor = SetColor(WHITE);
        s = "TRACE: " + s;
        LogMsg(LogLevel::TRACE, s, LogInfo(sl.file_name(), sl.function_name(), sl.line()));
        SetColor(oldColor);
    }
     */
}

#define WILLOG_TRACE(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::WHITE, Willog::LogLevel::TRACE, "[TRACE] ", s, __VA_ARGS__)
#define WILLOG_DEBUG(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::GREEN, Willog::LogLevel::DEBUG, "[DEBUG] ", s, __VA_ARGS__)
#define WILLOG_INFO(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::WHITE, Willog::LogLevel::INFO, "[INFO] ", s, __VA_ARGS__)
#define WILLOG_WARN(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::YELLOW, Willog::LogLevel::WARN, "[WARNING] ", s, __VA_ARGS__)
#define WILLOG_ERROR(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::RED, Willog::LogLevel::ERR, "[ERROR] ", s, __VA_ARGS__)
#define WILLOG_FATAL(s, ...) PrepareMsg(__FILE__, __LINE__, __func__, Willog::LogColor::RED, Willog::LogLevel::FATAL, "[FATAL] ", s, __VA_ARGS__)