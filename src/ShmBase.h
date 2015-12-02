/**********************************
 * File: ShmBase.hpp
 * Author: ponlee
 * Version: 1.0
 * Date: 2015-08
 * Desc: 共享内存shm操作类
***********************************/

#ifndef _SHM_BASE_HPP__
#define _SHM_BASE_HPP__

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>
#include <errno.h>
#include <cstring>
#include <string>

class ShmAdapter
{
public:
	ShmAdapter()
		: m_shmid(0)
		, m_ddwShmSize(0)
		, m_pShm(NULL)
		, m_isNewCreate(false)
		, m_errno(0)
	{}

	~ShmAdapter()
	{
		if ( m_pShm )
		{
			shmdt(m_pShm);
			m_pShm = NULL;
		}
	}

public:
	/*************************************************
	** @DESC:   创建共享内存；根据key,size新建共享内存，不存在则创建，
	**			存在且无进程使用时删除已有的并创建新的
	** @Input:	key(ftok返回的IPC键值),iShmSize(所创建共享内存大小)
	** @Output:	返回指向该段内存的指针
	*************************************************/
	void* CreateShm( key_t iShmKey,int iShmSize, bool bInitClear = true );

	void* OpenShm( );

	/*************************************************
	** @DESC:   关闭共享内存
	** @Output:
	**		0=>成功， -1=> 失败
	*************************************************/
	int32_t CloseShm();

	uint64_t GetShmid() { return m_shmid; }
	void* GetShmptr()  { return m_pShm; }

	bool IsNewCreate() { return m_isNewCreate; }
	int32_t	GetErrno() { return m_errno; }
	const std::string&	GetErrMsg()	{ return m_strErrMsg; }

private:

	uint64_t	m_shmid;		//共享内存ID
	uint64_t	m_ddwShmSize;	//共享内存的大小
	void*		m_pShm;			//共享内存的指针

	bool		m_isNewCreate;	//是否为新创建
	int32_t		m_errno;		//错误码
	std::string m_strErrMsg;	//错误信息
};

#endif
