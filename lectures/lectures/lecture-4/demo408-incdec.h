class roadposition {
public:
	roadposition(int km)
	: km_from_sydney_(km) {}

	// pre-increment
	roadposition& operator++() { // prefix
		this->tick_();
		return *this;
	};

	// post increment
	// This is *always* an int, no
	// matter your type.
	roadposition operator++(int) { // postfix
		roadposition rp = *this;
		this->tick_();
		return rp;
	}
	int km() {
		return km_from_sydney_;
	}

private:
	void tick_();
	int km_from_sydney_;
};

void roadposition::tick_() {
	++(this->km_from_sydney_);
}