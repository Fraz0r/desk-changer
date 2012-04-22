#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "config.h"
#include "desk-changer.h"

// Variable defs
GtkWidget *desk_changer_window = NULL, *desk_changer_tray_menu = NULL;

void desk_changer_about()
{
	GtkWidget *about;
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("/home/eric/Projects/desk-changer/resources/desk-changer.png", NULL);
	const gchar *authors[] = {
		"Eric Gach &lt;eric@php-oop.net&gt;",
		NULL
	};

	about = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about), "DeskChanger");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about), DESK_CHANGER_VERSION);
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about), authors);
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about), GTK_LICENSE_GPL_2_0);
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about), pixbuf);
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about), "DeskChanger is a simple application that allows you to configure images to be rotated on your desktop background at the interval specified by you.");
	g_object_unref(G_OBJECT(pixbuf));
	pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG(about));
	gtk_widget_destroy(GTK_WIDGET(about));
}

void desk_changer_delete_main_window()
{
	gtk_widget_hide(desk_changer_window);
}

void desk_changer_init_main_window()
{
	GtkWidget *mainbox;

	if (desk_changer_window) return;

	desk_changer_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(desk_changer_window), "delete-event", G_CALLBACK(desk_changer_delete_main_window), NULL);
	gtk_window_set_title(GTK_WINDOW(desk_changer_window), "DeskChanger");
	mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(desk_changer_window), mainbox);
	desk_changer_init_menu_bar(GTK_BOX(mainbox));
	gtk_widget_show_all(desk_changer_window);
	gtk_window_present(GTK_WINDOW(desk_changer_window));
}

void desk_changer_init_menu_bar(GtkBox *mainbox)
{
	GtkWidget *menubar, *filemenu, *file, *quit, *helpmenu, *help, *about;

	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	helpmenu = gtk_menu_new();
	file = gtk_menu_item_new_with_label("File");
	help = gtk_menu_item_new_with_label("Help");
	quit = gtk_menu_item_new_with_label("Quit");
	about = gtk_menu_item_new_with_label("About");

	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(desk_changer_about), NULL);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
	gtk_box_pack_start(mainbox, menubar, FALSE, FALSE, 3);
}

void desk_changer_init_tray_icon()
{
	GtkStatusIcon *tray_icon;

	tray_icon = gtk_status_icon_new_from_file("/home/eric/Projects/desk-changer/resources/desk-changer.png");
	gtk_status_icon_set_tooltip_text(tray_icon, "DeskChanger");
	g_signal_connect(G_OBJECT(tray_icon), "popup-menu", G_CALLBACK(desk_changer_show_tray_menu), NULL);
	g_signal_connect(G_OBJECT(tray_icon), "activate", G_CALLBACK(desk_changer_toggle_window), NULL);
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

		item = gtk_menu_item_new_with_label("About");
		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(desk_changer_about), NULL);

		item = gtk_menu_item_new_with_label("Exit");
		gtk_menu_shell_append(GTK_MENU_SHELL(desk_changer_tray_menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(gtk_main_quit), NULL);
	}

	gtk_widget_show_all(desk_changer_tray_menu);
	gtk_menu_popup(GTK_MENU(desk_changer_tray_menu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}

void desk_changer_toggle_window(GtkWidget *widget, GdkEventWindowState *event, gpointer tray_icon)
{
	if (gtk_widget_get_visible(desk_changer_window)) {
		gtk_widget_hide(desk_changer_window);
	} else {
		gtk_widget_show_all(desk_changer_window);
	}
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
