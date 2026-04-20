#include<iostream>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n-----------------------------------\n"


class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it);
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void balance()
	{
		balance(Root);
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void depth_print(int depth, int interval)const
	{
		depth_print(Root, depth, interval);
		cout << endl;
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void tree_print()const
	{
		tree_print(0, depth() * 8);
	}
private:
	void balance(Element* Root)
	{
		if (Root == nullptr)return;
		if (abs(count(Root->pLeft) - count(Root->pRight)) < 2)return;
		if (count(Root->pLeft) > count(Root->pRight))
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Root->Data);
			else						insert(Root->Data, Root->pRight);
			Root->Data = maxValue(Root->pLeft);
			erase(maxValue(Root->pLeft), Root->pLeft);
		}
		if (count(Root->pLeft) < count(Root->pRight))
		{
			if (Root->pLeft == nullptr)	Root->pLeft = new Element(Root->Data);
			else						insert(Root->Data, Root->pLeft);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
		if (Root)
		{
			if (Root->pLeft)erase(Data, Root->pLeft);
			if (Root->pRight)erase(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		if (this->Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (this->Root == nullptr)return 0;
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int count(Element* Root)const
	{
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr) return 0;
		int lDepth = depth(Root->pLeft) + 1;
		int rDepth = depth(Root->pRight) + 1;
		return lDepth > rDepth ? lDepth : rDepth;
	}
	void depth_print(Element* Root, int depth, int interval = 8)const
	{
		cout.width(interval);
		if (Root == nullptr)
		{
			cout << "";
			return;
		}
		if (depth == 0)
		{
			cout << Root->Data;
			cout.width(interval);
			cout << "";
			return;
		}
		depth_print(Root->pLeft, depth - 1, interval);
		depth_print(Root->pRight, depth - 1, interval);
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	void tree_print(int depth, int interval = 8)const
	{
		if (depth == this->depth())return;
		depth_print(depth, interval);
		cout << endl;
		cout << endl;
		cout << endl;
		tree_print(depth + 1, interval / 2);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template<typename T>
void measure(const char message[], T(Tree::* function)		 (/*ôóíêöèÿ íè÷åãî íå ïðèíèìàåò*/)	const, const Tree& tree)
//								   type (Class::*function_poiter)(parameters)						modifiers
{
	clock_t start = clock();
	T result = (tree.*function)(/*parameters*/);
	clock_t end = clock();
	cout.width(48);
	cout << std::left;
	cout << message << result << "\t âû÷èñëåíî çà "
		<< double(end - start) / CLOCKS_PER_SEC << " ñåêóíä" << endl;
}

//#define BASE_CHECK
//#define ERASE_CHECK
//#define PERFORMANCE_CHECK
#define DEPTH_CHECK
//#define TREE_PRINT

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Ââåäèòå ðàçìåð äåðåâà: "; cin >> n;
	Tree tree;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue() << endl;
	cout << "Ñóììà ýëåìåíòîâ äåðåâà: " << tree.sum() << endl;
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << tree.count() << endl;
	cout << "Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << u_tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << u_tree.maxValue() << endl;
	cout << "Ñóììà ýëåìåíòîâ äåðåâà: " << u_tree.sum() << endl;
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << u_tree.count() << endl;
	cout << "Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: " << u_tree.avg() << endl;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree =
	{
					50,

			25,				75,

		16,		32,		64,		85, 91, 98
	};
	tree.print();
	cout << "Ãëóáèíà äåðåâà: " << tree.depth() << endl;
	//tree.clear();
	int value;
	cout << "Ââåäèòå óäàëÿåìîå çíà÷åíèå: "; cin >> value;
	tree.erase(value);
	tree.print();
#endif // ERASE_CHECK

#ifdef PERFORMANCE_CHECK
	clock_t start;
	clock_t end;
	int n;
	cout << "Ââåäèòå ðàçìåð äåðåâà: "; cin >> n;
	Tree tree;
	start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand()/* % 1000*/);
	}
	end = clock();
	cout << "Äåðåâî çàïîëíåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä\n";
	//tree.print();
	measure("Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: ", &(Tree::minValue), tree);
	measure("Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: ", &(Tree::maxValue), tree);
	measure("Ñóììà ýëåìåíòîâ äåðåâà: ", &(Tree::sum), tree);
	measure("Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: ", &(Tree::count), tree);
	measure("Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: ", &(Tree::avg), tree);
	measure("Ãëóáèíà äåðåâà: ", &(Tree::depth), tree);
	/*start = clock();
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";

	start = clock();
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";

	start = clock();
	cout << "Ñóììà ýëåìåíòîâ äåðåâà: " << tree.sum() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";

	start = clock();
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << tree.count() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";

	start = clock();
	cout << "Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: " << tree.avg() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";

	start = clock();
	cout << "Ãëóáèíà äåðåâà: " << tree.depth() << "\t";
	end = clock();
	cout << "âû÷èñëåíî çà " << double(end - start) / CLOCKS_PER_SEC << " ñåêóíä.\n";*/



	/*int value;
	cout << "Ââåäèòå óäàëÿåìîå çíà÷åíèå: "; cin >> value;
	tree.erase(value);
	tree.print();*/
#endif // PERFORMANCE_CHECK

#ifdef TREE_PRINT
	Tree tree =
	{
					50,

			25,				75,

		16,		32,		64,		85, 91//, 98
	};
	//tree.depth_print(55);
	tree.tree_print();
#endif // TREE_PRINT

	Tree tree = { 55, 34, 21, 13, 8, 5, 3 };
	//Tree tree = { 3, 5, 8, 13, 21, 34, 55 };
	//Tree tree = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 15, 16, 17, 18, 21, 34, 55 };
	//Tree tree = { 16,25,32,50,58,75,85 };
	tree.tree_print();
	tree.balance();
	tree.tree_print();

}