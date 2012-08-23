#include <IOKit/IOService.h>
#include <IOKit/serial/IOSerialStreamSync.h>

class org_mboyd_DubKext : public IOSerialStreamSync {
	OSDeclareDefaultStructors(org_mboyd_DubKext)
public:
	virtual bool init(OSDictionary *dictionary = 0);
	virtual void free(void);
	
	bool attach(IOService *provider);
	void detach(IOService *provider);
	
	virtual IOService *probe(IOService *provider, SInt32 *score);
	
	virtual bool start(IOService *provider);
	virtual void stop(IOService *provider);
	
	virtual bool open(IOService *forClient, IOOptionBits options = 0, void *arg = 0);
	virtual void close(IOService *forClient, IOOptionBits options = 0);
	
	/* acquire tests and sets the state of the port object.  If the port was
	 *available, then the state is set to busy, and IO_R_SUCCESS is returned.
	 *If the port was already busy and sleep is YES, then the thread will sleep
	 *until the port is freed, then re-attempts the acquire.  If the port was
	 *already busy and sleep in NO, then IO_R_EXCLUSIVE_ACCESS is returned.
	 */
    virtual IOReturn acquirePort(bool sleep);
    
    /* release sets the state of the port object to available and wakes up any
	 *threads sleeping for access to this port.  It will return IO_R_SUCCESS
	 *if the port was in a busy state, and IO_R_NOT_OPEN if it was available.
	 */
    virtual IOReturn releasePort();
    
    /*
     *Set the state for the port device.
     */
    virtual IOReturn setState(UInt32 state, UInt32 mask);
	
    /*
     *Get the state for the port device.
     */
    virtual UInt32 getState();
    
    /*
     *Wait for the at least one of the state bits defined in mask to be equal
     *to the value defined in state.
     *Check on entry then sleep until necessary.
     */
    virtual IOReturn watchState(UInt32 *state, UInt32 mask);
	
    /* nextEvent returns the type of the next event on the RX queue.  If no
     *events are present on the RX queue, then EOQ is returned.
     */
    virtual UInt32 nextEvent();
	
    /* executeEvent causes the specified event to be processed immediately.
     *This is primarily used for channel control commands like START & STOP
     */
    virtual IOReturn executeEvent(UInt32 event, UInt32 data);
	
    /* requestEvent processes the specified event as an immediate request and
     *returns the results in data.  This is primarily used for getting link
     *status information and verifying baud rate and such.
     */
    virtual IOReturn requestEvent(UInt32 event, UInt32 *data);
	
    /* enqueueEvent will place the specified event into the TX queue.  The
     *sleep argument allows the caller to specify the enqueueEvent's
     *behaviour when the TX queue is full.  If sleep is true, then this
     *method will sleep until the event is enqueued.  If sleep is false,
     *then enqueueEvent will immediatly return IO_R_RESOURCE.
     */
    virtual IOReturn enqueueEvent(UInt32 event, UInt32 data, bool sleep);
	
    /* dequeueEvent will remove the oldest event from the RX queue and return
     *it in event & data.  The sleep argument defines the behaviour if the RX
     *queue is empty.  If sleep is true, then this method will sleep until an
     *event is available.  If sleep is false, then an EOQ event will be
     *returned.  In either case IO_R_SUCCESS is returned.
     */
    virtual IOReturn dequeueEvent(UInt32 *event, UInt32 *data, bool sleep);
	
    /* enqueueData will attempt to copy data from the specified buffer to the
     *TX queue as a sequence of VALID_DATA events.  The argument bufferSize
     *specifies the number of bytes to be sent.  The actual number of bytes
     *transferred is returned in transferCount.  If sleep is true, then this
     *method will sleep until all bytes can be transferred.  If sleep is
     *false, then as many bytes as possible will be copied to the TX queue.
     */
    virtual IOReturn enqueueData(UInt8 *buffer,  UInt32 size, UInt32 *count, bool sleep );
	
    /* dequeueData will attempt to copy data from the RX queue to the specified
     *buffer.  No more than bufferSize VALID_DATA events will be transferred.
     *In other words, copying will continue until either a non-data event is
     *encountered or the transfer buffer is full.  The actual number of bytes
     *transferred is returned in transferCount.
     *
     *The sleep semantics of this method are slightly more complicated than
     *other methods in this API:  Basically, this method will continue to
     *sleep until either minCount characters have been received or a non
     *data event is next in the RX queue.  If minCount is zero, then this
     *method never sleeps and will return immediatly if the queue is empty.
     *
     *The latency parameter specifies the maximum amount of time that should
     *pass after the first character is available before the routine returns.
     *This allows the caller to specify a 'packet' timeout.  The unit of the
     *latency parameter is microseconds, though the exact delay may vary
     *depending on the granularity of the timeout services available to the
     *driver.
     */
    virtual IOReturn dequeueData(UInt8 *buffer, UInt32 size, UInt32 *count, UInt32 min);
};