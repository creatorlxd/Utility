#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

void ThrowError(const string& str)
{
	cout<<str<<endl;
	abort();
}

using namespace std::chrono;

int GetClock()
{
	return clock()/CLOCKS_PER_SEC;
}

double GetDeltaTime()
{
	static steady_clock::time_point TimeNow=steady_clock::now();
	static steady_clock::time_point TimeBuffer;
	static duration<double> time_span;
	TimeBuffer = steady_clock::now();
	time_span = duration_cast<duration<double>>(TimeBuffer - TimeNow);
	TimeNow = steady_clock::now();
	return time_span.count();
}

struct TimeTest
{
	steady_clock::time_point m_BeginTime;
	steady_clock::time_point m_EndTime;
	bool m_IfEnd=false;
	double m_Content=0.00f;

	void Begin()
	{
		m_BeginTime=steady_clock::now();
	}
	void End()
	{
		m_EndTime=steady_clock::now();
		duration<double> time_span=duration_cast<duration<double>>(m_EndTime-m_BeginTime);
		m_Content=time_span.count();
		m_IfEnd=true;
	}
	double GetContent()
	{
		if(!m_IfEnd)
		{
			ThrowError("this timetest has not end yet");
		}
		else
		{
			return m_Content;
		}
	}
};
