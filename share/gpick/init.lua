
local gpick_module = gpick

gpick = {}
gpick.converters = {}
gpick.user = {}
gpick.global = gpick_module
gpick.options = {}

require('helpers')
require('layouts')
suggest('user_init')

gpick.serialize_web_hex = function(color_object, params)
	if not color_object then return nil end
	if not params then return nil end
	local c = color_object:get_color()
	if gpick.options.upper_case then
		return '#' .. string.format('%02X%02X%02X', round(c:red() * 255), round(c:green() * 255), round(c:blue() * 255))
	else
		return '#' .. string.format('%02x%02x%02x', round(c:red() * 255), round(c:green() * 255), round(c:blue() * 255))
	end
end
gpick.deserialize_web_hex = function(text, color_object)
	local c = color:new()
	local find_start, find_end, red, green, blue = string.find(text, '#([%x][%x])([%x][%x])([%x][%x])[^%x]?')
	if find_start~=nil then
		red = tonumber(red, 16)
		green = tonumber(green, 16)
		blue = tonumber(blue, 16)
		c:red(red / 255)
		c:green(green / 255)
		c:blue(blue / 255)
		color_object:set_color(c)
		return 1 - (math.atan(find_start - 1)/math.pi) - (math.atan(string.len(text) - find_end) / math.pi)
	else
		return -1
	end
end

gpick.serialize_web_hex_no_hash = function(color_object, params)
	if not color_object then return nil end
	if not params then return nil end
	local c = color_object:get_color()
	if gpick.options.upper_case then
		return string.format('%02X%02X%02X', round(c:red() * 255), round(c:green() * 255), round(c:blue() * 255))
	else
		return string.format('%02x%02x%02x', round(c:red() * 255), round(c:green() * 255), round(c:blue() * 255))
	end
end
gpick.deserialize_web_hex_no_hash = function (text, color_object)
	local c = color:new()
	local find_start, find_end, red, green, blue = string.find(text, '([%x][%x])([%x][%x])([%x][%x])[^%x]?')
	if find_start ~= nil then
		red = tonumber(red, 16)
		green = tonumber(green, 16)
		blue = tonumber(blue, 16)
		c:red(red / 255)
		c:green(green / 255)
		c:blue(blue / 255)
		color_object:set_color(c)
		return 1 - (math.atan(find_start - 1) / math.pi) - (math.atan(string.len(text) - find_end) / math.pi)
	else
		return -1
	end
end

gpick.serialize_web_hex_3_digit = function(color_object, params)
	if not color_object then return nil end
	if not params then return nil end
	local c = color_object:get_color()
	if gpick.options.upper_case then
		return '#' .. string.format('%01X%01X%01X', round(c:red() * 15), round(c:green() * 15), round(c:blue() * 15))
	else
		return '#' .. string.format('%01x%01x%01x', round(c:red() * 15), round(c:green() * 15), round(c:blue() * 15))
	end
end
gpick.deserialize_web_hex_3_digit = function(text, color_object)
	local c = color:new()
	local find_start, find_end, red, green, blue = string.find(text, '#([%x])([%x])([%x])[^%x]?')
	if find_start ~= nil then
		red = tonumber(red, 16)
		green = tonumber(green, 16)
		blue = tonumber(blue, 16)
		c:red(red / 15)
		c:green(green / 15)
		c:blue(blue / 15)
		color_object:set_color(c)
		return 1 - (math.atan(find_start - 1) / math.pi) - (math.atan(string.len(text) - find_end) / math.pi)
	else
		return -1
	end
end

gpick.serialize_css_hsl = function (color_object)
	local c = color_object:get_color()
	c = c:rgb_to_hsl()
	return 'hsl(' .. string.format('%d, %d%%, %d%%', round(c:hue() * 360), round(c:saturation() * 100), round(c:lightness() * 100)) .. ')'
end

gpick.serialize_css_rgb = function (color_object)
	local c = color_object:get_color()
	return 'rgb(' .. string.format('%d, %d, %d', round(c:red() * 255), round(c:green() * 255), round(c:blue() * 255)) .. ')'
end

gpick.serialize_color_css_block = function(color_object, params, position)
	if not color_object then return nil end
	if not params then return nil end
	local c = color_object:get_color()
	local hsl = c:rgb_to_hsl()
	local result = '';
	if position.first then
		result = '/**\n * Generated by Gpick ' .. gpick.global.version .. '\n'
	end
	local name = color_object:get_name()
	if not name then
		name = ''
	end
	result = result .. ' * ' .. name
	if gpick.options.upper_case then
		result = result .. '#' .. string.format('%02X%02X%02X', round(c:red()*255), round(c:green()*255), round(c:blue()*255))
	else
		result = result .. '#' .. string.format('%02x%02x%02x', round(c:red()*255), round(c:green()*255), round(c:blue()*255))
	end
	result = result .. ', rgb(' .. string.format('%d, %d, %d', round(c:red()*255), round(c:green()*255), round(c:blue()*255)) .. '), hsl(' .. string.format('%d, %d%%, %d%%', round(c:hue()*360), round(c:saturation()*100), round(c:lightness()*100)) .. ')'
	if position.last then
		result = result .. '\n */'
	end
	return result
end

