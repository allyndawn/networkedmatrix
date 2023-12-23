#include "static-eyes-renderer.h"

StaticEyesRenderer::StaticEyesRenderer() {
	// GNDN
}

void StaticEyesRenderer::drawFrameToCanvas(rgb_matrix::Canvas *canvas) {
	this->drawEyeOnCanvas(canvas, 8, 8);
	this->drawEyeOnCanvas(canvas, 40, 8);
}


void StaticEyesRenderer::drawEyeOnCanvas(rgb_matrix::Canvas *canvas, int x, int y) {
        const unsigned int eye_data[16] = {0x0C00, 0x1F00, 0x1F80, 0x1000, 0x1FE0, 0x3FE0, 0x3FF0, 0x3FF0,
                                        0x3FF0, 0x3FF0, 0x3FF0, 0x1FE0, 0x1FE0, 0x1FC0, 0x1F80, 0x0F00};

        for (int ex = 0; ex<16; ex++) {
                unsigned int column = eye_data[ex];
                for (int ey = 0; ey<16; ey++) {
                        int g = column & 0x001 ? 255 : 0;
                        canvas->SetPixel(x+ex, y+ey, 0, 0, g);
                        column = column >> 1;
                }
        }
}
