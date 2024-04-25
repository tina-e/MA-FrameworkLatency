#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>

int width = GetSystemMetrics(SM_CXSCREEN);
int height = GetSystemMetrics(SM_CYSCREEN);

class MainWindow : public Fl_Double_Window
{
public:
    MainWindow() : Fl_Double_Window(0, 0, width, height)
    {
        color(FL_BLACK);
        fl_color(FL_BLACK);
        label("framework");
        border(0);
        fullscreen();
        image = new Fl_PNG_Image("noise.png");
    }
    bool pressed = false;
    Fl_PNG_Image* image;

protected:
    void draw() override
    {
        if (pressed)
        {
            image->draw(0, 0, width, height);
        }
        else
        {
            fl_rectf(0, 0, width, height);
        }
    }

    int handle(int event) override
    {
        switch (event)
        {
        case FL_PUSH:
            pressed = true;
            redraw();
            return 1;
        case FL_RELEASE:
            pressed = false;
            redraw();
            return 1;
        }
        return Fl_Double_Window::handle(event);
    }
};

int main(int argc, char** argv)
{
    MainWindow window;
    window.show();
    return Fl::run();
}
