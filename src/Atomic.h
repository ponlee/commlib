/**********************************
 * File: Atomic.h
 * Author: ponlee
 * Version: 1.0
 * Date: 2015-08-27
 * Desc: gcc 内置原子内存整数存取函数簇封装
***********************************/

#ifndef __COMM_ATOMIC_HPP_
#define __COMM_ATOMIC_HPP_

#include <stdint.h>

template<typename T>
class AtomicIntegerT
{
private:
	AtomicIntegerT( const noncopyable& );
	const AtomicIntegerT& operator=( const AtomicIntegerT& );

public:
	AtomicIntegerT()
		: value_(0)
	{
	}

	/**************************************
	** @DESC 原子获取接口
	**
	***************************************/
	T AtomicGet()
	{
		return __sync_val_compare_and_swap(&value_, 0, 0);
	}

	/**************************************
	** @DESC 原子加操作接口,先返回原来值，再加
	**
	***************************************/
	T AtomicGetAndAdd(T x)
	{
		return __sync_fetch_and_add(&value_, x);
	}
	/**************************************
	** @DESC 原子加操作接口,先原子加操作再将新值返回
	***************************************/
	T AtomicAddAndGet(T x)
	{
		return __sync_add_and_fetch(&value_, x);
	}

	/**************************************
	** @DESC 原子自增接口
	***************************************/
	void AtmoicIncr()
	{
		AtomicGetAndAdd( 1 );
	}

	/**************************************
	** @DESC 原子自减接口
	***************************************/
	void AtomicDecr()
	{
		AtomicGetAndAdd( -1 );
	}

	/**************************************
	** @DESC 原子赋值接口；将value赋值给value_，返回赋值前的value_
	** 
	***************************************/
	T AtomicGetAndSet(T newValue)
	{
		return __sync_lock_test_and_set(&value_, newValue);
	}

private:
	volatile T _value;
};

//特例化两种整数类型 
typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;

#endif
