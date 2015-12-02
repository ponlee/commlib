#include "Lock.h"

//###################################################################
SpinLock::SpinLock()
{
	//PTHREAD_PROCESS_SHARED  PTHREAD_PROCESS_PRIVATE 
	pthread_spin_init( &m_spinlock, PTHREAD_PROCESS_SHARED ); 
}

SpinLock::~SpinLock()
{
	pthread_spin_destroy( &m_spinlock );
}

void SpinLock::Lock()
{
	pthread_spin_lock( &m_spinlock );
}

void SpinLock::UnLock()
{
	pthread_spin_unlock( &m_spinlock );
}

int SpinLock::TryLock()
{
	return pthread_spin_trylock( &m_spinlock );
}

//###################################################################
MutexLock::MutexLock()
{
	pthread_mutex_init( &m_mutex, NULL );
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy( &m_mutex );
}

void MutexLock::Lock()
{
	pthread_mutex_lock( &m_mutex );
}

void MutexLock::UnLock()
{
	pthread_mutex_unlock( &m_mutex );
}

int MutexLock::TryLock()
{
	return pthread_mutex_trylock( &m_mutex );
}

pthread_mutex_t* MutexLock::GetThreadMutex()
{
	return &m_mutex;
}

//###################################################################
