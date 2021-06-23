#pragma once

#include "Willog.hpp"

namespace Willog {

    enum ProgBarType {
        squares = 0,
        dots = 1,
        circles = 2,
        bars = 3
    };

    class ProgBar
    {
    private:
        unsigned int m_Prog; // symbols
        unsigned int m_Length; // symbols
        ProgBarType m_Type;

    public:
        ProgBar(unsigned int symbolLength, ProgBarType pbt)
                : m_Prog(0), m_Length(symbolLength),
                  m_Type(pbt)
        {}

        void Display()
        {
            std::string res;
            for(unsigned int i = 1; i <= m_Length; i++)
            {
                res += GetSymbol(i);
            }
            if(m_Prog)
            {
                if(m_Prog <= m_Length) {
                    res = "\r" + res;
                }
            } else {

            }
            std::string whole = std::to_string((double) m_Prog/m_Length*100);
            std::string left = whole.substr(0, whole.find('.'));
            std::string right = whole.substr(whole.find('.'), 3);
            whole = left + right;

            res += " \t" + whole + "%";
            if(m_Prog >= m_Length) {
                res = res + "\n";
            }

            std::cout << res << std::flush;
        }

        // Update the internal state of the bar
        // Negative values moves it backwards
        void UpdateProg(int deltaSymbols)
        {
            m_Prog += deltaSymbols;
            m_Prog = Clamp(m_Prog, m_Length, 0);
        }

        void SetProg(double frac)
        {
            double dProg = (m_Length * Clamp(frac, 1.0, 0.0));
            //std::cout << dProg << std::endl;
            m_Prog = round(dProg);
        }

    private:
        std::string GetSymbol(unsigned int symbolNr)
        {
            if(symbolNr <= m_Prog)
            {
                switch(m_Type)
                {
                    case squares:
                        return ProgBar::s_SqComp;
                    case dots:
                        return ProgBar::s_DotComp;
                    case circles:
                        return ProgBar::s_CircComp;
                    case bars:
                        return ProgBar::s_BarComp;
                }
            } else
            {
                switch(m_Type)
                {
                    case squares:
                        return ProgBar::s_SqUn;
                    case dots:
                        return ProgBar::s_DotUn;
                    case circles:
                        return ProgBar::s_CircUn;
                    case bars:
                        return ProgBar::s_BarUn;
                }
            }
        }

        static std::string s_CircUn;
        static std::string s_CircComp;
        static std::string s_DotUn;
        static std::string s_DotComp;
        static std::string s_SqUn;
        static std::string s_SqComp;
        static std::string s_BarUn;
        static std::string s_BarComp;
    };

    std::string ProgBar::s_CircUn = "⚪";
    std::string ProgBar::s_CircComp = "⚫";
    std::string ProgBar::s_DotUn = "⣀";
    std::string ProgBar::s_DotComp = "⣿";
    std::string ProgBar::s_SqUn = "⬜";
    std::string ProgBar::s_SqComp = "⬛";
    std::string ProgBar::s_BarUn = "▁";
    std::string ProgBar::s_BarComp = "█";
}