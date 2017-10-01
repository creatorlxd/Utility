#include "Game.h"

Game::Game()
{
	m_IfOver = false;
	m_ComputeThread = thread([&]()->void
	{
		unique_lock<mutex> locker(m_Mutex);
		m_BeginConditionVariable.wait(locker);
		locker.unlock();
		int lasttime = 0;
		int thistime = 0;
		while (!m_IfOver)
		{
			lasttime = timeGetTime();
			locker.lock();
			Compute();
			locker.unlock();
			thistime = timeGetTime();
			//Sleep(1000 - (thistime - lasttime));
			std::this_thread::sleep_for(chrono::milliseconds(1000 - (thistime - lasttime)));
		}
	});
}

Game::~Game()
{
	m_IfOver = true;
	while (!m_ComputeThread.joinable())
		this_thread::sleep_for(chrono::seconds(1));
	m_ComputeThread.join();
}

void Game::Begin()
{
	m_BeginConditionVariable.notify_all();
}

void Game::End()
{
	m_IfOver = true;
}

void Game::Compute()
{
	
}
