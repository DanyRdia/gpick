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

#ifndef GPICK_COLOR_LIST_H_
#define GPICK_COLOR_LIST_H_

class ColorObject;
struct dynvSystem;
#include "Color.h"
#include <list>
#include <cstddef>

class ColorList
{
	public:
		std::list<ColorObject*> colors;
		typedef std::list<ColorObject*>::iterator iter;
		dynvSystem *params;
		int (*on_insert)(ColorList *color_list, ColorObject *color_object);
		int (*on_delete)(ColorList *color_list, ColorObject *color_object);
		int (*on_delete_selected)(ColorList *color_list);
		int (*on_change)(ColorList *color_list, ColorObject *color_object);
		int (*on_clear)(ColorList *color_list);
		int (*on_get_positions)(ColorList *color_list);
		void* userdata;
};

ColorList* color_list_new(struct dynvHandlerMap *handler_map);
ColorList* color_list_new_with_one_color(ColorList *template_color_list, const Color *color);
void color_list_destroy(ColorList *color_list);
ColorObject* color_list_new_color_object(ColorList *color_list, const Color *color);
ColorObject* color_list_add_color(ColorList *color_list, const Color *color);
int color_list_add_color_object(ColorList *color_list, ColorObject *color_object, int add_to_palette);
int color_list_remove_color_object(ColorList *color_list, ColorObject *color_object);
int color_list_remove_selected(ColorList *color_list);
int color_list_remove_all(ColorList *color_list);
size_t color_list_get_count(ColorList *color_list);
int color_list_get_positions(ColorList *color_list);

#endif /* GPICK_COLOR_LIST_H_ */
