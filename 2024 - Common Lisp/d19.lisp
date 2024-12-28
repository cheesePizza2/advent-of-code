(defun every-other (l)
  (if (null l) nil (cons (first l) (every-other (cddr l)))))

(defun read-file (file)
  (let ((rd (uiop:read-file-lines file)))
    (list (every-other (uiop:split-string (first rd) :separator ", ")) (cddr rd))))

(defun reduce-design (towel design)
  (when (and (>= (length design) (length towel)) (string-equal towel (subseq design 0 (length towel)))) (subseq design (length towel))))

(defun check-design (towels design)
  (if (member design towels :test #'string-equal)
      t
      (some #'(lambda (rd) (check-design towels rd)) (remove nil (mapcar #'(lambda (tl) (reduce-design tl design)) towels)))))

(defun part1 (file)
  (let* ((rd (read-file file)))
    (length (remove nil (mapcar #'(lambda (d) (check-design (first rd) d)) (second rd))))))
