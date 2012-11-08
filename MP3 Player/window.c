
#include "mp3player.h"


GtkWidget*          create_window()
{
    GtkWidget*      PlayerWindow    = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(PlayerWindow), "MP3 Player (OfA)");
    //gtk_window_set_default_size(GTK_WINDOW(PlayerWindow), 500, 200);
    gtk_window_set_position(GTK_WINDOW(PlayerWindow), GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(PlayerWindow), "destroy", GTK_SIGNAL_FUNC(gtk_exit), NULL);
    gtk_signal_connect(GTK_OBJECT(PlayerWindow), "delete_event", GTK_SIGNAL_FUNC(gtk_exit), NULL);


    gtk_container_set_border_width(GTK_CONTAINER(PlayerWindow), 10);
    gtk_widget_realize(PlayerWindow);

    return PlayerWindow;
}


void                create_interface(GtkWidget* PlayerWindow)
{
    GtkWidget*      Panel;
    GtkWidget*      Button;
    GtkWidget*      Image;


    Panel           = gtk_hbox_new(FALSE, 0);

    // Backward Button
    Button          = gtk_button_new();
    gtk_button_set_image(Button, gtk_image_new_from_file("ressources/backward.png"));
    gtk_signal_connect(GTK_OBJECT(Button), "clicked", GTK_SIGNAL_FUNC(backward_callback), NULL);
    gtk_container_add(GTK_CONTAINER(Panel), Button);

    // Play Button
    Button          = gtk_button_new();
    gtk_button_set_image(Button, gtk_image_new_from_file("ressources/play.png"));
    gtk_signal_connect(GTK_OBJECT(Button), "clicked", GTK_SIGNAL_FUNC(play_callback), NULL);
    gtk_container_add(GTK_CONTAINER(Panel), Button);

    // Pause Button
    Button          = gtk_button_new();
    gtk_button_set_image(Button, gtk_image_new_from_file("ressources/pause.png"));
    gtk_signal_connect(GTK_OBJECT(Button), "clicked", GTK_SIGNAL_FUNC(pause_callback), NULL);
    gtk_container_add(GTK_CONTAINER(Panel), Button);

    // Forward Button
    Button          = gtk_button_new();
    gtk_button_set_image(Button, gtk_image_new_from_file("ressources/forward.png"));
    gtk_signal_connect(GTK_OBJECT(Button), "clicked", GTK_SIGNAL_FUNC(forward_callback), NULL);
    gtk_container_add(GTK_CONTAINER(Panel), Button);


    gtk_container_add(GTK_CONTAINER(PlayerWindow), Panel);
    gtk_widget_show_all(PlayerWindow);
}
