(define (gcd a b)
 	(if (= b 0)
	 	a
		(gcd b (remainder a b))))
;Assump that the absolute value of n is less than d,otherwise the gcd of n and d will be a positive number(fixed,there is no need to make |n| bigger than |d|))
(define (make-rat n d)
 	(let ((g (gcd n d)))
	(if (positive? g)
	 	(cond ((and (negative? n) (negative? d)) (cons (/ n (- g)) (/ d (- g))))
		 	  (else (cons (/ n  g) (/ d g))))
		(cond ((and (positive? n) (negative? d)) (cons (/ n g) (/ d g)))
		 	  (else (cons (/ n (- g)) (/ d (- g))))))))

(define (numer x) (car x))
(define (denom x) (cdr x))

(define (print-rat x)
 	(newline)
	(display (numer x))
	(display "/")
	(display (denom x)))

