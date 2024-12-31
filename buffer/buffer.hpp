#ifndef BUFFER
#define BUFFER

#include <exception>
#include <algorithm>
#include <iterator>

namespace sbuf 
{

template<typename T>
class BufferIterator : std::iterator<>
{
public:
private:
};

template<typename T, std::size_t CAPACITY>
class Buffer
{
public:
    Buffer() :
        m_size{0}
    {

    }
    Buffer(std::initializer_list<T>&& initList) :
        m_size{initList.size()}
    {
        std::copy(initList.begin(), initList.end(), m_array);
    }
    Buffer(const Buffer<T, CAPACITY>& other) :
        m_size{other.m_size}
    {
        std::copy(std::begin(other.m_array), std::end(other.m_array), std::begin(m_array));
    }
    Buffer(Buffer<T, CAPACITY>&& other) :
        m_array(std::move(other.m_array)),
        m_size{std::move(other.m_size)}
    {
        
    }
    void operator=(const std::initializer_list<T>& initList)
    {
        std::copy(initList.begin(), initList.end(), std::begin(m_array));
        m_size = initList.size();
    }
    void operator=(Buffer<T, CAPACITY>&& other)
    {
        m_array = std::move(other.m_array);
        m_size = std::move(other.m_size);
    }
    void operator=(const Buffer<T, CAPACITY>& other)
    {
        std::copy(std::begin(other.m_array), std::end(other.m_array), std::begin(m_array));
        m_size = other.m_size;
    }

    inline bool operator==(const Buffer<T, CAPACITY>& other) const
    {
        if (other.m_size != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (m_array[i] != other.m_array[i])
            {
                return false;
            }
        }
        return true;
    }
    inline bool operator==(const std::initializer_list<T>& initList) const
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (m_array[i] != *(initList.begin() + i))
            {
                return false;
            }
        }
        return true;
    }

    inline std::iterator<std::forward_iterator_tag, T> begin()
    {
        return std::iterator<std::forward_iterator_tag, T>(m_array);
    } 
    inline std::iterator<std::input_iterator_tag, T> begin() const
    {
        
    } 
    inline std::iterator<std::forward_iterator_tag, T> end()
    {

    } 
    inline std::iterator<std::input_iterator_tag, T> end() const
    {
        
    } 

    inline T& operator[](size_t i)
    {
    #ifdef _DEBUG
        if (i >= m_size)
        {
            throw std::out_of_range("ERROR: index " + std::to_string(i) + " is larger than capacity " + std::to_string(CAPACITY));
        }
    #endif // _DEBUG end
        return m_array[i];
    }
    inline const T& operator[](size_t i) const
    {
    #ifdef _DEBUG
        if (i >= m_size)
        {
            throw std::out_of_range("ERROR: index " + std::to_string(i) + " is larger than capacity " + std::to_string(CAPACITY));
        }
    #endif // _DEBUG end
        return m_array[i];
    }
    inline std::size_t size() const
    {
        return m_size;
    }
    inline std::size_t capacity() const
    {
        return CAPACITY;
    }
    inline T& back()
    {
        return m_array[m_size-1];
    }
    inline const T& back() const
    {
        return m_array[m_size-1];
    }
    inline T& front()
    {
        return m_array[0];
    }
    inline const T& front() const
    {
        return m_array[0];
    }

    inline void push(const T& t)
    {

    }
    inline void pop()
    {

    }

private:
    T m_array[CAPACITY];
    std::size_t m_size;
};

}

#endif // BUFFER END