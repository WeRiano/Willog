#include "Willog.hpp"
#include "ProgBar.hpp"

#include <chrono>
#include <thread>

void DoWork()
{
    volatile int k = 0;
    for(int i = 0; i < 10000; i++)
    {
        for(int j = 0; j < 100000; j++)
        {
            k = i*j;
        }
    }
}

void TestProgBar()
{
    unsigned int l = 19;
    Willog::ProgBar pb = Willog::ProgBar(l, Willog::ProgBarType::squares);
    for(unsigned int i = 1; i <= 27 + 1; i++)
    {
        pb.Display();
        Sleep(500);
        pb.SetProg((double) (i) / 27 );
    }
}

int main()
{
    Willog::Init();

    TestProgBar();
}