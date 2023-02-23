// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>
#include <type_traits>

/**
 * @brief 缓动函数集合.
 */
class Easing
{
public:
	/**
	 * @brief 简单线性补间.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float linear_tween(float t, float b, float c, float d) { return c * t / d + b; }

	/**
	 * @brief 二次方淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_quad(float t, float b, float c, float d) { return c * t * t / d + b; }

	/**
	 * @brief 二次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_quad(float t, float b, float c, float d) { return -c * t * (t - 2) / d + b; }

	/**
	 * @brief 二次方淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_quad(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return c / 2 * t * t + b;
		t--;
		return -c / 2 * (t * (t - 2) - 1) + b;
	}

	/**
	 * @brief 三次方淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_cubic(float t, float b, float c, float d) { return c * t * t * t / d + b; }

	/**
	 * @brief 三次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_cubic(float t, float b, float c, float d)
	{
		t = t / d - 1;
		return c * (t * t * t + 1) + b;
	}

	/**
	 * @brief 三次方淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_cubic(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return c / 2 * t * t * t + b;
		t -= 2;
		return c / 2 * (t * t * t + 2) + b;
	}

	/**
	 * @brief 四次方淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_quart(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t * t * t + b;
	}

	/**
	 * @brief 四次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_quart(float t, float b, float c, float d)
	{
		t = t / d - 1;
		return -c * (t * t * t * t - 1) + b;
	}

	/**
	 * @brief 四次方淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_quart(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return c / 2 * t * t * t * t + b;
		t -= 2;
		return -c / 2 * (t * t * t * t - 2) + b;
	}

	/**
	 * @brief 五次方淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_quint(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t * t * t * t + b;
	}

	/**
	 * @brief 五次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_quint(float t, float b, float c, float d)
	{
		t = t / d - 1;
		return c * (t * t * t * t * t + 1) + b;
	}

	/**
	 * @brief 五次方淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_quint(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return c / 2 * t * t * t * t * t + b;
		t -= 2;
		return c / 2 * (t * t * t * t * t + 2) + b;
	}

	/**
	 * @brief 正弦淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_sine(float t, float b, float c, float d)
	{
		return -c * cos(t / d * (std::numbers::pi / 2)) + c + b;
	}

	/**
	 * @brief 正弦淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_sine(float t, float b, float c, float d)
	{
		return c * sin(t / d * (std::numbers::pi / 2)) + b;
	}

	/**
	 * @brief 正弦淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_sine(float t, float b, float c, float d)
	{
		return -c / 2 * (cos(std::numbers::pi * t / d) - 1) + b;
	}

	/**
	 * @brief 指数淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_expo(float t, float b, float c, float d) { return c * pow(2, 10 * (t / d - 1)) + b; }

	/**
	 * @brief 指数淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_expo(float t, float b, float c, float d) { return c * (-pow(2, -10 * t / d) + 1) + b; }

	/**
	 * @brief 指数淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_expo(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return c / 2 * pow(2, 10 * (t - 1)) + b;
		t--;
		return c / 2 * (-pow(2, -10 * t) + 2) + b;
	}

	/**
	 * @brief 圆形淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_circ(float t, float b, float c, float d)
	{
		t /= d;
		return -c * (std::sqrt(1 - t * t) - 1) + b;
	}

	/**
	 * @brief 圆形淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_circ(float t, float b, float c, float d)
	{
		t = t / d - 1;
		return c * std::sqrt(1 - t * t) + b;
	}

	/**
	 * @brief 圆形淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_circ(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return -c / 2 * (std::sqrt(1 - t * t) - 1) + b;
		t -= 2;
		return c / 2 * (std::sqrt(1 - t * t) + 1) + b;
	}

	/**
	 * @brief 弹性淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_elastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		t /= d;
		if(t == 1)
			return b + c;
		if(!p)
			p = d * .3f;
		if(a < std::abs(c))
		{
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * std::numbers::pi) * asin(c / a);
		t--;
		return -(a * pow(2, 10 * t) * sin((t * d - s) * (2 * std::numbers::pi) / p)) + b;
	}

	/**
	 * @brief 弹性淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_elastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		t /= d;
		if(t == 1)
			return b + c;
		if(!p)
			p = d * .3f;
		if(a < std::abs(c))
		{
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * std::numbers::pi) * asin(c / a);
		return a * pow(2, -10 * t) * sin((t * d - s) * (2 * std::numbers::pi) / p) + c + b;
	}

	/**
	 * @brief 弹性淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_elastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		t /= d / 2;
		if(t == 2)
			return b + c;
		if(!p)
			p = d * (.3f * 1.5f);
		if(a < std::abs(c))
		{
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * std::numbers::pi) * asin(c / a);
		if(t-- < 1)
			return -.5f * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * std::numbers::pi) / p)) + b;
		return a * pow(2, -10 * t) * sin((t * d - s) * (2 * std::numbers::pi) / p) * .5f + c + b;
	}

	static float ease_in_back(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		t /= d;
		return c * t * t * ((s + 1) * t - s) + b;
	}

	static float ease_out_back(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		t = t / d - 1;
		return c * (t * t * ((s + 1) * t + s) + 1) + b;
	}

	static float ease_in_out_back(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		t /= d / 2;
		s *= 1.525f;
		if(t < 1)
			return c / 2 * (t * t * ((s + 1) * t - s)) + b;
		t -= 2;
		return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
	}

	/**
	 * @brief 反弹淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_bounce(float t, float b, float c, float d) { return c - ease_out_bounce(d - t, 0, c, d) + b; }

	/**
	 * @brief 反弹淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_out_bounce(float t, float b, float c, float d)
	{
		t /= d;
		if(t < 1.f / 2.75f)
			return c * (7.5625f * t * t) + b;
		else if(t < 2 / 2.75f)
		{
			t -= 1.5f / 2.75f;
			return c * (7.5625f * t * t + .75f) + b;
		}
		else if(t < 2.5f / 2.75f)
		{
			t -= 2.25f / 2.75f;
			return c * (7.5625f * t * t + .9375f) + b;
		}
		else
		{
			t -= (2.625f / 2.75f);
			return c * (7.5625f * t * t + .984375f) + b;
		}
	}

	/**
	 * @brief 反弹淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float ease_in_out_bounce(float t, float b, float c, float d)
	{
		if(t < d / 2)
			return ease_in_bounce(t * 2, 0, c, d) * .5f + b;
		return ease_out_bounce(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
	}
};
