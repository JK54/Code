(define (fixed-point f first-guess)
	(define tolerance 0.00001)
 	(define (close-enough? v1 v2)
	 	(< (abs (- v1 v2)) tolerance))
	(define (try guess step)
	 	(let ((next (f guess)))
		 	(if (close-enough? guess next)
			 	(begin
				 	(newline)
				 	(display step)
					(display " steps\n")
					next)
				(try next (+ 1 step)))))
	(try first-guess 0))

(define (repeated f n)
 	(lambda(x)
	 	(if (= n 0)
		 	x
			((repeated f (- n 1)) (f x)))))

(define (average-damp f)
	(define (average x y) (/ (+ x y) 2))
 	(lambda (x) 
	 	(average x (f x))))

(define (average-damp-n n)
 	(lambda(x)
		((repeated (average-damp (lambda(y) )) ) n) 

(define (n-root? origin expo n)
 	(fixed-point (average-damp-n ) 1.0))
