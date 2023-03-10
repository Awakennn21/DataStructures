#include <iostream>
#include <string>
#define ALPHABET_SIZE 26
struct node
{
	bool HasTranslation;
	std::string Translation;

	struct node* Children[ALPHABET_SIZE];
}; 
typedef node* NodePtr;

class TRIE
{
public:
	NodePtr root = CreateNode();

	void Insert(const std::string& word, const std::string& translation)
	{
		NodePtr Tmp = root;

		for (size_t i = 0; i < word.length(); i++)
		{
			int index = word[i] - 'a';//converting char to alphabet index

			if (Tmp->Children[index] == nullptr)
			{
				Tmp->Children[index] = CreateNode();
			}

			Tmp = Tmp->Children[index];
		}
		Tmp->HasTranslation = true;
		Tmp->Translation = translation;
	}

	NodePtr CreateNode()
	{
		NodePtr TMPNode = new node;

		TMPNode->HasTranslation = false;
		TMPNode->Translation = "";

		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			TMPNode->Children[i] = nullptr;
		}

		return TMPNode;
	}

	void SearchForTranslation(const std::string& word) const
	{
		NodePtr Tmp = root;

		for (size_t i = 0; i < word.length(); i++)
		{
			int index = word[i] - 'a';

			if (Tmp->Children[index] == nullptr)
			{
				std::cout << "-" << std::endl;
				return;
			}

			Tmp = Tmp->Children[index];
		}
		if (Tmp->HasTranslation)
		{
			std::cout << Tmp->Translation << std::endl;
		}
		else
		{
			std::cout << "-" << std::endl;
		}
	}

	NodePtr FindNode(const std::string& prefix)
	{
		NodePtr Tmp = root;

		for (size_t i = 0; i < prefix.length(); i++)
		{
			int index = prefix[i] - 'a';

			if (Tmp != nullptr)
			{
				Tmp = Tmp->Children[index];
			}
		}
		return Tmp;
	}

	void PrintAllWords(NodePtr node,const std::string& prefix)
	{
		if (node != nullptr)
		{
			if (node->HasTranslation)
			{
				std::cout << FindNode(prefix)->Translation;
				std::cout << std::endl;
			}
		
			for (int i = 0; i < 26; i++)
			{
				if (node->Children[i] != nullptr)
				{
					PrintAllWords(node->Children[i], prefix + (char)(i + 'a'));
				}
			}
		}
		else
		{
			std::cout << "-" << std::endl;
		}
	}

	void Dealocate(NodePtr Tmp)
	{
		for (int i = 0; i < 26; i++)
		{
			if (Tmp->Children[i] != nullptr)
			{
				Dealocate(Tmp->Children[i]);
			}
		}
		delete Tmp;
	}

	~TRIE()
	{
		Dealocate(root);
	}
};