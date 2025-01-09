(defun fstrings-to-lstrings (fstrings)
  (when fstrings (cons (subseq fstrings 0 7)
                       (fstrings-to-lstrings (nthcdr 8 fstrings)))))

(defun lstring-to-key (lstring)
  (loop for col from 0 to 4
        collect (loop for i from 5 downto 0
                      if (char-equal (aref (nth i lstring) col) #\.)
                      return (- 5 i))))

(defun lstring-to-lock (lstring)
  (loop for col from 0 to 4
        collect (loop for i from 1 to 6
                      if (char-equal (aref (nth i lstring) col) #\.)
                      return (1- i))))

(defun parse-lstring (lstring)
  (if (string-equal (first lstring) "#####")
      (setf *temp-locks* (cons (lstring-to-lock lstring) *temp-locks*))
      (setf *temp-keys* (cons (lstring-to-key lstring) *temp-keys*))))

(defun parse-file (file)
  (defparameter *temp-locks* nil)
  (defparameter *temp-keys* nil)
  (mapc #'parse-lstring (fstrings-to-lstrings (uiop:read-file-lines file)))
  (list *temp-locks* *temp-keys*))

(defun check-pair (lock key)
  (if (null lock) t
      (when (< (+ (first lock) (first key)) 6) (check-pair (cdr lock) (cdr key)))))

(defun count-pairs (locks keys)
  (apply #'+ (mapcar #'(lambda (lock)
                         (length (remove-if-not #'(lambda (key) (check-pair lock key)) keys)))
                     locks)))

(defun part1 (file)
  (apply #'count-pairs (parse-file file)))
