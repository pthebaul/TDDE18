#include <string>

class Sorted_List
{
public:
    bool is_empty() const;
    int size{0};
    
    std::string to_string();
    void add(int const& new_data);
    void rm (int const& target);

    Sorted_List();
    Sorted_List(Sorted_List const& other);
    Sorted_List(Sorted_List&& other);
    ~Sorted_List();
private:
    struct Node
    {
	std::string to_string();
	void add(int const& new_data);
	
	int data{};
	Node* next{nullptr};
    };
    Node* first{};
};
