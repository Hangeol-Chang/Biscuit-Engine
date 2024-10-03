#include <gtk/gtk.h>
#include "BiscuitEditor.h"

using namespace editor;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 960, 720);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // editor setting
    BiscuitEditor editor = BiscuitEditor();

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    GtkWidget *button1 = gtk_button_new_with_label("Button 1");
    GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    GtkWidget *button3 = gtk_button_new_with_label("Button 3");
    GtkWidget *button4 = gtk_button_new_with_label("Button 4");

    // 버튼들을 그리드에 배치 (열, 행, 가로 길이, 세로 길이)
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);  // (열 0, 행 0) 위치
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);  // (열 1, 행 0) 위치
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1);  // (열 0, 행 1) 위치
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1);  // (열 1, 행 1) 위치
    // gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(editor.GetPage().get()));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}