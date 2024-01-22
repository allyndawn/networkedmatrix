#include <iostream>

#include <signal.h>
#include <unistd.h>

#include "cpprest/http_listener.h"

#include "led-matrix.h"
#include "renderers/static-eyes-renderer.h"
#include "renderers/kitt-renderer.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
	interrupt_received = true;
}

//////

class MatrixServer {
	public:
		MatrixServer() {}
		MatrixServer(utility::string_t url);

		pplx::task<void> open();
    	pplx::task<void> close();

    	void handle_get(web::http::http_request message);
    	void handle_post(web::http::http_request message);

	private:
		// Error handlers
    	static void handle_error(pplx::task<void>& t);
    	pplx::task<web::json::value> handle_exception(pplx::task<web::json::value>& t, const utility::string_t& field_name);

		// HTTP listener
    	web::http::experimental::listener::http_listener m_listener;
};

MatrixServer::MatrixServer(utility::string_t url) : m_listener(url)
{
    m_listener.support(web::http::methods::GET, std::bind(&MatrixServer::handle_get, this, std::placeholders::_1));
}

void MatrixServer::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch (...)
    {
        // Ignore the error, Log it if a logger is available
    }
}

pplx::task<void> MatrixServer::open()
{
    return m_listener.open().then([](pplx::task<void> t) { handle_error(t); });
}

pplx::task<void> MatrixServer::close()
{
    return m_listener.close().then([](pplx::task<void> t) { handle_error(t); });
}

// Handler to process HTTP::GET requests.
// Replies to the request with data.
void MatrixServer::handle_get(web::http::http_request message)
{
    message.reply(web::http::status_codes::OK, U("Howdy from MatrixServer")).then([](pplx::task<void> t) { handle_error(t); });
}

//////

int main(int argc, char **argv) {
	std::cout << "OWObot Eyes POC" << std::endl;
	std::cout << "Press Ctrl-C to exit" << std::endl;

	utility::string_t address = "http://localhost:9000";
	MatrixServer matrixServer(address);
	matrixServer.open().wait();
    std::cout << "Listening on 9000" << std::endl;

	RGBMatrix::Options defaults;
	defaults.hardware_mapping = "regular";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.chain_length = 1;
	defaults.parallel = 1;
	defaults.show_refresh_rate = false;
	Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
	if (canvas == NULL) {
		std::cout << "Unable to create canvas" << std::endl;
		return 1;
	}
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	StaticEyesRenderer *renderer = new StaticEyesRenderer();
	// KITTRenderer *renderer = new KITTRenderer();

	do {
		renderer->drawFrameToCanvas(canvas);
		usleep(100000);
	} while (!interrupt_received);

	canvas->Clear();
	delete canvas;

	matrixServer.close().wait();

	return 0;
}

