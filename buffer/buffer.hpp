#ifndef BUFFER
#define BUFFER

#include <exception>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <cstring>

namespace sbuf 
{

/**
 * @brief SFINAE check for whether or not object has an operator==(T) (False).
 * If this struct is chosen buffer class will determine if two buffers are equal by using memcmp instead of operator===(T).
 * 
 * @tparam T type.
 */
template <typename T, typename = void>
struct HasEquals : std::false_type {};

/**
 * @brief SFINAE check for whether or not object has an operator==(T) (True).
 * If this struct is chosen buffer class will determine if two buffers are equal by using operator==(T).
 * 
 * @tparam T type.
 */
template <typename T>
struct HasEquals<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

/**
 * @brief SFINAE check for whether or not object is printable via std::cout << T (False).
 * If this struct is chosen Buffer class will not be printable.
 * 
 * @tparam T type.
 */
template <typename T, typename = void>
struct Printable : std::false_type {};

/**
 * @brief SFINAE check for whether or not object is printable via std::cout << T (True).
 * If this struct is chosen Buffer class will be printable.
 * 
 * @tparam T type.
 */
template <typename T>
struct Printable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

/**
 * @brief Vector like container that is stored on the stack rather than the heap. 
 * 
 * @tparam T 
 * @tparam CAPACITY 
 */
template<typename T, size_t CAPACITY>
class Buffer
{
public:
    /**
     * @brief Forward iterator for buffer container.
     * 
     */
    class Iterator
    {
    public:
        Iterator(T* ptr) :
            m_ptr(ptr)
        {}
        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++(*this);
            return iterator;
        }
        Iterator& operator--()
        {
            m_ptr--;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator iterator = *this;
            --(*this);
            return iterator;
        }
        Iterator operator+(long i) const
        {
            return Iterator(m_ptr + i);
        }
        Iterator& operator+=(long i)
        {
            m_ptr += i;
            return *this;
        }
        ssize_t operator+(const Iterator& ptr) const
        {
            return m_ptr + ptr.m_ptr;
        }
        Iterator operator-(long i) const
        {
            return Iterator(m_ptr - i);
        }
        Iterator& operator-=(long i)
        {
            m_ptr -= i;
            return *this;
        }
        ssize_t operator-(const Iterator& ptr) const
        {
            return m_ptr - ptr.m_ptr;
        }
        T& operator[](size_t index)
        {
            return *(m_ptr + index);
        }
        T* operator->()
        {
            return m_ptr;
        }
        T& operator*()
        {
            return *m_ptr;
        }
        bool operator==(const Iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }
        bool operator!=(const Iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }
        bool operator>(const Iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        bool operator>=(const Iterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
        bool operator<(const Iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        bool operator<=(const Iterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
    public:
        typedef T value_type;
        typedef T difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::forward_iterator_tag iterator_category;
    private:
        T* m_ptr;
    };
    /**
     * @brief Input iterator for buffer container.
     * 
     */
    class ConstIterator
    {
    public:
        ConstIterator(const T* ptr) :
            m_ptr(ptr)
        {}
        ConstIterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator iterator = *this;
            ++(*this);
            return iterator;
        }
        ConstIterator& operator--()
        {
            m_ptr--;
            return *this;
        }
        ConstIterator operator--(int)
        {
            ConstIterator iterator = *this;
            --(*this);
            return iterator;
        }
        ConstIterator operator+(long i) const
        {
            return ConstIterator(m_ptr + i);
        }
        ConstIterator& operator+=(long i)
        {
            m_ptr += i;
            return *this;
        }
        ssize_t operator+(const ConstIterator& ptr) const
        {
            return m_ptr + ptr.m_ptr;
        }
        ConstIterator operator-(long i) const
        {
            return ConstIterator(m_ptr - i);
        }
        ConstIterator& operator-=(long i)
        {
            m_ptr -= i;
            return *this;
        }
        ssize_t operator-(const ConstIterator& ptr) const
        {
            return m_ptr - ptr.m_ptr;
        }
        const T& operator[](size_t index)
        {
            return *(m_ptr + index);
        }
        const T* operator->() const
        {
            return m_ptr;
        }
        const T& operator*() const
        {
            return *m_ptr;
        }
        bool operator==(const ConstIterator& other) const
        {
            return m_ptr == other.m_ptr;
        }
        bool operator!=(const ConstIterator& other) const
        {
            return m_ptr != other.m_ptr;
        }
        bool operator>(const ConstIterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        bool operator>=(const ConstIterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
        bool operator<(const ConstIterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        bool operator<=(const ConstIterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
    public:
        typedef const T value_type;
        typedef const T difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::input_iterator_tag iterator_category;
    private:
        const T* m_ptr;
    };
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

    template<typename U = T, size_t C>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const Buffer<U, C>& other) const
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == other[i]))
            {
                return false;
            }
        }
        return true;
    }
    template<typename U = T, size_t C>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const Buffer<U, C>& other)
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == other[i]))
            {
                return false;
            }
        }
        return true;
    }
    template<typename U = T, size_t C>
    std::enable_if<!HasEquals<U>::value, 
            bool>::type
    operator==(const Buffer<U, C>& other) const
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(memcmp(&m_array[i], &other[i], sizeof(U)) == 0))
            {
                return false;
            }
        }
        return true;
    }
    template<typename U = T>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList) const
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == *(initList.begin() + i)))
            {
                return false;
            }
        }
        return true;
    }
    template<typename U = T>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList)
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == *(initList.begin() + i)))
            {
                return false;
            }
        }
        return true;
    }

    template<typename U = T>
    std::enable_if<!HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList) const
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(memcmp(&m_array[i], (initList.begin() + i), sizeof(U)) == 0))
            {
                return false;
            }
        }
        return true;
    }

    inline Iterator begin()
    {
        return Iterator(static_cast<T*>(m_array));
    } 
    inline ConstIterator begin() const
    {
        return ConstIterator(static_cast<const T*>(m_array));
    } 
    inline Iterator end()
    {
        return Iterator(static_cast<T*>(m_array) + m_size);
    } 
    inline ConstIterator end() const
    {
        return ConstIterator(static_cast<const T*>(m_array) + m_size);
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
    inline size_t size() const
    {
        return m_size;
    }
    inline size_t capacity() const
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

    inline void pushBack(const T& t)
    {
        m_array[m_size] = t;
        m_size++;
    }
    inline void pushFront(const T& t)
    {
        for (size_t i = m_size-1; i != SIZE_MAX; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[0] = t;
        m_size++;
    }
    inline void pop()
    {
        m_size--;
    }
    inline void insert(size_t index, const T& t)
    {
        for (size_t i = m_size-1; i >= index && i != index-1u; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[index] = t;
        m_size++;
    }
    inline void erase(size_t index)
    {
        m_size--;
        for (size_t i = index; i < m_size; i++) 
        {
            m_array[i] = m_array[i + 1];
        }
    }
    template<typename... ARGS>
    inline void emplaceBack(ARGS&&... args)
    {
        m_array[m_size] = T(std::forward<ARGS>(args)...);
        m_size++;
    }
    template<typename... ARGS>
    inline void emplaceFront(ARGS&&... args)
    {
        for (size_t i = m_size-1; i != SIZE_MAX; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[0] = T(std::forward<ARGS>(args)...);
        m_size++;
    }
    template<typename... ARGS>
    inline void emplace(size_t index, ARGS&&... args)
    {
        for (size_t i = m_size-1; i >= index && i != index-1u; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[index] = T(std::forward<ARGS>(args)...);
        m_size++;
    }

private:
    T m_array[CAPACITY];
    size_t m_size;
};

template<typename T, size_t CAPACITY>
std::enable_if<Printable<T>::value, 
        std::ostream&>::type
operator<<(std::ostream &out, const Buffer<T, CAPACITY>& obj)
{
    out << "{ ";
    for (size_t i = 0; i < obj.size(); i++)
    {
        out << obj[i];
        if (i != obj.size() - 1)
        {
            out << ", ";
        }
    }
    out << " }";
    return out;
}

}

#endif // BUFFER END