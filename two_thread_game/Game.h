#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <functional>
#include <chrono>

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Begin();
	void End();
private:
	bool m_IfOver;
	mutex m_Mutex;
	thread m_ComputeThread;
	condition_variable m_BeginConditionVariable;
	void Compute();
};
