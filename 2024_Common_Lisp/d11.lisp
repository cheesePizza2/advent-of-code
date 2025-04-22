(defun parse-file (file)
  (mapcar #'parse-integer (uiop:split-string (uiop:read-file-line file))))

(defun stone-count (stone step)
  (cond ((equal step 25) 1)
        ((equal stone 0) (stone-count 1 (+ step 1)))
        (t (let ((string (write-to-string stone)))
             (if (evenp (length string))
                 (+ (stone-count (parse-integer (subseq string 0 (/ (length string) 2))) (+ step 1))
                    (stone-count (parse-integer (subseq string (/ (length string) 2))) (+ step 1)))
                 (stone-count (* stone 2024) (+ step 1)))))))

(defun part1 (file)
  (apply #'+ (mapcar #'(lambda (st) (stone-count st 0)) (parse-file file))))

(defparameter *cache* '((0)))

(defun add-to-cache (step stone val)
  (if (assoc step *cache*)
      (if (not (assoc stone (cdr (assoc step *cache*))))
          (setf (cdr (last (assoc step *cache*))) (cons (cons stone val) nil)))
      (setf (cdr (last *cache*)) (cons (cons step (cons (cons stone val) nil)) nil))))

(defun stone-count-2 (stone step)
  (if (equal step 75)
      1
      (if (and (assoc step *cache*) (assoc stone (cdr (assoc step *cache*))))
          (cdr (assoc stone (cdr (assoc step *cache*))))
          (let ((result nil)
                (string (write-to-string stone)))
            (cond ((zerop stone) (setf result (stone-count-2 1 (+ step 1))))
                  ((evenp (length string)) (setf result (+ (stone-count-2 (parse-integer (subseq string 0 (/ (length string) 2))) (+ step 1))
                                                           (stone-count-2 (parse-integer (subseq string (/ (length string) 2))) (+ step 1)))))
                  (t (setf result (stone-count-2 (* stone 2024) (+ step 1)))))
            (add-to-cache step stone result)
            result))))

(defun part2 (file)
  (apply #'+ (mapcar #'(lambda (st) (stone-count-2 st 0)) (parse-file file))))
