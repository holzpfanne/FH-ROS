; Auto-generated. Do not edit!


(cl:in-package koenig-msg)


;//! \htmlinclude custom.msg.html

(cl:defclass <custom> (roslisp-msg-protocol:ros-message)
  ((radmove
    :reader radmove
    :initarg :radmove
    :type cl:float
    :initform 0.0)
   (pos
    :reader pos
    :initarg :pos
    :type cl:float
    :initform 0.0)
   (radius
    :reader radius
    :initarg :radius
    :type cl:float
    :initform 0.0))
)

(cl:defclass custom (<custom>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <custom>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'custom)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name koenig-msg:<custom> is deprecated: use koenig-msg:custom instead.")))

(cl:ensure-generic-function 'radmove-val :lambda-list '(m))
(cl:defmethod radmove-val ((m <custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader koenig-msg:radmove-val is deprecated.  Use koenig-msg:radmove instead.")
  (radmove m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader koenig-msg:pos-val is deprecated.  Use koenig-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'radius-val :lambda-list '(m))
(cl:defmethod radius-val ((m <custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader koenig-msg:radius-val is deprecated.  Use koenig-msg:radius instead.")
  (radius m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <custom>) ostream)
  "Serializes a message object of type '<custom>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'radmove))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'radius))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <custom>) istream)
  "Deserializes a message object of type '<custom>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radmove) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radius) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<custom>)))
  "Returns string type for a message object of type '<custom>"
  "koenig/custom")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'custom)))
  "Returns string type for a message object of type 'custom"
  "koenig/custom")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<custom>)))
  "Returns md5sum for a message object of type '<custom>"
  "e608c3fdddc29a45d2145bc9a1790451")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'custom)))
  "Returns md5sum for a message object of type 'custom"
  "e608c3fdddc29a45d2145bc9a1790451")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<custom>)))
  "Returns full string definition for message of type '<custom>"
  (cl:format cl:nil "float64 radmove~%float64 pos~%float64 radius~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'custom)))
  "Returns full string definition for message of type 'custom"
  (cl:format cl:nil "float64 radmove~%float64 pos~%float64 radius~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <custom>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <custom>))
  "Converts a ROS message object to a list"
  (cl:list 'custom
    (cl:cons ':radmove (radmove msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':radius (radius msg))
))
