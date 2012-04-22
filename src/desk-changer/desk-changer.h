/*
 * File:   desk-changer.h
 * Author: eric
 *
 * Created on April 22, 2012, 4:38 AM
 */

#ifndef DESK_CHANGER_H
#define	DESK_CHANGER_H

#ifdef	__cplusplus
extern "C" {
#endif

void desk_changer_about();
void desk_changer_delete_main_window();
void desk_changer_init_main_window();
void desk_changer_init_menu_bar(GtkBox *);
void desk_changer_init_tray_icon();
void desk_changer_show_tray_menu(GtkStatusIcon *, guint, guint, gpointer);
void desk_changer_toggle_window();
void desk_changer_wallpaper_next();
void desk_changer_wallpaper_previous();

#ifdef	__cplusplus
}
#endif

#endif	/* DESK_CHANGER_H */

