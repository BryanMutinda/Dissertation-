
"use strict";

let inputs_outputs = require('./inputs_outputs.js');
let PantiltStatus = require('./PantiltStatus.js');
let ArmStatus = require('./ArmStatus.js');
let Alarms = require('./Alarms.js');
let InverterStatus = require('./InverterStatus.js');
let Pose2DStamped = require('./Pose2DStamped.js');
let encoders = require('./encoders.js');
let RobotnikMotorsStatus = require('./RobotnikMotorsStatus.js');
let MotorReferenceValue = require('./MotorReferenceValue.js');
let WatchdogStatusArray = require('./WatchdogStatusArray.js');
let PresenceSensorArray = require('./PresenceSensorArray.js');
let MotorStatus = require('./MotorStatus.js');
let MotorPID = require('./MotorPID.js');
let MotorsStatus = require('./MotorsStatus.js');
let named_input_output = require('./named_input_output.js');
let QueryAlarm = require('./QueryAlarm.js');
let PantiltStatusStamped = require('./PantiltStatusStamped.js');
let ElevatorStatus = require('./ElevatorStatus.js');
let SubState = require('./SubState.js');
let Axis = require('./Axis.js');
let OdomCalibrationStatus = require('./OdomCalibrationStatus.js');
let State = require('./State.js');
let ptz = require('./ptz.js');
let Pose2DArray = require('./Pose2DArray.js');
let alarmmonitor = require('./alarmmonitor.js');
let alarmsmonitor = require('./alarmsmonitor.js');
let SafetyModuleStatus = require('./SafetyModuleStatus.js');
let Interfaces = require('./Interfaces.js');
let Registers = require('./Registers.js');
let BatteryDockingStatus = require('./BatteryDockingStatus.js');
let OdomCalibrationStatusStamped = require('./OdomCalibrationStatusStamped.js');
let StringArray = require('./StringArray.js');
let StringStamped = require('./StringStamped.js');
let PresenceSensor = require('./PresenceSensor.js');
let BatteryDockingStatusStamped = require('./BatteryDockingStatusStamped.js');
let MotorsStatusDifferential = require('./MotorsStatusDifferential.js');
let WatchdogStatus = require('./WatchdogStatus.js');
let ElevatorAction = require('./ElevatorAction.js');
let AlarmSensor = require('./AlarmSensor.js');
let RecordStatus = require('./RecordStatus.js');
let MotorCurrent = require('./MotorCurrent.js');
let BatteryStatusStamped = require('./BatteryStatusStamped.js');
let MotorReferenceValueArray = require('./MotorReferenceValueArray.js');
let OdomManualCalibrationStatusStamped = require('./OdomManualCalibrationStatusStamped.js');
let MotorHeadingOffset = require('./MotorHeadingOffset.js');
let Logger = require('./Logger.js');
let BatteryStatus = require('./BatteryStatus.js');
let LaserStatus = require('./LaserStatus.js');
let named_inputs_outputs = require('./named_inputs_outputs.js');
let Data = require('./Data.js');
let BoolArray = require('./BoolArray.js');
let OdomManualCalibrationStatus = require('./OdomManualCalibrationStatus.js');
let LaserMode = require('./LaserMode.js');
let Register = require('./Register.js');
let Cartesian_Euler_pose = require('./Cartesian_Euler_pose.js');
let ReturnMessage = require('./ReturnMessage.js');
let SetElevatorAction = require('./SetElevatorAction.js');
let SetElevatorActionFeedback = require('./SetElevatorActionFeedback.js');
let SetElevatorFeedback = require('./SetElevatorFeedback.js');
let SetElevatorActionGoal = require('./SetElevatorActionGoal.js');
let SetElevatorResult = require('./SetElevatorResult.js');
let SetElevatorActionResult = require('./SetElevatorActionResult.js');
let SetElevatorGoal = require('./SetElevatorGoal.js');

module.exports = {
  inputs_outputs: inputs_outputs,
  PantiltStatus: PantiltStatus,
  ArmStatus: ArmStatus,
  Alarms: Alarms,
  InverterStatus: InverterStatus,
  Pose2DStamped: Pose2DStamped,
  encoders: encoders,
  RobotnikMotorsStatus: RobotnikMotorsStatus,
  MotorReferenceValue: MotorReferenceValue,
  WatchdogStatusArray: WatchdogStatusArray,
  PresenceSensorArray: PresenceSensorArray,
  MotorStatus: MotorStatus,
  MotorPID: MotorPID,
  MotorsStatus: MotorsStatus,
  named_input_output: named_input_output,
  QueryAlarm: QueryAlarm,
  PantiltStatusStamped: PantiltStatusStamped,
  ElevatorStatus: ElevatorStatus,
  SubState: SubState,
  Axis: Axis,
  OdomCalibrationStatus: OdomCalibrationStatus,
  State: State,
  ptz: ptz,
  Pose2DArray: Pose2DArray,
  alarmmonitor: alarmmonitor,
  alarmsmonitor: alarmsmonitor,
  SafetyModuleStatus: SafetyModuleStatus,
  Interfaces: Interfaces,
  Registers: Registers,
  BatteryDockingStatus: BatteryDockingStatus,
  OdomCalibrationStatusStamped: OdomCalibrationStatusStamped,
  StringArray: StringArray,
  StringStamped: StringStamped,
  PresenceSensor: PresenceSensor,
  BatteryDockingStatusStamped: BatteryDockingStatusStamped,
  MotorsStatusDifferential: MotorsStatusDifferential,
  WatchdogStatus: WatchdogStatus,
  ElevatorAction: ElevatorAction,
  AlarmSensor: AlarmSensor,
  RecordStatus: RecordStatus,
  MotorCurrent: MotorCurrent,
  BatteryStatusStamped: BatteryStatusStamped,
  MotorReferenceValueArray: MotorReferenceValueArray,
  OdomManualCalibrationStatusStamped: OdomManualCalibrationStatusStamped,
  MotorHeadingOffset: MotorHeadingOffset,
  Logger: Logger,
  BatteryStatus: BatteryStatus,
  LaserStatus: LaserStatus,
  named_inputs_outputs: named_inputs_outputs,
  Data: Data,
  BoolArray: BoolArray,
  OdomManualCalibrationStatus: OdomManualCalibrationStatus,
  LaserMode: LaserMode,
  Register: Register,
  Cartesian_Euler_pose: Cartesian_Euler_pose,
  ReturnMessage: ReturnMessage,
  SetElevatorAction: SetElevatorAction,
  SetElevatorActionFeedback: SetElevatorActionFeedback,
  SetElevatorFeedback: SetElevatorFeedback,
  SetElevatorActionGoal: SetElevatorActionGoal,
  SetElevatorResult: SetElevatorResult,
  SetElevatorActionResult: SetElevatorActionResult,
  SetElevatorGoal: SetElevatorGoal,
};
