#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

//int width = (int) (GetSystemMetrics(SM_CXSCREEN) * 0.8);
//int height = (int) (GetSystemMetrics(SM_CYSCREEN) * 0.8);
int width = GetSystemMetrics(SM_CXSCREEN);
int height = GetSystemMetrics(SM_CYSCREEN);

int randomBoundedInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

class MainWindow : public Fl_Double_Window
{
public:
    MainWindow() : Fl_Double_Window(0, 0, width, height)
    {
        color(FL_BLACK);
        label("framework");
        border(0);
        //fullscreen();
    }
    bool pressed = false;

protected:
    void draw() override
    {
        if (pressed)
        {
            for (int i = 0; i < 999; i++)
            {
                float r = rand() % 255;
                float g = rand() % 255;
                float b = rand() % 255;

                int w = randomBoundedInt(100, 300);
                int h = randomBoundedInt(100, 300);
                int x = randomBoundedInt(500, width - w);
                int y = randomBoundedInt(0, height - h);
                
                fl_color(r, g, b);
                fl_rectf(x, y, w, h);
            }
            fl_color(FL_WHITE);
            fl_rectf(0, 0, 300, 300);
        }
        else
        {
            fl_color(FL_BLACK);
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
