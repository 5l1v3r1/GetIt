/*
 * gi-element-header.c
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
 *
 */

#include <glib-object.h>
#include <gtk/gtk.h>
#include <string.h>

#include "gi-element-header.h"

G_DEFINE_TYPE(GiElementHeader, gi_element_header, GTK_TYPE_GRID)

static void gi_element_header_init(GiElementHeader* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/element-header.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->cbtn_enabled = GTK_WIDGET(gtk_builder_get_object(builder, "cbtn_enabled"));
    self->et_key = GTK_WIDGET(gtk_builder_get_object(builder, "et_key"));
    self->et_value = GTK_WIDGET(gtk_builder_get_object(builder, "et_value"));
    self->btn_remove = GTK_WIDGET(gtk_builder_get_object(builder, "btn_remove"));

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);
    gtk_widget_show_all(GTK_WIDGET(self));

    g_object_unref(builder);
}

static void gi_element_header_class_init(GiElementHeaderClass* class)
{
    GtkGridClass* parent_class = GTK_GRID_CLASS(class);
}

GiElementHeader* gi_element_header_new()
{
    return g_object_new(GI_TYPE_ELEMENT_HEADER, NULL);
}

gboolean gi_element_header_get_enabled(GiElementHeader* self)
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self->cbtn_enabled)) && strlen(gtk_entry_get_text(GTK_ENTRY(self->et_key))) > 0;
}