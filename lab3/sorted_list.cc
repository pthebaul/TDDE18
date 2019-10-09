#include "sorted_list.h"
#include <sstream>
#include <typeinfo>

bool Sorted_List::is_empty()
{
    return this->first == nullptr;
}

std::string Sorted_List::to_string()
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

std::string Sorted_List::Node::to_string()
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
    if ((this->is_empty()) or (target < this->first->data))
    {
	throw std::out_of_range("Target to remove not found in list");
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
	    throw std::out_of_range("Target to remove not found in list");
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
