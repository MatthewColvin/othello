#include <iostream>

class space
{

public:
	space(bool b = false, bool w = false, bool n = true);
	void make_white();
	void make_black();
	void make_neutral();

	void flip();
	bool const are_oppsite(space sp)const; // outputs true only when black and white netrual returns false;
	bool const are_same(space sp)const;
	bool const is_white()const;
	bool const is_black()const;

	void output(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& os,space sp);


private:
	bool black;
	bool white;
	bool neutral;
};

