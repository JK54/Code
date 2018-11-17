(define (smooth-n f x n)
	(define dx 0.01)
	(define (avg y) (/ (+ (f (- x dx)) y (f (+ x dx))) 3))
	(define (iter n result)
	 	(if (= n 0)
		 	result
			(iter (- n 1) (avg result))))
	(iter n (f x)))
