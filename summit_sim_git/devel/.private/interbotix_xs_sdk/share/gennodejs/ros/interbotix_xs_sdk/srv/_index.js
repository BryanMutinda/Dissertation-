
"use strict";

let RegisterValues = require('./RegisterValues.js')
let MotorGains = require('./MotorGains.js')
let RobotInfo = require('./RobotInfo.js')
let Reboot = require('./Reboot.js')
let TorqueEnable = require('./TorqueEnable.js')
let OperatingModes = require('./OperatingModes.js')

module.exports = {
  RegisterValues: RegisterValues,
  MotorGains: MotorGains,
  RobotInfo: RobotInfo,
  Reboot: Reboot,
  TorqueEnable: TorqueEnable,
  OperatingModes: OperatingModes,
};
