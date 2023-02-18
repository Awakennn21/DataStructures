#include <iostream>
template<typename T>
class Vector
{
public:
    enum class e_DataMode
    {
        TIME_EFFICIENT = 0,
        MEMORY_EFFICIENT = 1
    };

private:
    T* m_DataPointer;
    uint32_t m_DataSize;
    uint32_t m_BufferCapacity;
    e_DataMode m_AllocationMode;

public:
    Vector()
        :m_DataSize(0), m_BufferCapacity(2), m_AllocationMode(e_DataMode::TIME_EFFICIENT)
    {
        m_DataPointer = new T[2];
    }
    Vector(const Vector& other)
    {
        m_DataSize = other.Size();
        m_BufferCapacity = other.Size();
        m_DataPointer = new T[m_DataSize];
        memcpy(m_DataPointer, other.Data(), m_DataSize * sizeof(T));
    }
    Vector(Vector&& other)
    {
        m_DataSize = other.Size();
        m_BufferCapacity = other.Size();
        m_DataPointer = other.Data();

        other.Data() = nullptr;
    }

    ~Vector()
    {
        delete[] m_DataPointer;
    }

    void PushBack(const T& value)
    {
        if (m_DataSize < m_BufferCapacity)
        {
            m_DataPointer[m_DataSize] = value;
            m_DataSize++;
        }
        else
        {
            Alloc();
            PushBack(value);
        }
    }
    void Emplace(const T& value, uint32_t location)
    {
        if (m_DataSize < m_BufferCapacity)
        {
            memmove_s(m_DataPointer + (location + 1), (m_DataSize - location)*sizeof(T), m_DataPointer + location, (m_DataSize - location) * sizeof(T));
            m_DataPointer[location] = value;
            m_DataSize++;
        }
        else
        {
            Alloc();
            Emplace(value, location);
        }
    }

    void PopBack()
    {
        m_DataSize = m_DataSize > 0 ? m_DataSize - 1 : 0;
    }
    void Remove(uint32_t location)
    {
        memmove_s(m_DataPointer + location, (m_DataSize - location) * sizeof(T), m_DataPointer + (location + 1) , (m_DataSize - location-1) * sizeof(T));
        m_DataSize--;
    }
    void Clear()
    {
        delete[] m_DataPointer;
        m_DataPointer = new T[2];
        m_DataSize = 0;
        m_BufferCapacity = 2;
    }

    void ChangeAllocationMode(e_DataMode mode)
    {
        m_AllocationMode = mode;
    }

    uint32_t Size()
    {
        return m_DataSize;
    }
    bool IsEmpty()
    {
        return m_DataSize == 0;
    }
    bool IsFull()
    {
        return m_DataSize == m_BufferCapacity;
    }

    T* Data()
    {
        return m_DataPointer;
    }
    T* begin()
    {
        return m_DataPointer;
    }
    T* end()
    {
        return m_DataPointer+m_DataSize;
    }
    T Front()
    {
        return m_DataPointer[0];
    }
    T Back()
    {
        return m_DataPointer[m_DataSize - 1 > 0 ? m_DataSize - 1 : 0];
    }

private:
    void Alloc()
    {
        T* tmp = nullptr;
        if (m_AllocationMode == e_DataMode::TIME_EFFICIENT)
        {
            m_BufferCapacity = (int)(1.5f * m_DataSize);
            tmp = new T[(int)(1.5 * m_DataSize)];  
        }
        else
        {
            m_BufferCapacity++;
            tmp = new T[m_BufferCapacity];
        }
        memcpy(tmp, m_DataPointer, m_DataSize * sizeof(T));
        delete[] m_DataPointer;
        m_DataPointer = tmp;
    }

};
