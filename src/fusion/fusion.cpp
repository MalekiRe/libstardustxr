#include "fusion.hpp"
#include "fusion_internal.hpp"
#include "../client/connector.hpp"
#include "flex.hpp"
#include "fusion_internal.hpp"

#include "types/spatial/spatial.hpp"

#include <poll.h>
#include <iostream>
#include <linux/limits.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include "random.hpp"
#include "fusion.h"
//C-Interface
stardust_spatial *spatial_root = nullptr;
stardust_spatial *stardust_get_root() {
    if(spatial_root == nullptr) {
        spatial_root = (stardust_spatial *)(malloc(sizeof(*spatial_root)));
        spatial_root->obj = StardustXRFusion::Root();
    }
    return spatial_root;
}
void stardust_on_logic_step(void (*fun)(double, double)) {
    StardustXRFusion::OnLogicStep(fun);
}
bool stardust_setup() {
    return StardustXRFusion::Setup();
}
void stardust_run_event_loop() {
    StardustXRFusion::RunEventLoop();
}
void stardust_set_skytext(const char *path) {
    StardustXRFusion::SetSkytex(path);
}
void stardust_set_skylight(const char *path) {
    StardustXRFusion::SetSkylight(path);
}
char *stardust_convert_exe_relative_path(const char *path) {
    return strdup(StardustXRFusion::ConvertExeRelativePath(path).c_str());
}
namespace StardustXRFusion {

//C++ Implementation
std::vector<uint32_t> usedIDs;

std::atomic_bool running = {false};
StardustXRFusion::FusionScenegraph *scenegraph = nullptr;
StardustXRFusion::Messenger *messenger = nullptr;

Spatial root;
Spatial hmd;

LogicStepMethod logicMethod;

std::vector<uint8_t> FlexDummy(flexbuffers::Reference data, bool) {
	return std::vector<uint8_t>();
}

std::string GenerateID() {
	uint32_t id = 0;
	while(id == 0 || find(usedIDs.begin(), usedIDs.end(), id) != usedIDs.end()) {
		id = Random::generate<uint32_t>();
	}
	usedIDs.push_back(id);
	std::string strID = std::to_string(id);
	strID.reserve(16);
	return strID;
}

bool Setup() {
	if(running)
		return true;
	printf("Client starting...\n");
	int fd = StardustXR::ConnectClient();
	if (!fd) {
		perror("Client failed to connect to server\n");
		return false;
	}

	scenegraph = new FusionScenegraph();
	messenger = new Messenger(fd, scenegraph);

	const char* launchAnchor = getenv("STARDUST_LAUNCH_ANCHOR");
	if(launchAnchor) {
		messenger->sendSignal(
			"/",
			"applyLaunchAnchor",
			FLEX_ARG(FLEX_UINT(std::stoul(launchAnchor)))
		);
	}

	messenger->sendSignal(
		"/",
		"subscribeLogicStep",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("logicStep"))
		)
	);
	scenegraph->addMethod("logicStep", &FlexDummy);

	hmd.setBackend("", "hmd");

	running = true;
	return true;
}

void RunEventLoop(int timeout) {
	pollfd poll_fd = {
		.fd = messenger->fd,
		.events = POLLIN,
	};
	while(1) {
		int fdStatus = poll(&poll_fd, 1, timeout);
		if(fdStatus < 0)
			break;
		if(fdStatus == 0)
			continue;

		if(!messenger->dispatch())
			break;
	}
	Shutdown();
}

void Shutdown() {
	if(!running)
		return;
	messenger->sendSignal(
		"/",
		"disconnect",
		FLEX_ARG(FLEX_NULL)
	);
	delete scenegraph;
	delete messenger;
	scenegraph = nullptr;
	messenger  = nullptr;
	running = false;
}

Spatial *Root() {
	return &root;
}
Spatial *HMD() {
	return &hmd;
}

void SetSkytex(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkytex",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

void SetSkylight(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkylight",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

std::vector<uint8_t> LogicStep(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vec = data.AsVector();
	double delta = vec[0].AsDouble();
	double timeToRender = vec[1].AsDouble();
	logicMethod(delta, timeToRender);

	return std::vector<uint8_t>();
}

void OnLogicStep(LogicStepMethod method) {
	scenegraph->addMethod("logicStep", &LogicStep);
	logicMethod = method;
}

bool FileExists(std::string path) {
	std::string convertedPath = ConvertExeRelativePath(path);
	FILE *file = fopen(convertedPath.c_str(), "ro");
	bool exists = file;
	if(exists)
		fclose(file);
	else
		printf("File \"%s\" does not exist\n", convertedPath.c_str());
	fflush(stdout);
	return exists;
}

std::string ConvertExeRelativePath(std::string path) {
	if(*path.begin() == '/')
		return path;
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	std::string exePath;
	if (count != -1) {
		exePath = dirname(result);
	}
	return std::string(exePath) + "/" + path;
}

}
