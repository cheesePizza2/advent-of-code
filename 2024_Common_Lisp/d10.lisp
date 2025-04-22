(defun parse-file (file)
  (mapcar #'(lambda (s) (mapcar #'digit-char-p (coerce s 'list))) (uiop:read-file-lines file)))

(defun mget (map x y)
  (nth x (nth y map)))

(defun trailhead-search (curval map x y)
  (cond ((or (< x 0) (< y 0) (>= x (length (first map))) (>= y (length map))) nil)
        ((not (equal (+ curval 1) (mget map x y))) nil)
        ((equal curval 8) (list (list x y)))
        (t (append (trailhead-search (+ curval 1) map (+ x 1) y)
                   (trailhead-search (+ curval 1) map (- x 1) y)
                   (trailhead-search (+ curval 1) map x (+ y 1))
                   (trailhead-search (+ curval 1) map x (- y 1))))))

(defun sum-map (map)
  (loop for y from 0 to (- (length map) 1)
        summing (loop for x from 0 to (- (length (first map)) 1)
                      if (zerop (mget map x y))
                      sum (length (remove-duplicates (trailhead-search -1 map x y) :test #'equal)) into itot
                      finally (return itot)) into otot
        finally (return otot)))

(defun part1 (file)
  (sum-map (parse-file file)))

(defun trailrate-search (curval map x y)
  (cond ((or (< x 0) (< y 0) (>= x (length (first map))) (>= y (length map))) 0)
        ((not (equal (+ curval 1) (mget map x y))) 0)
        ((equal curval 8) 1)
        (t (+ (trailrate-search (+ curval 1) map (+ x 1) y)
              (trailrate-search (+ curval 1) map (- x 1) y)
              (trailrate-search (+ curval 1) map x (+ y 1))
              (trailrate-search (+ curval 1) map x (- y 1))))))

(defun sum-rate (map)
  (loop for y from 0 to (- (length map) 1)
        summing (loop for x from 0 to (- (length (first map)) 1)
                      if (zerop (mget map x y))
                      sum (trailrate-search -1 map x y) into itot
                      finally (return itot)) into otot
        finally (return otot)))

(defun part2 (file)
  (sum-rate (parse-file file)))
