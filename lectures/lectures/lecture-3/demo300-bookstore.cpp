class foo {
public:
	// Members accessible by everyone
	foo(); // The default constructor.

private:
	// Accessible only by members and friends
	void private_member_function();
	int private_data_member_;

public:
	// May define multiple sections of the same name
};