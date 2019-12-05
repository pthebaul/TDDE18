#include "sorted_list.h"
#include <sstream>
#include <iostream>

// TODO Complementary work needed: please fix the indentation, right now it
//is hard to see what goes inside which statements

// Spaces and tabs were mixed, we did not see that. It should be fixed.

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
    ++list_size;
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
        --list_size;
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
            --list_size;
        }
    }
}

int Sorted_List::at(int index) const
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

int Sorted_List::size() const
{
    return list_size;
}

Sorted_List::Sorted_List() : first{nullptr} {}

// Copy constructor

//TODO Complementary work needed: it is unefficient to use your add function here.
//since you already know the list is sorted you dont have to use the add that sorts the list

// Done
Sorted_List::Sorted_List(Sorted_List const& other)
{
    std::cout << "Copy constructor called. Copying " << other.to_string() << std::endl;

    if (!other.is_empty())
    {
        first = new Node {other.first->data};
        Node* this_ptr {first};

        Node* other_ptr {other.first->next};

        while (other_ptr != nullptr)
        {
            this_ptr->next = new Node{other_ptr->data};
            other_ptr = other_ptr->next;
            this_ptr = this_ptr->next;
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
