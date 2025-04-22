(ql:quickload '(:cl-ppcre :cl-heap))

(defun read-file (file)
  (mapcar #'(lambda (s) (mapcar #'parse-integer (ppcre:all-matches-as-strings "(\\d)+" s))) (uiop:read-file-lines file)))

(defclass node ()
  ((pos :initarg :pos :accessor pos)
   (links :initarg :links :accessor links)
   (cost :initform nil :accessor cost)))

(defvar *nodes* nil)
(defvar *frontier* nil)

(defun map-nodes (bytes size)
  (setf *nodes* nil)
  (loop for y from 0 to size
        do (loop for x from 0 to size
                 if (not (member (list x y) bytes :test #'equal))
                 do (setf *nodes* (cons (make-instance 'node :pos (list x y) :links (list `(,x ,(1+ y)) `(,x ,(1- y)) `(,(1+ x) ,y) `(,(1- x) ,y))) *nodes*)))))

(defun find-node (coords)
  (first (member coords *nodes* :test #'(lambda (c n) (equal c (pos n))))))

(defun linknodes ()
  (loop for node in *nodes*
        do (setf (links node) (remove nil (mapcar #'find-node (links node))))))

(defun handle-node ()
  (let* ((node (cl-heap:dequeue *frontier*)))
    (mapcar #'(lambda (n) (unless (and (cost n) (<= (cost n) (cost node))) (progn (setf (cost n) (1+ (cost node))) (cl-heap:enqueue *frontier* n (- (cost n) (apply #'+ (pos n))))))) (links node))))

(defun part1 (file size kbsize)
  (let ((bytes (read-file file)))
    (map-nodes (nthcdr (- (length bytes) kbsize) (reverse bytes)) size))
  (linknodes)
  (setf *frontier* (make-instance 'cl-heap:priority-queue))
  (let ((fn (find-node '(0 0))))
    (setf (cost fn) 0)
    (cl-heap:enqueue *frontier* fn 0))
  (let ((endnode (find-node (list size size))))
    (loop while (null (cost endnode)) do (handle-node))
    (cost endnode)))
