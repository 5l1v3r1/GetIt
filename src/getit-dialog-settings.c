/* getit-dialog-settings.c
 *
 * Copyright (C) 2017 Bart Kessels <bartkessels@bk-mail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "getit-dialog-settings.h"

struct _GetitDialogSettings {
	GtkDialog parent_instance;

    /* Template widgets */
    GtkSwitch *switch_display_notifications;
    GtkSwitch *switch_show_recents_on_startup;
    GtkSpinButton *spbtn_timeout;
    GtkEntry *et_user_agent;
    GtkButton *btn_save;
};

G_DEFINE_TYPE (GetitDialogSettings, getit_dialog_settings, GTK_TYPE_DIALOG)

/*
 * =============================================================================
 * Signatures
 *
 */
 static void getit_dialog_settings_class_init (GetitDialogSettingsClass *klass);
 static void getit_dialog_settings_init (GetitDialogSettings *self);

/* Callback functions */
static void getit_dialog_settings_cb_btn_save (GtkWidget *caller,
                                               gpointer   user_data);

 /*
 * =============================================================================
 * Public function implementations
 *
 */
GetitDialogSettings *
getit_dialog_settings_new (GtkWindow *parent_window)
{
    g_assert (GTK_IS_WINDOW (parent_window));

    GetitDialogSettings *dialog_settings;

    dialog_settings = g_object_new (GETIT_TYPE_DIALOG_SETTINGS,
                                    "transient-for", parent_window,
                                    NULL);

    return dialog_settings;
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
 static void
getit_dialog_settings_class_init (GetitDialogSettingsClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/dialog-settings.ui");

    gtk_widget_class_bind_template_child (widget_class, GetitDialogSettings, switch_display_notifications);
    gtk_widget_class_bind_template_child (widget_class, GetitDialogSettings, switch_show_recents_on_startup);
    gtk_widget_class_bind_template_child (widget_class, GetitDialogSettings, spbtn_timeout);
    gtk_widget_class_bind_template_child (widget_class, GetitDialogSettings, et_user_agent);
    gtk_widget_class_bind_template_child (widget_class, GetitDialogSettings, btn_save);
}

static void
getit_dialog_settings_init (GetitDialogSettings *self)
{
    g_assert (GTK_IS_WIDGET (self));
    g_assert (GETIT_IS_DIALOG_SETTINGS (self));

    gboolean show_recents_on_startup;
    gboolean show_notifications;
    gint timeout;
    const gchar *user_agent;

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_save, "clicked",
                      G_CALLBACK (getit_dialog_settings_cb_btn_save), self);

    /* Load settings */
    show_notifications = getit_settings_get_show_notifications ();
    show_recents_on_startup = getit_settings_get_show_recents_on_startup ();
    timeout = getit_settings_get_timeout ();
    user_agent = getit_settings_get_user_agent ();

    /* Display settings in UI */
    gtk_switch_set_active (self->switch_display_notifications, show_notifications);
    gtk_switch_set_active (self->switch_show_recents_on_startup, show_recents_on_startup);
    gtk_spin_button_set_value (self->spbtn_timeout, timeout);
    gtk_entry_set_text (self->et_user_agent, user_agent);
}

 /*
 * =============================================================================
 * Callback function implementations
 *
 */
static void
getit_dialog_settings_cb_btn_save (GtkWidget *caller,
                                   gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GETIT_IS_DIALOG_SETTINGS (user_data));

    GetitDialogSettings *self;
    gboolean show_notifications;
    gboolean show_recents_on_startup;
    gint timeout;
    const gchar *user_agent;

    self = GETIT_DIALOG_SETTINGS (user_data);
    show_notifications = gtk_switch_get_state (self->switch_display_notifications);
    show_recents_on_startup = gtk_switch_get_state (self->switch_show_recents_on_startup);
    timeout = gtk_spin_button_get_value_as_int (self->spbtn_timeout);
    user_agent = gtk_entry_get_text (self->et_user_agent);

    getit_settings_set_show_notifications (show_notifications);
    getit_settings_set_show_recents_on_startup (show_recents_on_startup);
    getit_settings_set_timeout (timeout);
    getit_settings_set_user_agent (user_agent);

    gtk_dialog_response (GTK_DIALOG (self), GTK_RESPONSE_OK);
}
