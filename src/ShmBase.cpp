#include <cstddef>
#include "ShmBase.h"

void* ShmAdapter::CreateShm( key_t iShmKey,int iShmSize, bool bInitClear /*= true */ )
{
	m_errno = 0;
	m_pShm = NULL;

	int m_shmid = shmget( iShmKey, iShmSize, IPC_CREAT|IPC_EXCL|0666);
	if( m_shmid < 0 )
	{
		m_isNewCreate = false;
		if(errno != EEXIST )
		{
			m_errno = errno;
			return NULL;
		}
		m_shmid = shmget( iShmKey, iShmSize, 0666);  //尝试重新新建
		if( m_shmid < 0 )
		{
			m_shmid = shmget( iShmKey, 0, 0666);//获取共享内存
			if( m_shmid < 0 )
			{
				m_errno = errno;
				return NULL;
			}
			else
			{
				struct shmid_ds s_ds;
				shmctl(m_shmid,IPC_STAT,&s_ds);		//获取共享内存状态
				if(s_ds.shm_nattch > 0)
				{
					m_errno = EEXIST;
					return NULL;
				}
				if( shmctl( m_shmid, IPC_RMID, NULL ) ) //无进程使用则删除
				{
					m_errno = errno;
					return NULL;
				}
				m_shmid = shmget( iShmKey, iShmSize, IPC_CREAT|IPC_EXCL|0666);
				if( m_shmid < 0 )
				{
					m_errno = errno;
					return NULL;
				}
				m_isNewCreate = true;
			}
		}
	}
	else
	{
		m_isNewCreate = true;
	}
	m_pShm = shmat( m_shmid, NULL, 0);
	m_ddwShmSize = iShmSize;

	if ( bInitClear && m_pShm )
		memset( m_pShm, 0, m_ddwShmSize );

	return m_pShm;
}

int32_t ShmAdapter::CloseShm()
{
	if(m_pShm)
	{
		int iRet = shmdt( m_pShm );
		if(iRet < 0)
		{
			m_strErrMsg = "shmdt shm failed - "; 
			m_strErrMsg.append( strerror(errno) );
			return -1;
		}
		m_pShm = NULL;
	}
	return 0;
}
