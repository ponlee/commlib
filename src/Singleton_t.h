#ifndef SINGLETON_T_H
#define SINGLETON_T_H

class CDummyLock
{
};

template <class TYPE, class LOCK1 = CDummyLock>

class CSingletonT
{
public:
    static TYPE* Instance();
	static void SwitchInstance(TYPE&); 

private:
    CSingletonT();
    CSingletonT(const CSingletonT&);
    ~CSingletonT(); 

private:
	TYPE s_aGuestInstance;
	static CSingletonT<TYPE, LOCK1> s_aHostInstance;
};

/////////////////////////////////////////
template <class TYPE, class LOCK1>
CSingletonT<TYPE, LOCK1> CSingletonT<TYPE, LOCK1>::s_aHostInstance;

template <class TYPE, class LOCK1>
CSingletonT<TYPE, LOCK1>::CSingletonT()
{
}

template <class TYPE, class LOCK1>
CSingletonT<TYPE, LOCK1>::~CSingletonT()
{
}

template <class TYPE, class LOCK1>
TYPE* 
CSingletonT<TYPE, LOCK1>::Instance()
{
    //LOCK1 Guard
    //....

    return &(s_aHostInstance.s_aGuestInstance);
}


template <class TYPE, class LOCK1>
void 
CSingletonT<TYPE, LOCK1>::SwitchInstance(TYPE& newInstance)
{
	s_aHostInstance.s_aGuestInstance = newInstance;
}

#endif /* SINGLETON_T_H */
 
