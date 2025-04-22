(ql:quickload :cl-ppcre)

(defun parse-file (file)
  (loop for (a b c d) on (uiop:read-file-lines file) by #'cddddr
        collect (list (mapcar #'parse-integer (ppcre:all-matches-as-strings "\(\\d\)+" a))
                      (mapcar #'parse-integer (ppcre:all-matches-as-strings "\(\\d\)+" b))
                      (mapcar #'parse-integer (ppcre:all-matches-as-strings "\(\\d\)+" c)))))

;; time to code matrix operations!

(defun inverse-matrix (ix iy jx jy)
  (mapcar #'(lambda (n) (/ n (- (* ix jy) (* iy jx)))) (list jy (* iy -1) (* jx -1) ix)))

(defun mult-vec-by-matrix (ix iy jx jy vi vj)
  (list (+ (* vi ix) (* vj jx)) (+ (* vi iy) (* vj jy))))

(defun inverse-matrix-list (matrix)
  (inverse-matrix (first (first matrix)) (second (first matrix)) (first (second matrix)) (second (second matrix))))

(defun mult-vec-by-matrix-list (matrix vector)
  (mult-vec-by-matrix (first matrix) (second matrix) (third matrix) (fourth matrix) (first vector) (second vector)))

(defun solve-syseq (syseq)
  (mult-vec-by-matrix-list (inverse-matrix-list syseq) (third syseq)))

;; not necessary, input has no 0 sols / infinite sols
(defun check-syseq (syseq)
  (if (equal (/ (first (first syseq)) (second (first syseq))) (/ (first (second syseq)) (second (second syseq))))
      (if (equal (/ (first (first syseq)) (second (first syseq))) (/ (first (third syseq)) (second (third syseq))))
          '(0 0)
          nil)
      (solve-syseq syseq)))

(defun part1 (file)
  (reduce #'+ (mapcar #'(lambda (s) (if (and (integerp (first s)) (integerp (second s))) (+ (* 3 (first s)) (second s)) 0)) (mapcar #'solve-syseq (parse-file file)))))

;; is this a joke
(defun part2 (file)
  (reduce #'+ (mapcar #'(lambda (s) (if (and (integerp (first s)) (integerp (second s))) (+ (* 3 (first s)) (second s)) 0))
                      (mapcar #'(lambda (se) (solve-syseq (list (first se) (second se) (list (+ (first (third se)) 10000000000000) (+ (second (third se)) 10000000000000))))) (parse-file file)))))
