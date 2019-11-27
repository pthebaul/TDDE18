#pragma once
#include <string>

class Sorted_List
{
public:
    bool is_empty() const;
    
    std::string to_string() const;
    void add(int new_data);
    void rm (int target);

    int at(int index) const;
    int size() const;

    Sorted_List();
    Sorted_List(Sorted_List const& other);
    Sorted_List(Sorted_List&& other);
    Sorted_List& operator=(Sorted_List const& other);
    Sorted_List& operator=(Sorted_List&& other);
    ~Sorted_List();
private:
    struct Node
    {
	std::string to_string() const;
	void add(int new_data);
	
	int data{};
	Node* next{nullptr};
    };
    Node* first{};
    int list_size{0};
};
