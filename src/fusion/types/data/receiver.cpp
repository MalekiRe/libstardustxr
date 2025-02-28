#include "receiver.hpp"
#include "sender.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"
#include "receiver.h"

//C-Interface
stardust_pulse_receiver* stardust_pulse_receiver_create(stardust_spatial *parent, stardust_field *field, skmath_vec3 origin, skmath_quat orientation){
    stardust_pulse_receiver *r;

    r = (stardust_pulse_receiver *)malloc(sizeof(*r));
    r->obj  = new StardustXRFusion::PulseReceiver(static_cast<StardustXRFusion::Spatial *>(parent->obj), *static_cast<StardustXRFusion::Field *>(field->obj), stardust_convert_skmath_vec3(origin),
                                              stardust_convert_skmath_quat(orientation));
    return r;
}
void stardust_pulse_receiver_destroy(stardust_pulse_receiver* r) {
    delete static_cast<StardustXRFusion::PulseReceiver *>(r->obj);
}
void stardust_pulse_receiver_set_on_data_received(stardust_pulse_receiver *r, void (*fun)(char*, flex_buff_reference*)) {
    static_cast<StardustXRFusion::PulseReceiver *>(r->obj)->onDataReceived.swap(
            reinterpret_cast<std::function<void(std::basic_string<char>, flexbuffers::Reference)> &>(fun));
}





namespace StardustXRFusion {

PulseReceiver::PulseReceiver(Spatial *parent, Field &field, Vec3 origin, Quat rotation) : Spatial(true) {
	nodePath = "/data/receiver";
	nodeName = GenerateID();

	scenegraph->addMethod(nodeName, std::bind(&PulseReceiver::dataReceived, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/data",
		"createPulseReceiver",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field.getNodePath())
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}
PulseReceiver::PulseReceiver(PulseSender *sender, std::string nodePath, std::string nodeName) : Spatial(false) {
	this->sender = sender;
	this->nodePath = nodePath;
	this->nodeName = nodeName;
}

void PulseReceiver::getMask(std::function<void (flexbuffers::Reference)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getMask",
		FLEX_ARG(
			FLEX_NULL
		), [callback](flexbuffers::Reference data) {
			callback(data);
		}
	);
}
void PulseReceiver::getMask(std::function<void (flexbuffers::Map mask)> callback) {
	getMask([callback](flexbuffers::Reference mask) {
		callback(mask.AsMap());
	});
}

void PulseReceiver::setMask(std::vector<uint8_t> mask) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMask",
		FLEX_ARG(
			FLEX_BLOB(mask)
		)
	);
}
void PulseReceiver::setMask(std::function<void (flexbuffers::Builder &)> argsConstructor) {
	flexbuffers::Builder fbb(1024);
	fbb.Map([&]() {
		argsConstructor(fbb);
	});
	fbb.Finish();
	setMask(fbb.GetBuffer());
}

void PulseReceiver::sendData(std::vector<uint8_t> data) {
	messenger->sendSignal(
		sender->getNodePath().c_str(),
		"sendData",
		[&](flexbuffers::Builder &fbb) {
			fbb.Vector([&]() {
				fbb.String(getNodeName());
				fbb.Blob(data.data(), data.size());
			});
		}
	);
}
void PulseReceiver::sendData(std::function<void (flexbuffers::Builder &)> dataConstructor) {
	flexbuffers::Builder fbb(1024);
	fbb.Map([&]() {
		dataConstructor(fbb);
	});
	fbb.Finish();
	sendData(fbb.GetBuffer());
}

std::vector<uint8_t> PulseReceiver::dataReceived(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vector = data.AsVector();
	std::string senderUUID = vector[0].AsString().str();
	flexbuffers::Blob sentDataBlob = vector[1].AsBlob();

	onDataReceived(senderUUID, flexbuffers::GetRoot(sentDataBlob.data(), sentDataBlob.size()));

	return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
