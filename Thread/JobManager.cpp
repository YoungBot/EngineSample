#include <Windows.h>
#include "Jobmanager.hpp"

void CJobThread::ProcessAll()
{
	while (job_manager->RunJob()) {}
}

void CJobThread::Run()
{
	while (job_manager->is_running())
	{
		ProcessAll();
		yield();
	}

	ProcessAll();
}

CJobThread::CJobThread(CJobManager *manager)
{
	job_manager = manager;
}

void CJobManager::Init(int num_threads)
{
	running = true;
	AddThreads(num_threads);
}

void CJobManager::AddThreads(int num_threads)
{
	num_threads;
	CJobThread *job_thread = new CJobThread(this);
	job_thread->Start("job_thread");

	threads.push_back(job_thread);
}

void CJobManager::Shutdown()
{
	running = false;
	while (threads.size() > 0) {
		CThread *thread = threads.front();
		thread->Join();
		delete thread;

		threads.pop_front();
	}

	// finish out finished jobs
	Update();
}

void CJobManager::Update()
{
	if (threads.size() == 0) {
		RunJob();
	}

	CJob *finished_job;
	while (finished_jobs.Dequeue(&finished_job)) {
		if (finished_job->complete_cb != nullptr) {
			finished_job->complete_cb(finished_job->arg);
		}

		delete finished_job;
	}
}

void CJobManager::AddMyJob(CJob *job, ePriority priority, job_complete_cb on_complete, void *arg)
{
	job->complete_cb = on_complete;
	job->arg = arg;
	queued_jobs[priority].Enqueue(job);
}

bool CJobManager::RunJob()
{
	CJob *job;
	for (int p = EPRIORITY_HIGH; p >= EPRIORITY_LOW; --p)
	{

		if (queued_jobs[p].Dequeue(&job)) {
			job->Run();
			finished_jobs.Enqueue(job);
			return true;
		}

		//return false;
	}
	return false;
}

unsigned int SystemGetCoreCount()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return (unsigned int)sysinfo.dwNumberOfProcessors;
}