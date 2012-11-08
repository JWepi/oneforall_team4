
#include "mp3player.h"
#include <stdlib.h>


int                 main(int ac, char **av)
{
    GtkWidget       *PlayerWindow;
    GtkWidget       *Panel;

    gtk_init(&ac, &av);


    PlayerWindow   = create_window();
    create_interface(PlayerWindow);

    gtk_main();

    return EXIT_SUCCESS;
}
