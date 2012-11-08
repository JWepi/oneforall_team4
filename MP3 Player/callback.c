
#include "mp3player.h"
#include <windows.h>

void            backward_callback(GtkWidget* widget, gpointer data)
{

}

void            play_callback(GtkWidget* widget, gpointer data)
{
    PlaySound("ressources/test.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void            pause_callback(GtkWidget* widget, gpointer data)
{

}

void            forward_callback(GtkWidget* widget, gpointer data)
{

}
