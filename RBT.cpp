#include <iostream>
template<typename T>
class RBT
{
	class Node
	{
	public:
		enum class e_Color
		{
			BLACK = 0,
			RED = 1
		};

		T m_Data;
		e_Color m_Color;

		Node* m_LeftChild;
		Node* m_RightChild;
		Node* m_Parent;

	public:
		Node() = default;
		Node(const T& data,Node* parent)
			:m_Color(e_Color::RED), m_LeftChild(nullptr), m_RightChild(nullptr)
		{
			memcpy(m_Data, data, sizeof(T));
		}
		Node(T&& data, Node* parent)
			:m_Color(e_Color::RED), m_LeftChild(nullptr), m_RightChild(nullptr)
		{
			m_Data = data;
			data = nullptr;
		}

		Node(const T& data, e_Color color, Node* lChild, Node* rChild, Node* parent)
			:m_Color(color), m_LeftChild(lChild), m_RightChild(rChild) 
		{
			memcpy(m_Data, data, sizeof(T));
		}
		Node(T&& data, e_Color color, Node* lChild, Node* rChild, Node* parent)
			:m_Color(color), m_LeftChild(lChild), m_RightChild(rChild)
		{
			m_Data = data;
			data = nullptr;
		}
	};

	Node* m_Root;
public:
	void Push(const T& data)
	{
		if (m_Root == nullptr)
		{
			m_Root = new Node(data, Node::e_Color::BLACK, nullptr, nullptr, nullptr);
			return;
		}
		Node* Iterator = m_Root;
		bool LastTraversionLeft = true;
		try
		{
			while (Iterator != nullptr)
			{
				if (data < Iterator->m_Data)
				{
					TraverseLeft(Iterator);
					LastTraversionLeft = true;
				}
				else
				{
					TraverseRight(Iterator);
					LastTraversionLeft = false;
				}
			}
		}
		catch (const std::exception&)
		{
			std::cout << "<>operator has not been overloaded";
			return;
		}

		LastTraversionLeft ? Iterator->m_Parent->m_LeftChild = Iterator : Iterator->m_Parent->m_RightChild = Iterator;
		Iterator->m_Data = data;
		Iterator->m_Color = Node::e_Color::RED;

		if (Iterator->m_Parent->m_Color == Node::e_Color::RED)
		{
			FixTree(Iterator);
		}
	}

	void Push(T&& data)
	{

	}

	void Pop()
	{

	}

	Node* IsInTree(const T& target)
	{

	}

	void InvertTree()
	{

	}

private:

	void TraverseRight(Node* target)
	{
		if (target != nullptr)
		{
			target = target->m_RightChild;
		}
	}
	void TraverseLeft(Node* target)
	{
		if (target != nullptr)
		{
			target = target->m_LeftChild;
		}
	}

	void FixTree(Node* Changed)
	{
		if (Changed->m_Parent->m_Parent->m_LeftChild == Changed->m_Parent)
		{
			if (Changed->m_Parent->m_Parent->m_RightChild->m_Color == Node::e_Color::RED)
			{
				ReColor(Changed);
			}
			else
			{
				RotateRight(Changed);
			}
		}
		else
		{
			if (Changed->m_Parent->m_Parent->m_RightChild->m_Color == Node::e_Color::RED)
			{
				ReColor(Changed);
			}
			else
			{
				RotateLeft(Changed);
			}
		}
	}

	void RotateLeft(Node* target)
	{

	}
	void RotateRight(Node* target)
	{

	}

	void ReColor(Node* target)
	{

	}
};

int main()
{
	RBT<int> tree;
}