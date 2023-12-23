#include <iostream>

#include <signal.h>
#include <unistd.h>

#include "led-matrix.h"
#include "renderers/static-eyes-renderer.h"

using namespace std;

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
	interrupt_received = true;
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

	StaticEyesRenderer *renderer = new StaticEyesRenderer();
	renderer->drawFrameToCanvas(canvas);
	sleep(5);

	canvas->Clear();
	delete canvas;

	return 0;
}

