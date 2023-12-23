#include <iostream>

#include <signal.h>
#include <unistd.h>

#include "led-matrix.h"
#include "renderers/static-eyes-renderer.h"
#include "renderers/kitt-renderer.h"

using namespace std;

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
	interrupt_received = true;
}

int main(int argc, char **argv) {
	cout << "OWObot Eyes POC" << endl;
	cout << "Press Ctrl-C to exit" << endl;

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

	// StaticEyesRenderer *renderer = new StaticEyesRenderer();
	KITTRenderer *renderer = new KITTRenderer();

	do {
		renderer->drawFrameToCanvas(canvas);
		usleep(100000);
	} while (!interrupt_received);

	canvas->Clear();
	delete canvas;

	return 0;
}

