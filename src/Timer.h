#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
public:
	inline static void Start();
	inline static double Stop();
protected:
	static clock_t start;
};


inline void Timer::Start()
{
	start = clock();
}

inline double Timer::Stop()
{
	clock_t finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

#endif