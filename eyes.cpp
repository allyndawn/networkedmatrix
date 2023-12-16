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
	defaults.chain_length = 1;
	defaults.parallel = 1;
	defaults.show_refresh_rate = true;
	Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
	if (canvas == NULL) {
		cout << "Unable to create canvas" << endl;
		return 1;
	}
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	DrawOnCanvas(canvas);

	canvas->Clear();
	delete canvas;

	return 0;
}

