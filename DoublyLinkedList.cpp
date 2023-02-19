#include <iostream>
template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        T m_Data;
        Node* m_Next;
        Node* m_Previous;

        Node()
            :m_Data(0), m_Next(nullptr), m_Previous(nullptr) {}
        Node(T&& data, Node* Previous, Node* next)
            :m_Next(next), m_Previous(Previous)
        {
            m_Data = data;
            data = NULL;
        }
        Node(const T& data, Node* Previous, Node* next)
            :m_Next(next), m_Previous(Previous)
        {
            memcpy(m_Data, data, sizeof(T));
        }
    };

    Node* m_Head;
    Node* m_Tail;
    size_t m_NumberOfElements;

public:
    LinkedList()
    {
        m_Head = nullptr;
        m_Tail = nullptr;
        m_NumberOfElements = 0;
    }

    inline size_t Size() const { return m_NumberOfElements; }
    inline bool Empty() const { return m_NumberOfElements == 0; }
    inline Node* Front() const { return m_Head; }
    inline Node* Back() const { return m_Tail; }

    void PushBack(const T& Value)
    {
        Node* tmp = new Node(Value, m_Tail, nullptr);
        if (m_Head == nullptr && m_NumberOfElements == 0)
        {
            m_Head = tmp;
        }
        else
        {
            m_Tail->m_Next = tmp;
        }
        m_Tail = tmp;
        m_NumberOfElements++;
        tmp = nullptr;
        delete tmp;
    }
    void PushBack(T&& Value)
    {
        Node* tmp = new Node(std::move(Value), m_Tail, nullptr);
        if (m_Head == nullptr && m_NumberOfElements == 0)
        {
            m_Head = tmp;
        }
        else
        {
            m_Tail->m_Next = tmp;
        }
        m_Tail = tmp;
        m_NumberOfElements++;
        tmp = nullptr;
        delete tmp;
    }
    void PushFront(const T& Value)
    {
        Node* tmp = new Node(Value, nullptr, m_Head);
        if (m_Head == nullptr && m_NumberOfElements == 0)
        {
            m_Tail = tmp;
        }
        else
        {
            m_Head->m_Previous = tmp;
        }
        m_Head= tmp;
        m_NumberOfElements++;
        tmp = nullptr;
        delete tmp;
    }
    void PushFront(T&& Value)
    {
        Node* tmp = new Node(std::move(Value), nullptr, m_Head);
        if (m_Head == nullptr && m_NumberOfElements == 0)
        {
            m_Tail = tmp;
        }
        else
        {
            m_Head->m_Previous = tmp;
        }
        m_Head = tmp;
        m_NumberOfElements++;
        tmp = nullptr;
        delete tmp;
    }
    void Put(const T& Data, size_t Position)
    {    
        if (Position == m_NumberOfElements)
        {
            PushBack(Data);
        }
        else if (Position < m_NumberOfElements)
        {
            Node* Current = m_Head;
            for (int i = 0; i < Position; i++)
            {
                Current = Current->m_Next;
            }

            Node* Target = new Node(Data, Current->m_Previous, Current);
            Current->m_Previous = Target;
            m_NumberOfElements++;
        }
    }
    void Put(T&& Data, size_t Position)
    {
        if (Position == m_NumberOfElements)
        {
            PushBack(std::move(Data));
        }
        else if (Position < m_NumberOfElements)
        {
            Node* Current = m_Head;
            for (int i = 0; i < Position; i++)
            {
                Current = Current->m_Next;
            }

            Node* Target = new Node(std::move(Data), Current->m_Previous, Current);
            Current->m_Previous = Target;
            m_NumberOfElements++;
        }
    }


    void PopBack()
    {
        if (m_Tail->m_Previous != nullptr)
        {
            m_Tail = m_Tail->m_Previous;
            delete m_Tail->m_Next;
            m_Tail->m_Next = nullptr;
            m_NumberOfElements--;
        }
        else
        {
            delete m_Tail;
            m_NumberOfElements = 0;
            m_Head = nullptr;
            m_Tail = nullptr;
        }
    }
    void PopFront()
    {
        if (m_Head->m_Next != nullptr)
        {
            m_Head = m_Head->m_Next;
            delete m_Head->m_Previous;
            m_Head->m_Previous = nullptr;
            m_NumberOfElements--;
        }
        else
        {
            delete m_Head;
            m_NumberOfElements = 0;
            m_Head = nullptr;
            m_Tail = nullptr;
        }
    }
    void Pop(size_t Position)
    {
        if (Position < m_NumberOfElements)
        {
            Node* Current = m_Head;
            for (int i = 0; i < Position; i++)
            {
                Current = Current->m_Next;
            }
            if (Current->m_Previous != nullptr && Current->m_Next != nullptr)
            {
                Current->m_Previous->m_Next = Current->m_Next;
                Current->m_Next->m_Previous = Current->m_Previous;
            }
            else if (Current->m_Previous == nullptr)
            {
                m_Head = m_Head->m_Next;
            }
            delete Current;
            m_NumberOfElements--;
        }
    }

    void Clear()
    {
        Node* Current = m_Head;
        for (int i = 0; i < m_NumberOfElements-1; i++)
        {
            Current = Current->m_Next;
            delete Current->m_Previous;
        }
        delete Current;
        m_NumberOfElements = 0;
        m_Head = nullptr;
        m_Tail = nullptr;
    }
    T at(size_t Position)
    {
        Node* Current = m_Head;
        for (int i = 0; i < Position; i++)
        {
            Current = Current->m_Next;
        }
        return Current->m_Data;
    }
};