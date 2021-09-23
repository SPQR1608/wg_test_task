#pragma once
#include <iostream>
#include <vector>

template<class T>
struct Node
{
    T value;
    Node<T>* next;
};

template<class T, size_t Size>
class circular_buffer_list
{
public:
    explicit circular_buffer_list()
    {
        head_ = tail_ = buf_;
        for (size_t i = 0; i < Size - 1; ++i)
            buf_[i].next = &buf_[i + 1];

        buf_[Size - 1].next = &buf_[0];
    }

    ~circular_buffer_list()
    {
        
    }

    void put(T value)
    {
        head_->value = value;

        if (full_)
        {
            tail_ = buf_;
        }

        head_ = head_->next;

        full_ = head_ == tail_;
        ++count_;
    }

    T pop()
    {
        if (empty())
        {
            return T();
        }

        auto value = tail_->value;
        full_ = false;
        tail_ = tail_->next;
        --count_;
        return value;
    }

    size_t size() const
    {
        return count_;
    }

    bool empty() const
    {
        return (!full_ && count_ == 0);
    }

    bool full() const
    {
        return full_;
    }

    void reset()
    {
        head_ = tail_;
        full_ = false;
        count_ = 0;
    }

    size_t capacity() const
    {
        return Size;
    }


private:
    Node<T> buf_[Size];
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t count_ = 0;
    bool full_ = false;
};