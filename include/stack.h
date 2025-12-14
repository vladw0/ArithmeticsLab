#pragma once

#include <iostream>

template <class T>
class TStack
{
protected:
    T** data;
    int len;
    int topIndex;
    bool isNew;

public:
    TStack();
    TStack(int len_);
    TStack(const TStack& obj);
    TStack(TStack&& obj);
    ~TStack();

    int GetLen() const;

    void Resize(int len_);
    void Push(T* value);
    void Push(T value);
    T Pop();
    T Top() const;
    bool IsEmpty() const;

    TStack& operator=(const TStack<T>& obj);
    TStack& operator=(TStack<T>&& obj);
};

template<class T>
inline TStack<T>::TStack() : data(nullptr), len(0), topIndex(-1), isNew(true) {}

template<class T>
inline TStack<T>::TStack(int len_) : data(nullptr), len(len_), topIndex(-1), isNew(true)
{
    if (len > 0) {
        data = new T * [len];
        for (int i = 0; i < len; i++) data[i] = nullptr;
    }
}

template<class T>
inline TStack<T>::TStack(const TStack& obj) : data(nullptr), len(obj.len), topIndex(obj.topIndex), isNew(true)
{
    if (len > 0) {
        data = new T * [len];
        for (int i = 0; i <= topIndex; i++) {
            data[i] = new T(*obj.data[i]);
        }
    }
}

template<class T>
inline TStack<T>::TStack(TStack&& obj) : data(obj.data), len(obj.len), topIndex(obj.topIndex), isNew(obj.isNew)
{
    obj.data = nullptr;
    obj.len = 0;
    obj.topIndex = -1;
    obj.isNew = false;
}

template<class T>
inline TStack<T>::~TStack()
{
    if (isNew && data != nullptr) {
        for (int i = 0; i <= topIndex; i++) delete data[i];
        delete[] data;
    }
}

template<class T>
inline int TStack<T>::GetLen() const
{
    return topIndex + 1;
}

template<class T>
inline void TStack<T>::Push(T* value)
{
    if (topIndex + 1 >= len) return; // простой контроль переполнения
    data[++topIndex] = value;
}

template<class T>
inline void TStack<T>::Push(T value)
{
    if (topIndex + 1 >= len) return;
    data[++topIndex] = new T(value);
}

template<class T>
inline T TStack<T>::Pop()
{
    if (topIndex < 0) return T();
    T val = *data[topIndex];
    delete data[topIndex];
    data[topIndex] = nullptr;
    topIndex--;
    return val;
}

template<class T>
inline T TStack<T>::Top() const
{
    if (topIndex < 0) return T();
    return *data[topIndex];
}

template<class T>
inline bool TStack<T>::IsEmpty() const
{
    return topIndex < 0;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& obj)
{
    if (this == &obj) return *this;
    if (isNew && data) {
        for (int i = 0; i <= topIndex; i++) delete data[i];
        delete[] data;
    }
    len = obj.len;
    topIndex = obj.topIndex;
    isNew = true;
    if (len > 0) {
        data = new T * [len];
        for (int i = 0; i <= topIndex; i++) {
            data[i] = new T(*obj.data[i]);
        }
    }
    return *this;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& obj)
{
    if (this == &obj) return *this;
    if (isNew && data) {
        for (int i = 0; i <= topIndex; i++) delete data[i];
        delete[] data;
    }
    data = obj.data;
    len = obj.len;
    topIndex = obj.topIndex;
    isNew = obj.isNew;

    obj.data = nullptr;
    obj.len = 0;
    obj.topIndex = -1;
    obj.isNew = false;

    return *this;
}