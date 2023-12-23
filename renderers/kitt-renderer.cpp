#include "kitt-renderer.h"

KITTRenderer::KITTRenderer() {
	m_on_lamp_index = 0;
	m_sweeping_right = true;
}

void KITTRenderer::drawFrameToCanvas(rgb_matrix::Canvas *canvas) {
	int c = 0;
	for (int i = 0; i < 8; i++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (i == m_on_lamp_index) {
					c = 255;
				} else {
					c = 0;
				}
				canvas->SetPixel(i * 8 + x, 12 + y, c, 0, 0);
			}
		}
	}

	if (m_sweeping_right) {
		m_on_lamp_index++;
	} else {
		m_on_lamp_index--;
	}

	if (m_on_lamp_index > 7) {
		m_sweeping_right = false;
		m_on_lamp_index = 6;
	}

	if (m_on_lamp_index < 0) {
		m_sweeping_right = true;
		m_on_lamp_index = 1;
	}
}
