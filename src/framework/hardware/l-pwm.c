/*
 * framework/hardware/l-pwm.c
 *
 * Copyright(c) 2007-2023 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <pwm/pwm.h>
#include <hardware/l-hardware.h>

static int l_pwm_new(lua_State * L)
{
	const char * name = luaL_checkstring(L, 1);
	struct pwm_t * pwm = search_pwm(name);
	if(!pwm)
		return 0;
	lua_pushlightuserdata(L, pwm);
	luaL_setmetatable(L, MT_HARDWARE_PWM);
	return 1;
}

static int l_pwm_list(lua_State * L)
{
	struct device_t * pos, * n;
	struct pwm_t * pwm;

	lua_newtable(L);
	list_for_each_entry_safe(pos, n, &__device_head[DEVICE_TYPE_PWM], head)
	{
		pwm = (struct pwm_t *)(pos->priv);
		if(!pwm)
			continue;
		lua_pushlightuserdata(L, pwm);
		luaL_setmetatable(L, MT_HARDWARE_PWM);
		lua_setfield(L, -2, pos->name);
	}
	return 1;
}

static const luaL_Reg l_pwm[] = {
	{"new",		l_pwm_new},
	{"list",	l_pwm_list},
	{NULL,	NULL}
};

static int m_pwm_tostring(lua_State * L)
{
	struct pwm_t * pwm = luaL_checkudata(L, 1, MT_HARDWARE_PWM);
	lua_pushstring(L, pwm->name);
	return 1;
}

static int m_pwm_config(lua_State * L)
{
	struct pwm_t * pwm = luaL_checkudata(L, 1, MT_HARDWARE_PWM);
	int duty = luaL_checkinteger(L, 2);
	int period = luaL_checkinteger(L, 3);
	int polarity = lua_toboolean(L, 4) ? 1 : 0;
	pwm_config(pwm, duty, period, polarity);
	lua_settop(L, 1);
	return 1;
}

static int m_pwm_enable(lua_State * L)
{
	struct pwm_t * pwm = luaL_checkudata(L, 1, MT_HARDWARE_PWM);
	pwm_enable(pwm);
	lua_settop(L, 1);
	return 1;
}

static int m_pwm_disable(lua_State * L)
{
	struct pwm_t * pwm = luaL_checkudata(L, 1, MT_HARDWARE_PWM);
	pwm_disable(pwm);
	lua_settop(L, 1);
	return 1;
}

static const luaL_Reg m_pwm[] = {
	{"__tostring",	m_pwm_tostring},
	{"config",		m_pwm_config},
	{"enable",		m_pwm_enable},
	{"disable",		m_pwm_disable},
	{NULL,	NULL}
};

int luaopen_hardware_pwm(lua_State * L)
{
	luaL_newlib(L, l_pwm);
	luahelper_create_metatable(L, MT_HARDWARE_PWM, m_pwm);
	return 1;
}
