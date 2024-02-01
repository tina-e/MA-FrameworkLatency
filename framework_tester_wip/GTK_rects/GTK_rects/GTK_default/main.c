#include <gtk/gtk.h>
#include <Windows.h>


int r = 0;
int g = 0;
int b = 0;
int width = 0;
int height = 0;
bool pressed = false;


static void cairo_draw(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    if (pressed)
    {
        for (int i = 0; i < 1000; i++)
        {
            
            float r = (float)rand() / RAND_MAX;
            float g = (float)rand() / RAND_MAX;
            float b = (float)rand() / RAND_MAX;
            cairo_set_source_rgba(cr, r, g, b, 1);

            int x = rand() % (width - 400 + 1) + 400;
            int y = rand() % height;
            int w = rand() % (width - x + 1);
            int h = rand() % (height - y + 1);

            cairo_rectangle(cr, x, y, w, h);
            cairo_fill(cr);
        }
        cairo_set_source_rgba(cr, 1, 1, 1, 1);
        cairo_rectangle(cr, 0, 0, 300, 300);
        cairo_fill(cr);
    }
}

static gboolean on_draw_event(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    cairo_draw(cr);
	return FALSE;
}

static gboolean on_click_event(GtkGesture* gesture, int n_press, double x, double y, gpointer area)
{
    pressed = true;
    GtkWidget* drawing_area = GTK_WIDGET(area);
	gtk_widget_queue_draw(drawing_area);
	return FALSE;
}

static gboolean on_release_event(GtkGesture* gesture, int n_press, double x, double y, gpointer area)
{
    pressed = false;
    GtkWidget* drawing_area = GTK_WIDGET(area);
    gtk_widget_queue_draw(drawing_area);
	return FALSE;
}

static void draw(GtkDrawingArea* area, cairo_t* cr, int width, int height, gpointer data)
{
    cairo_draw(cr);
}


static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "framework");
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    
    // for fullscreen / no-fullscreen
    //gtk_window_fullscreen(GTK_WINDOW(window));
    
    gtk_window_present(GTK_WINDOW(window));

    GtkWidget* area = gtk_drawing_area_new();
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), width);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), height);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw, NULL, NULL);
    gtk_window_set_child(GTK_WINDOW(window), area);

    GtkGesture* click_gesture = gtk_gesture_click_new();
    g_signal_connect(click_gesture, "pressed", G_CALLBACK(on_click_event), area);
    g_signal_connect(click_gesture, "released", G_CALLBACK(on_release_event), area);
    gtk_widget_add_controller(window, GTK_EVENT_CONTROLLER(click_gesture));

    HWND frameworkWindow = FindWindow(NULL, L"framework");
    if (frameworkWindow != NULL) {
        BringWindowToTop(frameworkWindow);
        SetForegroundWindow(frameworkWindow);
        MoveWindow(frameworkWindow, 0, 0, width, height, FALSE);
        SetFocus(frameworkWindow);
    }
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    width = (int) (GetSystemMetrics(SM_CXSCREEN) * 0.8);
    height = (int) (GetSystemMetrics(SM_CYSCREEN) * 0.8);
    /*width = 1000;
    height = 1000;*/

    GtkApplication* app;
    int status;

    app = gtk_application_new("framework.rects", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), NULL, NULL);
    g_object_unref(app);

    return status;
}
