/*
 * Copyright (c) 2009-2016, Albertas Vyšniauskas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of the software author nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GPICK_GTK_COLOR_WIDGET_H_
#define GPICK_GTK_COLOR_WIDGET_H_

#include <gtk/gtk.h>
#include "../Color.h"
#include "../transformation/Chain.h"

#define GTK_TYPE_COLOR (gtk_color_get_type())
#define GTK_COLOR(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_COLOR, GtkColor))
#define GTK_COLOR_CLASS(obj) (G_TYPE_CHECK_CLASS_CAST((obj), GTK_COLOR, GtkColorClass))
#define GTK_IS_COLOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_COLOR))
#define GTK_IS_COLOR_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE((obj), GTK_TYPE_COLOR))
#define GTK_COLOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_COLOR, GtkColorClass))

struct GtkColor
{
	GtkDrawingArea parent;
};
struct GtkColorClass
{
	GtkDrawingAreaClass parent_class;
	void (*activated)(GtkWidget* widget, gpointer userdata);
};
GtkWidget* gtk_color_new();
void gtk_color_set_color(GtkColor* widget, const Color* color, const char* text);
void gtk_color_set_text_color(GtkColor* widget, Color* color);
void gtk_color_get_color(GtkColor* widget, Color* color);
void gtk_color_set_rounded(GtkColor* widget, bool rounded_rectangle);
void gtk_color_set_roundness(GtkColor* widget, double roundness);
void gtk_color_set_hcenter(GtkColor* widget, bool hcenter);
void gtk_color_set_transformation_chain(GtkColor* widget, transformation::Chain *chain);
void gtk_color_set_split_color(GtkColor* widget, const Color* color);
void gtk_color_get_split_color(GtkColor* widget, Color* color);
void gtk_color_enable_split(GtkColor* widget, bool enable);
GType gtk_color_get_type();

#endif /* GPICK_GTK_COLOR_WIDGET_H_ */
