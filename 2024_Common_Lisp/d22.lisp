(defun read-file (file)
  (mapcar #'parse-integer (uiop:read-file-lines file)))

(defun get-next-secret (n)
  (setf n (mod (logxor n (ash n 6)) 16777216))
  (setf n (mod (logxor n (ash n -5)) 16777216))
  (setf n (mod (logxor n (ash n 11)) 16777216))
  n)

(defun get-step-secret (n step)
  (if (zerop step)
      n
      (get-next-secret (get-step-secret n (1- step)))))

(defun get-2000-secret (n)
  (get-step-secret n 2000))

(defun part1 (file)
  (apply #'+ (mapcar #'get-2000-secret (read-file file))))

(defun get-initials (s0)
  (let* ((s1 (get-next-secret s0))
         (s2 (get-next-secret s1))
         (s3 (get-next-secret s2)))
    (list s3
          (- (mod s1 10) (mod s0 10))
          (- (mod s2 10) (mod s1 10))
          (- (mod s3 10) (mod s2 10)))))

(defun get-step (old c3 c2 c1 step)
  (if (zerop step)
      nil
      (let* ((new (get-next-secret old))
             (c0 (- (mod new 10) (mod old 10))))
        (cons (list (mod new 10) c3 c2 c1 c0) (get-step new c2 c1 c0 (1- step))))))

(defun get-list-nums (n)
  (remove-duplicates (apply #'get-step (append (get-initials n) (list 1996))) :test #'(lambda (a b) (equal (rest a) (rest b)))))

(defun track-buyers (buyers)
  (let ((tracker nil))
    (loop for buyer in buyers
          do (loop for value in (get-list-nums buyer)
                   do (let ((pos (member value tracker :test #'(lambda (a b) (equal (rest a) (rest b))))))
                        (if pos
                            (incf (caar pos) (first value))
                            (setf tracker (cons value tracker))))))
    tracker))

(defun get-highest (l)
  (if (null l)
      0
      (max (caar l) (get-highest (cdr l)))))

(defun part2 (file)
  (get-highest (track-buyers (read-file file))))
