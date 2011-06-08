#ifndef __SINGLETON_HPP
#define __SINGLETON_HPP

template<class T>
class cSingleton
{
public:
	cSingleton()  {}
	~cSingleton() {}

	static T* getInstance()
	{
		static T* m_hInstance = new T;

		return m_hInstance;
	}

private:
};

#endif // __SINGLETON_HPP
