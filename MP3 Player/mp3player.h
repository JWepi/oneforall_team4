
#ifndef         MP3PLAYER_H
#define         MP3PLAYER_H


#include <gtk/gtk.h>

void            backward_callback(GtkWidget*, gpointer);
void            play_callback(GtkWidget*, gpointer);
void            pause_callback(GtkWidget*, gpointer);
void            forward_callback(GtkWidget*, gpointer);


#endif
