#include "sorted_list.h"
#include <sstream>
#include <iostream>
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
    if (this->next != nullptr)
    {
	os << this->next->to_string();
    }
    else
    {
	os << "nullptr";
    }
    return os.str();
}

void Sorted_List::add(int const& new_data)
{
    if (this->is_empty())
    {
	this->first = new Node{new_data};
    }
    else
    {
	this->first->add(new_data);
    }
}

void Sorted_List::Node::add(int const& new_data)
{
    if (new_data < this->data)
    {
	Node* tmp{new Node{new_data}};
	tmp->next = this;
	std::cout << type_name<decltype(this)>() << std::endl;
	//this = tmp;
    }
    else
    {
	// Insérer après
    }
}
