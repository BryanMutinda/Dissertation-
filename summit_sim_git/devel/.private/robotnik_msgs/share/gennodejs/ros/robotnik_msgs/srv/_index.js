
"use strict";

let SetNamedDigitalOutput = require('./SetNamedDigitalOutput.js')
let set_height = require('./set_height.js')
let set_mode = require('./set_mode.js')
let set_CartesianEuler_pose = require('./set_CartesianEuler_pose.js')
let get_alarms = require('./get_alarms.js')
let SetBuzzer = require('./SetBuzzer.js')
let get_mode = require('./get_mode.js')
let SetTransform = require('./SetTransform.js')
let SetCurrent = require('./SetCurrent.js')
let set_modbus_register_bit = require('./set_modbus_register_bit.js')
let set_ptz = require('./set_ptz.js')
let get_digital_input = require('./get_digital_input.js')
let SetString = require('./SetString.js')
let set_named_digital_output = require('./set_named_digital_output.js')
let get_modbus_register = require('./get_modbus_register.js')
let set_modbus_register = require('./set_modbus_register.js')
let Record = require('./Record.js')
let SetMotorMode = require('./SetMotorMode.js')
let GetMotorsHeadingOffset = require('./GetMotorsHeadingOffset.js')
let enable_disable = require('./enable_disable.js')
let SetLaserMode = require('./SetLaserMode.js')
let LoggerQuery = require('./LoggerQuery.js')
let ResetFromSubState = require('./ResetFromSubState.js')
let set_odometry = require('./set_odometry.js')
let GetPOI = require('./GetPOI.js')
let InsertTask = require('./InsertTask.js')
let SetMotorStatus = require('./SetMotorStatus.js')
let axis_record = require('./axis_record.js')
let ack_alarm = require('./ack_alarm.js')
let SetMotorPID = require('./SetMotorPID.js')
let SetElevator = require('./SetElevator.js')
let SetEncoderTurns = require('./SetEncoderTurns.js')
let SetInt16 = require('./SetInt16.js')
let GetBool = require('./GetBool.js')
let SetByte = require('./SetByte.js')
let set_analog_output = require('./set_analog_output.js')
let QueryAlarms = require('./QueryAlarms.js')
let set_digital_output = require('./set_digital_output.js')
let home = require('./home.js')
let set_float_value = require('./set_float_value.js')
let GetPTZ = require('./GetPTZ.js')

module.exports = {
  SetNamedDigitalOutput: SetNamedDigitalOutput,
  set_height: set_height,
  set_mode: set_mode,
  set_CartesianEuler_pose: set_CartesianEuler_pose,
  get_alarms: get_alarms,
  SetBuzzer: SetBuzzer,
  get_mode: get_mode,
  SetTransform: SetTransform,
  SetCurrent: SetCurrent,
  set_modbus_register_bit: set_modbus_register_bit,
  set_ptz: set_ptz,
  get_digital_input: get_digital_input,
  SetString: SetString,
  set_named_digital_output: set_named_digital_output,
  get_modbus_register: get_modbus_register,
  set_modbus_register: set_modbus_register,
  Record: Record,
  SetMotorMode: SetMotorMode,
  GetMotorsHeadingOffset: GetMotorsHeadingOffset,
  enable_disable: enable_disable,
  SetLaserMode: SetLaserMode,
  LoggerQuery: LoggerQuery,
  ResetFromSubState: ResetFromSubState,
  set_odometry: set_odometry,
  GetPOI: GetPOI,
  InsertTask: InsertTask,
  SetMotorStatus: SetMotorStatus,
  axis_record: axis_record,
  ack_alarm: ack_alarm,
  SetMotorPID: SetMotorPID,
  SetElevator: SetElevator,
  SetEncoderTurns: SetEncoderTurns,
  SetInt16: SetInt16,
  GetBool: GetBool,
  SetByte: SetByte,
  set_analog_output: set_analog_output,
  QueryAlarms: QueryAlarms,
  set_digital_output: set_digital_output,
  home: home,
  set_float_value: set_float_value,
  GetPTZ: GetPTZ,
};
