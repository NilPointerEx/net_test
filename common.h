#ifndef _COMMON_H_
#define _COMMON_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_SINGLETON(T)	\
public:							\
	static T* GetInstance()		\
	{							\
		static T instance_;		\
		return &instance_;		\
	}							\
private:						\
	T();						\
	T(const T&);				\
	T& operator=(const T&);		\
	~T();						\
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))



#endif //#ifndef _COMMON_H_
