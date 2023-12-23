#ifndef KITT_RENDERER_H
#define KITT_RENDERER_H

#include "renderer.h"

class KITTRenderer {
	public:
		KITTRenderer();
		void drawFrameToCanvas(rgb_matrix::Canvas *canvas);
	private:
		bool m_sweeping_right;
		int m_on_lamp_index;
		int m_lamp_brightness[8];
};

#endif

