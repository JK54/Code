(define (repeated f n)
	(lambda (y)
	 	(if (= n 0)
		 	y
			((repeated f (- n 1)) (f y)))))
