(define tolerance 0.00001)
(define (fixed-point f first-guess)
 	(define (close-enough? v1 v2)
	 	(< (abs (- v1 v2)) tolerance))
	(define (try guess)
	 	(let ((next (f guess)))
		 	(if (close-enough? guess next)
				next
				(try next))))
	(try first-guess))

(define (ee x)
 	(average x (/ (log 1000) (log x))))

(define (average x y) (/ (+ x y) 2))

(define (f0) (fixed-point ee 1.2))
