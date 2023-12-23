#ifndef STATIC_EYES_RENDERER_H
#define STATIC_EYES_RENDERER_H

#include "renderer.h"

class StaticEyesRenderer {
	public:
		StaticEyesRenderer();
		void drawFrameToCanvas(rgb_matrix::Canvas *canvas);
	private:
		void drawEyeOnCanvas(rgb_matrix::Canvas *canvas, int x, int y);
};

#endif

