#include <iostream>
#include <vector>

class Screen;

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
	void clear(ScreenIndex);
	Window_mgr();

private:
	std::vector <Screen> screens;
};


class Screen
{
public:
	friend void Window_mgr::clear(ScreenIndex);

	typedef std::string::size_type pos;

	Screen() = default;
	Screen(pos ht, pos wd, char c) : height(ht), width(wd),
		contents(ht * wd, c) { }

private:
	void do_display(std::ostream &os) const
	{
		os << contents;
	}

	pos cursor = 0;
	pos height = 0, width = 0;
	pos test_num = 100, test_num2 = 222;
	std::string contents = "contents";
};

Window_mgr::Window_mgr() : screens{ Screen(24, 80, ' ') } {}

void Window_mgr::clear(ScreenIndex i)
{
	Screen &s = screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}



int main() {
	return 0;
}