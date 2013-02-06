#include "Singleton.h"

template <class T> T Singleton<T>::m_instance = nullptr;

template <class T> T& Singleton<T>::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new T();
	}

	return m_instance;
}

template <class T> void Singleton<T>::freeInstance()
{
	if (m_instance != nullptr) {
		delete(m_instance);
		m_instance = nullptr;
	}
}

template <class T> Singleton<T>::Singleton ()
{
}

template <class T> Singleton<T>::~Singleton()
{
}