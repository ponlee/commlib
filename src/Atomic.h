/**********************************
 * File: Atomic.h
 * Author: ponlee
 * Version: 1.0
 * Date: 2015-08-27
 * Desc: gcc ����ԭ���ڴ�������ȡ�����ط�װ
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
	** @DESC ԭ�ӻ�ȡ�ӿ�
	**
	***************************************/
	T AtomicGet()
	{
		return __sync_val_compare_and_swap(&value_, 0, 0);
	}

	/**************************************
	** @DESC ԭ�ӼӲ����ӿ�,�ȷ���ԭ��ֵ���ټ�
	**
	***************************************/
	T AtomicGetAndAdd(T x)
	{
		return __sync_fetch_and_add(&value_, x);
	}
	/**************************************
	** @DESC ԭ�ӼӲ����ӿ�,��ԭ�ӼӲ����ٽ���ֵ����
	***************************************/
	T AtomicAddAndGet(T x)
	{
		return __sync_add_and_fetch(&value_, x);
	}

	/**************************************
	** @DESC ԭ�������ӿ�
	***************************************/
	void AtmoicIncr()
	{
		AtomicGetAndAdd( 1 );
	}

	/**************************************
	** @DESC ԭ���Լ��ӿ�
	***************************************/
	void AtomicDecr()
	{
		AtomicGetAndAdd( -1 );
	}

	/**************************************
	** @DESC ԭ�Ӹ�ֵ�ӿڣ���value��ֵ��value_�����ظ�ֵǰ��value_
	** 
	***************************************/
	T AtomicGetAndSet(T newValue)
	{
		return __sync_lock_test_and_set(&value_, newValue);
	}

private:
	volatile T _value;
};

//������������������ 
typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;

#endif
