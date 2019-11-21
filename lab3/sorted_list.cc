#include "sorted_list.h"
#include <sstream>
#include <iostream>

bool Sorted_List::is_empty() const
{
    return first == nullptr;
}

std::string Sorted_List::to_string() const
{
    std::ostringstream os{};
    if (is_empty())
    {
	os << "nullptr";
    }
    else
    {
	os << first->to_string();
    }
    return os.str();
}

std::string Sorted_List::Node::to_string() const
{
    std::ostringstream os{};
    os << data << "->";
    if (next == nullptr)
    {
	os << "nullptr";
    }
    else
    {
	os << next->to_string();
    }
    return os.str();
}

void Sorted_List::add(int new_data)
{
    ++size;
    if (is_empty())
    {
	first = new Node{new_data};
    }
    else if (new_data < first->data)
    {
	first = new Node{new_data, first};
    }
    else
    {
	first->add(new_data);
    }
}

void Sorted_List::Node::add(int new_data)
{
    if (next == nullptr)
    {
	next = new Node{new_data};
    }
    else if (new_data < next->data)
    {
	next = new Node{new_data, next};
    }
    else
    {
	next->add(new_data);
    }
}

void Sorted_List::rm(int target)
{
    std::out_of_range error{"Sorted_List::rm: Target not found"};
    if ((is_empty()) || (target < first->data))
    {
	throw error;
    }
    else if (target == first->data)
    {
	Node* tmp{first};
	first = first->next;
	delete tmp;
	--size;
    }
    else // target > first->data
    {
	Node* ptr{first};
	while ((ptr->next != nullptr) && (target > ptr->next->data))
	{
	    ptr = ptr->next;
	}

	if ((ptr->next == nullptr) || (target < ptr->next->data))
	{
	    throw error;
	}
	else // target == ptr->next->data
	{
	    Node* tmp{ptr->next};
	    ptr->next = ptr->next->next;
	    delete tmp;
	    --size;
	}
    }
}

int Sorted_List::at(int index)
{
    std::out_of_range error{"Sorted_List::at: out of range"};
    if (index < 0)
    {
	throw error;
    }
    
    Node* ptr{first};
    int current_index{0};
    while ((ptr != nullptr) && (current_index < index))
    {
	ptr = ptr->next;
	++current_index;
    }
    
    if (ptr == nullptr)
    {
	throw error;
    }
    else
    {
	return ptr->data;
    }
}

Sorted_List::Sorted_List() : first{nullptr} {}

// Copy constructor
Sorted_List::Sorted_List(Sorted_List const& other)
{
    std::cout << "Copy constructor called. Copying " << other.to_string() << std::endl;
    if (! other.is_empty())
    {
	Node* ptr{other.first};
	while (ptr != nullptr)
	{
	    add(ptr->data);
	    ptr = ptr->next;
	}
    }
}

// Move constructor
Sorted_List::Sorted_List(Sorted_List&& other)
{
    std::cout << "Move constructor called. Moving " << other.to_string() << std::endl;
    first = other.first;
    other.first = nullptr;
}

// Copy assignment
Sorted_List& Sorted_List::operator=(Sorted_List const& other)
{
    std::cout << "Copy assignment called. Copying " << other.to_string() << std::endl;
    Sorted_List tmp{other};
    std::swap(first, tmp.first);
    return *this;
}

// Move assignment
Sorted_List& Sorted_List::operator=(Sorted_List&& other)
{
    std::cout << "Move assignment called. Moving " << other.to_string() << std::endl;
    std::swap(first, other.first);
    return *this;
}

Sorted_List::~Sorted_List()
{
    while (!is_empty())
    {
	rm(first->data);
    }
}
