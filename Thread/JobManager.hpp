#pragma once
#if !defined(__JOB_MANAGER__)
#define __JOB_MANAGER__



#include <list>
#include "ThreadSafeQueue.hpp"
#include "Thread.hpp"

typedef void(*job_complete_cb)(void *arg);

class CJob
{
	friend class CJobManager;

private:
	job_complete_cb complete_cb;
	void *arg;

public:
	virtual void Run() = 0;
};


class CJobThread : public CThread
{
private:
	CJobManager *job_manager;

	void ProcessAll();

protected:
	virtual void Run();

public:
	CJobThread(CJobManager *manager);
};


enum ePriority
{
	EPRIORITY_LOW = 0,
	EPRIORITY_MEDIUM=1,
	EPRIORITY_HIGH=2,
	EPRIORITY_COUNT
};


class CJobManager
{
	friend class CJobThread;

private:
	bool running;
	std::list<CThread*> threads;

	CThreadSafeQueue<CJob*> queued_jobs[EPRIORITY_COUNT];
	CThreadSafeQueue<CJob*> finished_jobs;

public:
	void Init(int num_threads);
	void AddThreads(int num_threads);

	inline bool is_running() const { return running; }

	void Shutdown();

	void Update();
	bool RunJob();

	void AddMyJob(CJob *job, ePriority priority, job_complete_cb on_complete, void *arg);
};

unsigned int SystemGetCoreCount();

#endif