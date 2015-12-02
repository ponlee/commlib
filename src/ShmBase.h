/**********************************
 * File: ShmBase.hpp
 * Author: ponlee
 * Version: 1.0
 * Date: 2015-08
 * Desc: �����ڴ�shm������
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
	** @DESC:   ���������ڴ棻����key,size�½������ڴ棬�������򴴽���
	**			�������޽���ʹ��ʱɾ�����еĲ������µ�
	** @Input:	key(ftok���ص�IPC��ֵ),iShmSize(�����������ڴ��С)
	** @Output:	����ָ��ö��ڴ��ָ��
	*************************************************/
	void* CreateShm( key_t iShmKey,int iShmSize, bool bInitClear = true );

	void* OpenShm( );

	/*************************************************
	** @DESC:   �رչ����ڴ�
	** @Output:
	**		0=>�ɹ��� -1=> ʧ��
	*************************************************/
	int32_t CloseShm();

	uint64_t GetShmid() { return m_shmid; }
	void* GetShmptr()  { return m_pShm; }

	bool IsNewCreate() { return m_isNewCreate; }
	int32_t	GetErrno() { return m_errno; }
	const std::string&	GetErrMsg()	{ return m_strErrMsg; }

private:

	uint64_t	m_shmid;		//�����ڴ�ID
	uint64_t	m_ddwShmSize;	//�����ڴ�Ĵ�С
	void*		m_pShm;			//�����ڴ��ָ��

	bool		m_isNewCreate;	//�Ƿ�Ϊ�´���
	int32_t		m_errno;		//������
	std::string m_strErrMsg;	//������Ϣ
};

#endif
