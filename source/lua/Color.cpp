/*
 * Copyright (c) 2009-2017, Albertas Vyšniauskas
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

#include "Color.h"
#include "../Color.h"
extern "C"{
#include <lualib.h>
#include <lauxlib.h>
}
namespace lua
{
static int newColor(lua_State *L)
{
	Color *c = reinterpret_cast<Color*>(lua_newuserdata(L, sizeof(Color)));
	luaL_getmetatable(L, "color");
	lua_setmetatable(L, -2);
	if (lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER ){
		c->rgb.red = luaL_checknumber(L, 2);
		c->rgb.green = luaL_checknumber(L, 3);
		c->rgb.blue = luaL_checknumber(L, 4);
	}else{
		color_zero(c);
	}
	return 1;
}
Color &checkColor(lua_State *L, int index)
{
	void *ud = luaL_checkudata(L, index, "color");
	luaL_argcheck(L, ud != nullptr, index, "`color' expected");
	return *reinterpret_cast<Color*>(ud);
}
int pushColor(lua_State *L, const Color &color)
{
	Color *c = reinterpret_cast<Color*>(lua_newuserdata(L, sizeof(Color)));
	luaL_getmetatable(L, "color");
	lua_setmetatable(L, -2);
	color_copy(&color, c);
	return 1;
}
static int toString(lua_State *L)
{
	Color &c = checkColor(L, 1);
	lua_pushfstring(L, "color(%f, %f, %f)", c.rgb.red, c.rgb.green, c.rgb.blue);
	return 1;
}
static int colorRgb(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER){
		c.rgb.red = luaL_checknumber(L, 2);
		c.rgb.green = luaL_checknumber(L, 3);
		c.rgb.blue = luaL_checknumber(L, 4);
	}
	lua_pushnumber(L, c.rgb.red);
	lua_pushnumber(L, c.rgb.green);
	lua_pushnumber(L, c.rgb.blue);
	return 3;
}
static int colorRed(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.rgb.red = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.rgb.red);
	return 1;
}
static int colorGreen(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.rgb.green = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.rgb.green);
	return 1;
}
static int colorBlue(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.rgb.blue = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.rgb.blue);
	return 1;
}
static int colorHsl(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER){
		c.hsl.hue = luaL_checknumber(L, 2);
		c.hsl.saturation = luaL_checknumber(L, 3);
		c.hsl.lightness = luaL_checknumber(L, 4);
	}
	lua_pushnumber(L, c.hsl.hue);
	lua_pushnumber(L, c.hsl.saturation);
	lua_pushnumber(L, c.hsl.lightness);
	return 3;
}
static int colorHue(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.hsl.hue = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.hsl.hue);
	return 1;
}
static int colorSaturation(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.hsl.saturation = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.hsl.saturation);
	return 1;
}
static int colorLightness(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.hsl.lightness = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.hsl.lightness);
	return 1;
}
static int colorCmyk(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER && lua_type(L, 5) == LUA_TNUMBER){
		c.cmyk.c = luaL_checknumber(L, 2);
		c.cmyk.m = luaL_checknumber(L, 3);
		c.cmyk.y = luaL_checknumber(L, 4);
		c.cmyk.k = luaL_checknumber(L, 5);
	}
	lua_pushnumber(L, c.cmyk.c);
	lua_pushnumber(L, c.cmyk.m);
	lua_pushnumber(L, c.cmyk.y);
	lua_pushnumber(L, c.cmyk.k);
	return 4;
}
static int colorCyan(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.cmyk.c = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.cmyk.c);
	return 1;
}
static int colorMagenta(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.cmyk.m = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.cmyk.m);
	return 1;
}
static int colorYellow(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.cmyk.y = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.cmyk.y);
	return 1;
}
static int colorKeyBlack(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.cmyk.k = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.cmyk.k);
	return 1;
}
static int colorLabLightness(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lab.L = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lab.L);
	return 1;
}
static int colorLabA(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lab.a = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lab.a);
	return 1;
}
static int colorLabB(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lab.b = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lab.b);
	return 1;
}
static int colorRgbToHsl(lua_State *L)
{
	Color &c = checkColor(L, 1);
	Color c2;
	color_rgb_to_hsl(&c, &c2);
	pushColor(L, c2);
	return 1;
}
static int colorHslToRgb(lua_State *L)
{
	Color &c = checkColor(L, 1);
	Color c2;
	color_hsl_to_rgb(&c, &c2);
	pushColor(L, c2);
	return 1;
}
static int colorRgbToCmyk(lua_State *L)
{
	Color &c = checkColor(L, 1);
	Color c2, c3;
	color_rgb_to_cmy(&c, &c3);
	color_cmy_to_cmyk(&c3, &c2);
	pushColor(L, c2);
	return 1;
}
static int colorLchLightness(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lch.L = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lch.L);
	return 1;
}
static int colorLchChroma(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lch.C = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lch.C);
	return 1;
}
static int colorLchHue(lua_State *L)
{
	Color &c = checkColor(L, 1);
	if (lua_type(L, 2) == LUA_TNUMBER){
		c.lch.h = luaL_checknumber(L, 2);
	}
	lua_pushnumber(L, c.lch.h);
	return 1;
}
static const struct luaL_Reg color_functions[] =
{
	{"new", newColor},
	{nullptr, nullptr}
};
static const struct luaL_Reg color_members[] =
{
	{"__tostring", toString},
	{"red", colorRed},
	{"green", colorGreen},
	{"blue", colorBlue},
	{"rgb", colorRgb},
	{"hue", colorHue},
	{"saturation", colorSaturation},
	{"lightness", colorLightness},
	{"value", colorLightness},
	{"hsl", colorHsl},
	{"cyan", colorCyan},
	{"magenta", colorMagenta},
	{"yellow", colorYellow},
	{"key_black", colorKeyBlack},
	{"cmyk", colorCmyk},
	{"labLightness", colorLabLightness},
	{"labA", colorLabA},
	{"labB", colorLabB},
	{"lchLightness", colorLchLightness},
	{"lchChroma", colorLchChroma},
	{"lchHue", colorLchHue},
	{"rgbToHsl", colorRgbToHsl},
	{"hslToRgb", colorHslToRgb},
	{"rgbToCmyk", colorRgbToCmyk},
	{nullptr, nullptr}
};
int registerColor(lua_State *L)
{
	luaL_newmetatable(L, "color");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, color_members, 0);
	lua_pop(L, 1);
	luaL_newlib(L, color_functions);
	return 1;
}
}
