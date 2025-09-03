#pragma once
struct Rect {
		template <typename T> x, y, w, h;
		Rect() : <initialize values to zero> {}
			Rect(T x, T y, T w, T h) : <initialize value to passed in parameters>{}


		using rect = Rect<float>;
		using irect = Rect<int>;
};