gpick.deserialize_css_rgb = function(text, color_object)
	local c = color:new()
	local find_start, find_end, red, green, blue = string.find(text, 'rgb%(([%d]*)[%s]*,[%s]*([%d]*)[%s]*,[%s]*([%d]*)%)')
	if find_start ~= nil then
		c:rgb(math.min(1, red / 255), math.min(1, green / 255), math.min(1, blue / 255))
		color_object:set_color(c)
		return 1 - (math.atan(find_start - 1) / math.pi) - (math.atan(string.len(text) - find_end) / math.pi)
	else
		return -1
	end
end

gpick.serialize_css_color_hex = function(color_object, params)
	return 'color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_background_color_hex = function(color_object, params)
	return 'background-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_border_color_hex = function(color_object, params)
	return 'border-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_border_top_color_hex = function(color_object, params)
	return 'border-top-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_border_right_color_hex = function(color_object, params)
	return 'border-right-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_border_bottom_color_hex = function(color_object, params)
	return 'border-bottom-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_css_border_left_hex = function(color_object, params)
	return 'border-left-color: ' .. gpick.serialize_web_hex(color_object, params)
end

gpick.serialize_color_csv = function(color_object)
	local c = color_object:get_color()
	os.setlocale("C", "numeric")
	local r = string.format('%f\t%f\t%f', c:red(), c:green(), c:blue())
	os.setlocale("", "numeric")
	return r
end

gpick.converters['color_web_hex'] = {
	human_readable = _("Web: hex code"),
	serialize = gpick.serialize_web_hex,
	deserialize = gpick.deserialize_web_hex
}
gpick.converters['color_web_hex_3_digit'] = {
	human_readable = _("Web: hex code (3 digits)"),
	serialize = gpick.serialize_web_hex_3_digit,
	deserialize = gpick.deserialize_web_hex_3_digit
}
gpick.converters['color_web_hex_no_hash'] = {
	human_readable = _("Web: hex code (no hash symbol)"),
	serialize = gpick.serialize_web_hex_no_hash,
	deserialize = gpick.deserialize_web_hex_no_hash
}
gpick.converters['color_css_hsl'] = {
	human_readable = _("CSS: hue saturation lightness"),
	serialize = gpick.serialize_css_hsl,
	deserialize = nil
}
gpick.converters['color_css_rgb'] = {
	human_readable = _("CSS: red green blue"),
	serialize = gpick.serialize_css_rgb,
	deserialize = gpick.deserialize_css_rgb
}
gpick.converters['css_color_hex'] = {
	human_readable = 'CSS(color)',
	serialize = gpick.serialize_css_color_hex,
	deserialize = nil
}
gpick.converters['css_background_color_hex'] = {
	human_readable = 'CSS(background-color)',
	serialize = gpick.serialize_css_background_color_hex,
	deserialize = nil
}
gpick.converters['css_border_color_hex'] = {
	human_readable = 'CSS(border-color)',
	serialize = gpick.serialize_css_border_color_hex,
	deserialize = nil
}
gpick.converters['css_border_top_color_hex'] = {
	human_readable = 'CSS(border-top-color)',
	serialize = gpick.serialize_css_border_top_color_hex,
	deserialize = nil
}
gpick.converters['css_border_right_color_hex'] = {
	human_readable = 'CSS(border-right-color)',
	serialize = gpick.serialize_css_border_right_color_hex,
	deserialize = nil
}
gpick.converters['css_border_bottom_color_hex'] = {
	human_readable = 'CSS(border-bottom-color)',
	serialize = gpick.serialize_css_border_bottom_color_hex,
	deserialize = nil
}
gpick.converters['css_border_left_hex'] = {
	human_readable = 'CSS(border-left-color)',
	serialize = gpick.serialize_css_border_left_hex,
	deserialize = nil
}
gpick.converters['color_csv'] = {
	human_readable = 'CSV',
	serialize = gpick.serialize_color_csv,
	deserialize = nil
};
gpick.converters['color_css_block'] = {
	human_readable = 'CSS block',
	serialize = gpick.serialize_color_css_block,
	deserialize = nil
};

gpick.color_serialize = function(converter, color_object, params, position)
	return gpick.converters[converter].serialize(color_object, params, position)
end

gpick.color_deserialize = function(converter, text, color_object, params)
	return gpick.converters[converter].deserialize(text, color_object, params)
end

gpick.component_to_text = function(component_type, color)
	if component_type == 'rgb' then
		return {round(color:red()*255) .. '', round(color:green()*255) .. '', round(color:blue()*255) .. ''}
	end
	if component_type == 'hsl' then
		return {round(color:hue()*360) .. '', round(color:saturation()*100) .. '', round(color:lightness()*100) .. ''}
	end
	if component_type == 'hsv' then
		return {round(color:hue()*360) .. '', round(color:saturation()*100) .. '', round(color:value()*100) .. ''}
	end
	if component_type == 'cmyk' then
		return {round(color:cyan()*255) .. '', round(color:magenta()*255) .. '', round(color:yellow()*255) .. '', round(color:key_black()*255) .. ''}
	end
	if component_type == 'lab' then
		return {round(color:lab_lightness()) .. '', round(color:lab_a()) .. '', round(color:lab_b()) .. ''}
	end
	if component_type == 'lch' then
		return {round(color:lch_lightness()) .. '', round(color:lch_chroma()) .. '', round(color:lch_hue()) .. ''}
	end
	return {}
end

gpick.options_update = function(params)
	gpick.options.upper_case = params:get_string('gpick.options.hex_case', 'upper') == 'upper'
end

