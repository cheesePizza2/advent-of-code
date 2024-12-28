(ql:quickload :cl-ppcre)

(defun parse-file (file)
  (mapcar #'(lambda (str) (mapcar #'parse-integer (ppcre:all-matches-as-strings "-?(\\d)+" str))) (uiop:read-file-lines file)))

(defun step-robot (robot sx sy steps)
  (list (mod (+ (first robot) (* (third robot) steps)) sx)
        (mod (+ (second robot) (* (fourth robot) steps)) sy)))

(defvar *upleft* 0)
(defvar *upright* 0)
(defvar *downleft* 0)
(defvar *downright* 0)

(defun rob-quad (robot sx sy)
  (let ((pos (step-robot robot sx sy steps))
        (mdx (/ (- sx 1) 2))
        (mdy (/ (- sy 1) 2)))
    (cond ((or (equal (first pos) mdx) (equal (second pos) mdy)) nil)
          ((and (< (first pos) mdx) (< (second pos) mdy)) (incf *upleft*))
          ((and (> (first pos) mdx) (< (second pos) mdy)) (incf *upright*))
          ((and (< (first pos) mdx) (> (second pos) mdy)) (incf *downleft*))
          ((and (> (first pos) mdx) (> (second pos) mdy)) (incf *downright*)))))

(defun part1 (file sx sy)
  (setf *upleft* 0 *upright* 0 *downleft* 0 *downright* 0)
  (mapcar #'(lambda (rob) (rob-quad rob sx sy)) (parse-file file))
  (* *upleft* *upright* *downleft* *downright*))

(defun check-for-tree (robots)
  (if (equal (length robots) (length (delete-duplicates robots :test #'equal))) t))

(defun part2 (file sx sy)
  (let ((robs (parse-file file)))
    (loop for step from 0 to 10000
          if (check-for-tree (mapcar #'(lambda (r) (step-robot r sx sy step)) robs)) collect step)))
