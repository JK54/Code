(define (same-parity x . y)
 	(define (isodd x)
	 	(if (odd? x)
		 	1
			0))
	(define len (length y))
	(define partity (isodd x))
	(define (iter count result)
	  	(if (= count len)
			result
			(if (= partity (isodd (list-ref y count)))
			 	(iter (+ count 1) (append result (list (list-ref y count))))
				(iter (+ count 1) result))))
	 (iter 0 (list x)))

(same-parity 1 2 3 4 5 6 7)
