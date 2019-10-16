#include "sorted_list.h"
#include <sstream>
#include <iostream>

bool Sorted_List::is_empty() const
{
    return this->first == nullptr;
}

std::string Sorted_List::to_string() const
{
    std::ostringstream os{};
    if (this->is_empty())
    {
	os << "nullptr";
    }
    else
    {
	os << this->first->to_string();
    }
    return os.str();
}

std::string Sorted_List::Node::to_string() const
{
    std::ostringstream os{};
    os << this->data << "->";
    if (this->next == nullptr)
    {
	os << "nullptr";
    }
    else
    {
	os << this->next->to_string();
    }
    return os.str();
}

void Sorted_List::add(int const& new_data)
{
    this->size++;
    if (this->is_empty())
    {
	this->first = new Node{new_data};
    }
    else if (new_data < this->first->data)
    {
	this->first = new Node{new_data, this->first};
    }
    else
    {
	this->first->add(new_data);
    }
}

void Sorted_List::Node::add(int const& new_data)
{
    if (this->next == nullptr)
    {
	this->next = new Node{new_data};
    }
    else if (new_data < this->next->data)
    {
	this->next = new Node{new_data, this->next};
    }
    else
    {
	this->next->add(new_data);
    }
}

void Sorted_List::rm(int const& target)
{
    std::out_of_range error{"Sorted_List::rm: Target not found"};
    if ((this->is_empty()) or (target < this->first->data))
    {
	throw error;
    }
    else if (target == this->first->data)
    {
	Node* tmp{this->first};
	this->first = this->first->next;
	delete tmp;
	this->size--;
    }
    else // target > this->first->data
    {
	Node* ptr{this->first};
	while ((ptr->next != nullptr) and (target > ptr->next->data))
	{
	    ptr = ptr->next;
	}

	if ((ptr->next == nullptr) or (target < ptr->next->data))
	{
	    throw error;
	}
	else // target == ptr->next->data
	{
	    Node* tmp{ptr->next};
	    ptr->next = ptr->next->next;
	    delete tmp;
	    this->size--;
	}
    }
}

Sorted_List::Sorted_List()
{
    this->first = nullptr;
}

Sorted_List::Sorted_List(Sorted_List const& other)
{
    std::cout << "Copy constructor called. Copying " << other.to_string() << std::endl;
    if (other.is_empty())
    {
	// Nothing to do
    }
    else
    {
	Node* ptr = other.first;
	while (ptr != nullptr)
	{
	    this->add(ptr->data);
	    ptr = ptr->next;
	}
    }
}

Sorted_List::Sorted_List(Sorted_List&& other)
{
    std::cout << "Move constructor called. Moving " << other.to_string() << std::endl;
    this->first = other.first;
    other.first = nullptr;
}

Sorted_List& Sorted_List::operator=(Sorted_List const& other)
{
    std::cout << "Copy assignment called. Copying " << other.to_string() << std::endl;
    Sorted_List tmp{other};
    std::swap(first, tmp.first);
    return *this;
}

Sorted_List& Sorted_List::operator=(Sorted_List&& other)
{
    std::cout << "Move assignment called. Moving " << other.to_string() << std::endl;
    std::swap(first, other.first);
    return *this;
}

Sorted_List::~Sorted_List()
{
    while (not this->is_empty())
    {
	this->rm(this->first->data);
    }
}
