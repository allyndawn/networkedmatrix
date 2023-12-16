#include <iostream>

#include <signal.h>
#include <unistd.h>

#include "led-matrix.h"

using namespace std;

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
	interrupt_received = true;
}

static void DrawEyeOnCanvas(Canvas *canvas, int x, int y) {
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

static void DrawOnCanvas(Canvas *canvas) {
	for (int i = 0; i<32; i++) {
		if (interrupt_received) {
			return;
		}

		canvas->SetPixel(i, i, 255, 0, 0);

		usleep(10000);
	}
}

int main(int argc, char **argv) {
	cout << "Hello World" << endl;

	RGBMatrix::Options defaults;
	defaults.hardware_mapping = "regular";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.chain_length = 1;
	defaults.parallel = 1;
	defaults.show_refresh_rate = false;
	Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
	if (canvas == NULL) {
		cout << "Unable to create canvas" << endl;
		return 1;
	}
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	// DrawOnCanvas(canvas);
	DrawEyeOnCanvas(canvas, 8, 8);
	DrawEyeOnCanvas(canvas, 40, 8);
	sleep(5);

	canvas->Clear();
	delete canvas;

	return 0;
}

