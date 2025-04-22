(defun parse-file (file)
  (mapcar #'(lambda (s) (coerce s 'list)) (uiop:read-file-lines file)))

(defvar *regsearch* nil)
(defvar *curreg* nil)
(defvar *regions* nil)

(defun checkbounds (coord map)
  (or (< (car coord) 0) (< (cdr coord) 0) (>= (car coord) (length (first map))) (>= (cdr coord) (length map))))

(defun getcoord (coord map)
  (if (checkbounds coord map)
      nil
      (nth (car coord) (nth (cdr coord) map))))

(defun get-region (coord map curval)
  (if (and (equal (getcoord coord map) curval)
           (not (member coord *curreg* :test #'equal)))
      (progn (setf *curreg* (cons coord *curreg*))
             (get-region (cons (+ (car coord) 1) (cdr coord)) map curval)
             (get-region (cons (- (car coord) 1) (cdr coord)) map curval)
             (get-region (cons (car coord) (+ (cdr coord) 1)) map curval)
             (get-region (cons (car coord) (- (cdr coord) 1)) map curval))))

(defun get-regions (map)
  (setf *regsearch* nil)
  (setf *regions* nil)
  (loop for x from 0 to (- (length (first map)) 1)
        do (loop for y from 0 to (- (length map) 1)
                 do (setf *regsearch* (cons (cons x y) *regsearch*))))
  (loop while (> (length *regsearch*) 0)
        do (setf *curreg* nil)
        do (get-region (first *regsearch*) map (getcoord (first *regsearch*) map))
        do (setf *regions* (cons *curreg* *regions*))
        do (setf *regsearch* (set-difference *regsearch* *curreg* :test #'equal))))

(defun get-per-region (region)
  (loop for coord in region
        if (not (member (cons (+ (car coord) 1) (cdr coord)) region :test #'equal)) sum 1 into total
        if (not (member (cons (- (car coord) 1) (cdr coord)) region :test #'equal)) sum 1 into total
        if (not (member (cons (car coord) (+ (cdr coord) 1)) region :test #'equal)) sum 1 into total
        if (not (member (cons (car coord) (- (cdr coord) 1)) region :test #'equal)) sum 1 into total
        finally (return total)))

(defun get-price-region (region)
  (* (length region) (get-per-region region)))

(defun part1 (file)
  (get-regions (parse-file file))
  (reduce #'+ (mapcar #'get-price-region *regions*)))

(defun check-corner (coord region x y)
  (or (not (or (member (cons (+ (car coord) x) (cdr coord)) region :test #'equal)
               (member (cons (car coord) (+ (cdr coord) y)) region :test #'equal)))
      (and (member (cons (+ (car coord) x) (cdr coord)) region :test #'equal)
           (member (cons (car coord) (+ (cdr coord) y)) region :test #'equal)
           (not (member (cons (+ (car coord) x) (+ (cdr coord) y)) region :test #'equal)))))

(defun get-corn-region (region)
  (loop for coord in region
        if (check-corner coord region 1 1) sum 1 into total
        if (check-corner coord region -1 1) sum 1 into total
        if (check-corner coord region 1 -1) sum 1 into total
        if (check-corner coord region -1 -1) sum 1 into total
        finally (return total)))

(defun get-price-region-2 (region)
  (* (length region) (get-corn-region region)))

(defun part2 (file)
  (get-regions (parse-file file))
  (reduce #'+ (mapcar #'get-price-region-2 *regions*)))
