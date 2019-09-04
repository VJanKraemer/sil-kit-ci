// ------------------------------------------------------------
// Slave Setup
ControllerConfig slaveConfig;
slaveConfig.controllerMode = ControllerMode::Slave;
slaveConfig.baudRate = 20000;

slave->Init(slaveConfig);

// Register FrameStatusHandler
auto slave_FrameStatusHandler =
    [](ILinController*, const Frame&, FrameStatus, std::chrono::nanoseconds) {};
slave->RegisterFrameStatusHandler(slave_FrameStatusHandler);

// NOTE: No TX response is configured for the slave

// ------------------------------------------------------------
// Master Setup
ControllerConfig masterConfig;
masterConfig.controllerMode = ControllerMode::Master;
masterConfig.baudRate = 20000;

master->Init(masterConfig);

// Register FrameStatusHandler to receive data from the LIN slave
auto master_FrameStatusHandler =
    [](ILinController*, const Frame&, FrameStatus, std::chrono::nanoseconds) {};
master->RegisterFrameStatusHandler(master_FrameStatusHandler);

// ------------------------------------------------------------
// Perform TX from slave to master, i.e., the slave /is expected/
// to provide the frame response.
Frame frameRequest;
frameRequest.id = 0x11;
frameRequest.checksumModel = ChecksumModel::Enhanced;

// Use AUTOSAR interface to initiate the transmission.
master->SendFrame(frameRequest, FrameResponseType::SlaveResponse);

// ------------------------------------------------------------
// The following master callback will be triggered:
//  - LIN_RX_NO_RESPONSE for the master, since no slave did provide a response
master_FrameStatusHandler(master, frameRequest, FrameStatus::LIN_RX_NO_RESPONSE, timeEndOfFrame);
//  The slave_FrameStatusHandler will not be called!