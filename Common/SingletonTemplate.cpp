#include "SingletonTemplate.h"

template<typename T>
T* TSingleton<T>::GetInstance()
{
    static T Ins;
    return &Ins;    
}

template<typename T>
TSingleton<T>::~TSingleton()
{
}
