// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>
#include <type_traits>

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
	static float linearTween(float t, float b, float c, float d) { return c * t / d + b; }

	/**
	 * @brief 二次方淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInQuad(float t, float b, float c, float d) { return c * t * t / d + b; }

	/**
	 * @brief 二次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutQuad(float t, float b, float c, float d) { return -c * t * (t - 2) / d + b; }

	/**
	 * @brief 二次方淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInOutQuad(float t, float b, float c, float d)
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
	static float easeInCubic(float t, float b, float c, float d) { return c * t * t * t / d + b; }

	/**
	 * @brief 三次方淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutCubic(float t, float b, float c, float d)
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
	static float easeInOutCubic(float t, float b, float c, float d)
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
	static float easeInQuart(float t, float b, float c, float d)
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
	static float easeOutQuart(float t, float b, float c, float d)
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
	static float easeInOutQuart(float t, float b, float c, float d)
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
	static float easeInQuint(float t, float b, float c, float d)
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
	static float easeOutQuint(float t, float b, float c, float d)
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
	static float easeInOutQuint(float t, float b, float c, float d)
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
	static float easeInSine(float t, float b, float c, float d)
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
	static float easeOutSine(float t, float b, float c, float d) { return c * sin(t / d * (std::numbers::pi / 2)) + b; }

	/**
	 * @brief 正弦淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInOutSine(float t, float b, float c, float d)
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
	static float easeInExpo(float t, float b, float c, float d) { return c * pow(2, 10 * (t / d - 1)) + b; }

	/**
	 * @brief 指数淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutExpo(float t, float b, float c, float d) { return c * (-pow(2, -10 * t / d) + 1) + b; }

	/**
	 * @brief 指数淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInOutExpo(float t, float b, float c, float d)
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
	static float easeInCirc(float t, float b, float c, float d)
	{
		t /= d;
		return -c * (sqrt(1 - t * t) - 1) + b;
	}

	/**
	 * @brief 圆形淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutCirc(float t, float b, float c, float d)
	{
		t = t / d - 1;
		return c * sqrt(1 - t * t) + b;
	}

	/**
	 * @brief 圆形淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInOutCirc(float t, float b, float c, float d)
	{
		t /= d / 2;
		if(t < 1)
			return -c / 2 * (sqrt(1 - t * t) - 1) + b;
		t -= 2;
		return c / 2 * (sqrt(1 - t * t) + 1) + b;
	}

	/**
	 * @brief 弹性淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInElastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		if((t /= d) == 1)
			return b + c;
		if(!p)
			p = d * .3f;
		if(a < abs(c))
		{
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * std::numbers::pi) * asin(c / a);
		return -(a * pow(2, 10 * (--t)) * sin((t * d - s) * (2 * std::numbers::pi) / p)) + b;
	}

	/**
	 * @brief 弹性淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutElastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		if((t /= d) == 1)
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
	static float easeInOutElastic(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if(t == 0)
			return b;
		if((t /= d / 2) == 2)
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
		if(t < 1)
			return -.5f * (a * pow(2, 10 * (--t)) * sin((t * d - s) * (2 * std::numbers::pi) / p)) + b;
		return a * pow(2, -10 * (--t)) * sin((t * d - s) * (2 * std::numbers::pi) / p) * .5f + c + b;
	}

	static float easeInBack(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		return c * (t /= d) * t * ((s + 1) * t - s) + b;
	}

	static float easeOutBack(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
	}

	static float easeInOutBack(float t, float b, float c, float d, float s)
	{
		if(s == 0)
			s = 1.70158f;
		if((t /= d / 2) < 1)
			return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
		return c / 2 * ((t -= 2) * t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
	}

	/**
	 * @brief 反弹淡入.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInBounce(float t, float b, float c, float d) { return c - easeOutBounce(d - t, 0, c, d) + b; }

	/**
	 * @brief 反弹淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeOutBounce(float t, float b, float c, float d)
	{
		if((t /= d) < (1 / 2.75f))
			return c * (7.5625f * t * t) + b;
		else if(t < (2 / 2.75f))
			return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + b;
		else if(t < (2.5f / 2.75f))
			return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + b;
		else
			return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + .984375f) + b;
	}

	/**
	 * @brief 反弹淡入并淡出.
	 *
	 * @param t 当前时间.
	 * @param b 起始值.
	 * @param c 总变化量.
	 * @param d 持续时间.
	 */
	static float easeInOutBounce(float t, float b, float c, float d)
	{
		if(t < d / 2)
			return easeInBounce(t * 2, 0, c, d) * .5f + b;
		return easeOutBounce(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
	}
};
