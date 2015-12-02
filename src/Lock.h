/**********************************
 * File: Lock.hpp
 * Author:ponlee
 * Version:1.0
 * Date: 2014-04
 * Desc: mutexlock/spinlock的RAII封装
***********************************/

#ifndef _LOCK_HPP__
#define _LOCK_HPP__

#include <cstdio>
#include <pthread.h>

/***********spinlock 内核代码实现(比pthread_spinlock_t更高效)*********************************

#define LOCK "lock ; "

#define __raw_spin_lock_string \
	"\n1:\t" \
	LOCK \
	"decb %0\n\t" \
	"jns 3f\n" \
	"2:\t" \
	"rep;nop\n\t" \
	"cmpb $0,%0\n\t" \
	"jle 2b\n\t" \
	"jmp 1b\n" \
	"3:\n\t"

typedef struct {
	volatile unsigned int slock;
} raw_spinlock_t;

typedef struct {
	raw_spinlock_t raw_lock;
} spinlock_t;

static inline void __raw_spin_lock(raw_spinlock_t *lock)
{
	__asm__ __volatile__(
		__raw_spin_lock_string
		:"+m" (lock->slock) : : "memory");
}


#define __raw_spin_unlock_string \
	"movb $1,%0" \
	:"+m" (lock->slock) : : "memory"

static inline void __raw_spin_unlock(raw_spinlock_t *lock)
{
	__asm__ __volatile__(
		__raw_spin_unlock_string
		);
}

#define spin_lock_init(lock)    do {(lock)->raw_lock.slock = 1; } while (0)
#define spin_lock(lock) __raw_spin_lock(&(lock)->raw_lock)
#define spin_unlock(lock)  __raw_spin_unlock(&(lock)->raw_lock)
*****************************************************************/

/***********************************/
class SpinLock
{
public:
	SpinLock();
	~SpinLock();

	void Lock();
	void UnLock();
	int  TryLock();

private:
	pthread_spinlock_t	m_spinlock;
};

/***********************************/
class MutexLock
{
public:
	MutexLock();
	~MutexLock();

	void Lock();
	void UnLock();
	int  TryLock();

	pthread_mutex_t* GetThreadMutex();

private:
	MutexLock( const MutexLock& );
	MutexLock& operator=( const MutexLock& );

private:
	pthread_mutex_t m_mutex;
	pthread_mutexattr_t m_mattr;    //互斥锁属性设置

};


template <typename _Mutex>
class Lock
{
public:
	explicit Lock( _Mutex mutex )
		:m_mutex(mutex)
	{
		m_mutex.Lock();
	}
	~Lock()
	{
		m_mutex.UnLock();
	}

private:
	Lock( const Lock& lock );
	Lock& operator=( const Lock& lock );

private:
	_Mutex m_mutex;
};



#endif
