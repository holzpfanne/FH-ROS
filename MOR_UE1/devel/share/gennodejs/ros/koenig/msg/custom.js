// Auto-generated. Do not edit!

// (in-package koenig.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class custom {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.radmove = null;
      this.pos = null;
      this.radius = null;
    }
    else {
      if (initObj.hasOwnProperty('radmove')) {
        this.radmove = initObj.radmove
      }
      else {
        this.radmove = 0.0;
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = 0.0;
      }
      if (initObj.hasOwnProperty('radius')) {
        this.radius = initObj.radius
      }
      else {
        this.radius = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type custom
    // Serialize message field [radmove]
    bufferOffset = _serializer.float64(obj.radmove, buffer, bufferOffset);
    // Serialize message field [pos]
    bufferOffset = _serializer.float64(obj.pos, buffer, bufferOffset);
    // Serialize message field [radius]
    bufferOffset = _serializer.float64(obj.radius, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type custom
    let len;
    let data = new custom(null);
    // Deserialize message field [radmove]
    data.radmove = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pos]
    data.pos = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [radius]
    data.radius = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'koenig/custom';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e608c3fdddc29a45d2145bc9a1790451';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 radmove
    float64 pos
    float64 radius
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new custom(null);
    if (msg.radmove !== undefined) {
      resolved.radmove = msg.radmove;
    }
    else {
      resolved.radmove = 0.0
    }

    if (msg.pos !== undefined) {
      resolved.pos = msg.pos;
    }
    else {
      resolved.pos = 0.0
    }

    if (msg.radius !== undefined) {
      resolved.radius = msg.radius;
    }
    else {
      resolved.radius = 0.0
    }

    return resolved;
    }
};

module.exports = custom;
