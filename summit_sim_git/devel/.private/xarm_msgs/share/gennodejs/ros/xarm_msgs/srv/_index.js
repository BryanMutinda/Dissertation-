
"use strict";

let SetLoad = require('./SetLoad.js')
let ClearErr = require('./ClearErr.js')
let SetToolModbus = require('./SetToolModbus.js')
let GetControllerDigitalIO = require('./GetControllerDigitalIO.js')
let GripperConfig = require('./GripperConfig.js')
let TCPOffset = require('./TCPOffset.js')
let SetDigitalIO = require('./SetDigitalIO.js')
let GetDigitalIO = require('./GetDigitalIO.js')
let GripperState = require('./GripperState.js')
let ConfigToolModbus = require('./ConfigToolModbus.js')
let SetInt16 = require('./SetInt16.js')
let SetAxis = require('./SetAxis.js')
let Move = require('./Move.js')
let GetAnalogIO = require('./GetAnalogIO.js')
let GetErr = require('./GetErr.js')
let GripperMove = require('./GripperMove.js')

module.exports = {
  SetLoad: SetLoad,
  ClearErr: ClearErr,
  SetToolModbus: SetToolModbus,
  GetControllerDigitalIO: GetControllerDigitalIO,
  GripperConfig: GripperConfig,
  TCPOffset: TCPOffset,
  SetDigitalIO: SetDigitalIO,
  GetDigitalIO: GetDigitalIO,
  GripperState: GripperState,
  ConfigToolModbus: ConfigToolModbus,
  SetInt16: SetInt16,
  SetAxis: SetAxis,
  Move: Move,
  GetAnalogIO: GetAnalogIO,
  GetErr: GetErr,
  GripperMove: GripperMove,
};
