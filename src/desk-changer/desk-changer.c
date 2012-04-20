#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "desk-changer.h"

// Function defs
void desk_changer_init_main_window();
void desk_changer_init_tray_icon();
void desk_changer_show_tray_menu();
void desk_changer_wallpaper_next();
void desk_changer_wallpaper_previous();

// Variable defs
GtkWidget *desk_changer_window = NULL, *desk_changer_tray_menu = NULL;

void desk_changer_init_main_window()
{
	desk_changer_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(desk_changer_window), "DeskChanger");
	g_signal_connect(desk_changer_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(desk_changer_window);
	gtk_window_present(GTK_WINDOW(desk_changer_window));
}

void desk_changer_init_tray_icon()
{
	GtkStatusIcon *tray_icon;

	tray_icon = gtk_status_icon_new_from_file("/home/eric/Projects/desk-changer/resources/desk-changer.png");
	gtk_status_icon_set_tooltip_text(tray_icon, "DeskChanger");
	g_signal_connect(G_OBJECT(tray_icon), "popup-menu", G_CALLBACK(desk_changer_show_tray_menu), NULL);
	gtk_status_icon_set_visible(tray_icon, TRUE);
}

void desk_changer_show_tray_menu(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer user_data)
{
	if (!desk_changer_tray_menu) {
		GtkWidget *item;

		// Setup the menu for the first time
		desk_changer_tray_menu = gtk_menu_new();

		item = gtk_menu_item_new_with_label("Previous");
		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(desk_changer_wallpaper_previous), NULL);

		item = gtk_menu_item_new_with_label("Next");
		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(desk_changer_wallpaper_next), NULL);

		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), gtk_separator_menu_item_new());

		item = gtk_menu_item_new_with_label("Exit");
		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(gtk_main_quit), NULL);
	}

	gtk_widget_show_all(desk_changer_tray_menu);
	gtk_menu_popup(GTK_MENU(desk_changer_tray_menu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}

void desk_changer_wallpaper_next()
{
}

void desk_changer_wallpaper_previous()
{
}

int main (int argc, char *argv[])
{
	GtkIconFactory *factory;

	// Initalize our program
	gtk_init(&argc, &argv);
	factory = gtk_icon_factory_new();
	desk_changer_init_main_window();
	desk_changer_init_tray_icon();

	// Now initalize the main GTK thread
	gtk_main();

	return(0);
}
