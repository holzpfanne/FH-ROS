;; Auto-generated. Do not edit!


(when (boundp 'koenig::custom)
  (if (not (find-package "KOENIG"))
    (make-package "KOENIG"))
  (shadow 'custom (find-package "KOENIG")))
(unless (find-package "KOENIG::CUSTOM")
  (make-package "KOENIG::CUSTOM"))

(in-package "ROS")
;;//! \htmlinclude custom.msg.html


(defclass koenig::custom
  :super ros::object
  :slots (_radmove _pos _radius ))

(defmethod koenig::custom
  (:init
   (&key
    ((:radmove __radmove) 0.0)
    ((:pos __pos) 0.0)
    ((:radius __radius) 0.0)
    )
   (send-super :init)
   (setq _radmove (float __radmove))
   (setq _pos (float __pos))
   (setq _radius (float __radius))
   self)
  (:radmove
   (&optional __radmove)
   (if __radmove (setq _radmove __radmove)) _radmove)
  (:pos
   (&optional __pos)
   (if __pos (setq _pos __pos)) _pos)
  (:radius
   (&optional __radius)
   (if __radius (setq _radius __radius)) _radius)
  (:serialization-length
   ()
   (+
    ;; float64 _radmove
    8
    ;; float64 _pos
    8
    ;; float64 _radius
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _radmove
       (sys::poke _radmove (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _pos
       (sys::poke _pos (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _radius
       (sys::poke _radius (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _radmove
     (setq _radmove (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _pos
     (setq _pos (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _radius
     (setq _radius (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get koenig::custom :md5sum-) "e608c3fdddc29a45d2145bc9a1790451")
(setf (get koenig::custom :datatype-) "koenig/custom")
(setf (get koenig::custom :definition-)
      "float64 radmove
float64 pos
float64 radius
")



(provide :koenig/custom "e608c3fdddc29a45d2145bc9a1790451")


