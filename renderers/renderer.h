#ifndef RENDERER_H
#define RENDERER_H

#include "led-matrix.h"

class Renderer {
	public:
		Renderer();
		virtual void drawFrameToCanvas(rgb_matrix::Canvas *canvas) = 0;
};

#endif

