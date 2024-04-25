#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/names.h>
#include <iostream>

using namespace std;
int width = 100;
int height = 100;

class MainWindow : public Fl_Window
{
public:
	MainWindow() : Fl_Window(0, 0, width, height)
	{
		color(FL_BLACK);
		label("framework");
		border(0);
	}

private:
	int handle(int event) override
	{
		switch (event)
		{
		case FL_PUSH:
			color(FL_WHITE);
			redraw();
			return 1;
		case FL_RELEASE:
			color(FL_BLACK);
			redraw();
			return 1;
		}
		return Fl_Window::handle(event);
	}
};

int main(int argc, char **argv)
{
	MainWindow window;
	window.show();
	return Fl::run();
}