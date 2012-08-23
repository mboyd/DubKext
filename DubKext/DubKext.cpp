#include <IOKit/IOLib.h>
#include "DubKext.h"

OSDefineMetaClassAndStructors(org_mboyd_DubKext, IOSerialStreamSync)

#define super IOSerialStreamSync

bool org_mboyd_DubKext::init(OSDictionary *dict) {
	IOLog("WUB WUB WUB Init\n");
	return super::init(dict);
}

void org_mboyd_DubKext::free(void) {
	IOLog("WUB WUB WUB Free\n");
	super::free();
}

bool org_mboyd_DubKext::attach(IOService *provider) {
	IOLog("Attach\n");
	super::attach(provider);
	return true;
}

void org_mboyd_DubKext::detach(IOService *provider) {
	IOLog("Detach\n");
	super::detach(provider);
}

IOService *org_mboyd_DubKext::probe(IOService *provider, SInt32 *score) {
	IOLog("Probing\n");
	super::probe(provider, score);
	*score = 100;
	return this;
}

bool org_mboyd_DubKext::start(IOService *provider) {
	IOLog("Start\n");
	super::start(provider);
	return true;
}

void org_mboyd_DubKext::stop(IOService *provider) {
	IOLog("Stop\n");
	super::stop(provider);
}

bool org_mboyd_DubKext::open(IOService *forClient, IOOptionBits options, void *arg) {
	IOLog("Open\n");
	super::open(forClient, options, arg);
	return true;
}

void org_mboyd_DubKext::close(IOService *forClient, IOOptionBits options) {
	IOLog("Close");
	super::close(forClient, options);
}

IOReturn org_mboyd_DubKext::acquirePort(bool sleep) {
	IOLog("Acquire port\n");
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::releasePort() {
	IOLog("Release port\n");
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::setState(UInt32 state, UInt32 mask) {
	IOLog("Set state\n");
	return kIOReturnSuccess;
}

UInt32 org_mboyd_DubKext::getState() {
	IOLog("Get state\n");
	return 0;
}

IOReturn org_mboyd_DubKext::watchState(UInt32 *state, UInt32 mask) {
	IOLog("Set state\n");
	return kIOReturnSuccess;
}

UInt32 org_mboyd_DubKext::nextEvent() {
	IOLog("Next event\n");
	return PD_E_EOQ;
}

IOReturn org_mboyd_DubKext::executeEvent(UInt32 event, UInt32 data) {
	IOLog("Execute event\n");
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::requestEvent(UInt32 event, UInt32 *data) {
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::enqueueEvent(UInt32 event, UInt32 data, bool sleep) {
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::dequeueEvent(UInt32 *event, UInt32 *data, bool sleep) {
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::enqueueData(UInt8 *buffer,  UInt32 size, UInt32 *count, bool sleep ) {
	return kIOReturnSuccess;
}

IOReturn org_mboyd_DubKext::dequeueData(UInt8 *buffer, UInt32 size, UInt32 *count, UInt32 min) {
	for (UInt32 i = 0; i < size; i += 4) {
		buffer[i+0] = (UInt8)'W';
		buffer[i+1] = (UInt8)'U';
		buffer[i+1] = (UInt8)'B';
		buffer[i+1] = (UInt8)' ';
	}
	*count = size;
	return kIOReturnSuccess;
}
