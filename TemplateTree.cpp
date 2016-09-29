#include <iostream>
#include <vector>
#include <string>

#define NEED_TRACE

using namespace std;


// forward declaration of Tree class for declare it as friend
template <class T> 
class Tree;


//! Complex class which describe one node of tree
//! Every node has parent (except root-node) and can has children (as many as you want)
template<class T>
class Node
{
	// give the access from Tree object to children container
	template <class U>
	friend class Tree;

private:
	enum eLimit
	{
		indent_increment = 2
	};

	typedef Node<T>* tNodePtr;

	T m_value;						///< copy of value (use pointer for more efficient work)
	tNodePtr m_parent;				///< pointer on father node
	vector<tNodePtr> m_children;	///< container of children

	//! Set parent for current node
	void setParent(tNodePtr parent)
	{
		m_parent = parent;
	}

	//! Print self value and then every child recursively
	//! \param indent how many spaces will be printed before value
	void print(int indent = 0)
	{
		string sIndent;
		sIndent.append(indent, ' ');
		cout << sIndent << m_value << endl;
		for (const auto& child : m_children)
			child->print(indent+indent_increment);
	}

public:
	//! Constructor
	//! \param value value for node
	//! \param parent parent node
	Node(const T& value, tNodePtr parent = nullptr)
		: m_value(value)
		, m_parent(parent)
	{
		#ifdef NEED_TRACE
		cout << "Node created " << this << endl;
		#endif
	}

	//! Destructor
	~Node()
	{
		#ifdef NEED_TRACE
		cout << "Node destroyed " << this << endl;		
		#endif
	}

	//! Add one more child to node
	//! And set current node as parent
	//! \param child child node 
	void addChild(tNodePtr child)
	{
		if (child == nullptr)
			return;

		m_children.push_back(child);
		child->setParent(this);
	}

	//! Set new value of node
	//! \value new value
	void setValue(T value)
	{
		m_value = value;
	}

	//! Print self and all children with indents
	void traverse()
	{
		print();		
	}
};


//! Class which provides methods for working with nodes as one tree
template <class T>
class Tree
{
private:
	typedef Node<T>* tNodePtr;

	tNodePtr m_head;

	//! Remove all children recursively and then remove itself
	//! \param element root or sub-root node
	void removeElement(tNodePtr element)
	{
		if (element == nullptr)
			return;

		for (auto elemPtr : element->m_children)
		{
			removeElement(elemPtr);
		}

		delete element;
	}

public:
	//! constructor
	Tree()
	{
		#ifdef NEED_TRACE
		cout << "Tree created " << this << endl;
		#endif
	}

	//! Desctructor
	~Tree()
	{
		clear();
		#ifdef NEED_TRACE
		cout << "Tree destroyed " << this << endl;
		#endif
	}


	//! Add new element into tree
	//! \param element node which should be added
	//! \param parent parent of element. If it nullptr 
	//! then it will be added as child of root element
	void addElement(tNodePtr element, tNodePtr parent = nullptr)
	{
		if (element == nullptr)
			return;

		if (parent != nullptr)
		{
			parent->addChild(element);
			return;
		}

		if (m_head)
			m_head->addChild(element);
	}

	//! Set root elelement of tree
	void setRoot(tNodePtr root)
	{
		if (root)
			m_head = root;
	}

	//! Print the whole tree with indents
	void traverse()
	{
		if (m_head)
			m_head->traverse();
	}

	//! Remove all element from tree
	void clear()
	{
		removeElement(m_head);
		m_head = nullptr;
	}

};


/////////////////////
////////OWN TYPE/////
/////////////////////
class Info
{
	string m_name;
	int m_age;
public:
	Info(string name, int age)
		: m_name(name)
		, m_age(age)
	{

	}

	friend ostream& operator<<(ostream& os, Info info);
};

ostream& operator<<(ostream& os, Info info)
{
	os << "Name: " << info.m_name << ", Age: " << info.m_age;
	return os;
}



/////////////////////
////////USAGE////////
/////////////////////


void createIntTree()
{
	typedef int treeType;
	typedef Node<treeType> node;
	Tree<treeType> tree;

	node* head 		= new node(0);
	node* child1 	= new node(1);
	node* child2 	= new node(2);
	node* child3 	= new node(3);
	node* child4 	= new node(4);
	node* child5 	= new node(5);

	
	tree.addElement(child3, child2);
	tree.addElement(child4, child2);
	tree.addElement(child5, child3);
	tree.addElement(child2, child1);
	tree.addElement(child1, head);
	tree.setRoot(head);

	tree.traverse();
	tree.clear();
	tree.traverse();
}

void createStringTree()
{
	typedef string treeType;
	typedef Node<treeType> node;
	Tree<treeType> tree;

	node* head 		= new node("0");
	node* child1 	= new node("1");
	node* child2 	= new node("2");
	node* child3 	= new node("3");
	node* child4 	= new node("4");
	node* child5 	= new node("5");

	
	tree.addElement(child3, child2);
	tree.addElement(child4, child2);
	tree.addElement(child5, child3);
	tree.addElement(child2, child1);
	tree.addElement(child1, head);
	tree.setRoot(head);

	tree.traverse();
	tree.clear();
	tree.traverse();
}

void createOwnTypedTree()
{
	typedef Info treeType;
	typedef Node<treeType> node;
	Tree<treeType> tree;

	node* head 		= new node(Info(("Nick"), 10));
	node* child1 	= new node(Info(("Dick"), 15));
	node* child2 	= new node(Info(("Rick"), 6));
	node* child3 	= new node(Info(("Clark"), 23));
	node* child4 	= new node(Info(("Marty"), 15));
	node* child5 	= new node(Info(("Dory"), 15));

	
	tree.addElement(child3, child2);
	tree.addElement(child4, child2);
	tree.addElement(child5, child3);
	tree.addElement(child2, child1);
	tree.addElement(child1, head);
	tree.setRoot(head);

	tree.traverse();
	tree.clear();
	tree.traverse();
}

int main()
{
	// createIntTree();
	// createStringTree();
	createOwnTypedTree();
	return 0;
}