<<<<<<< HEAD
(define (double x) (+ x x))
(define (halve x) (/ x 2))

(define (multi_iter a b n)
	(cond ((= b 0) n)
	 	((odd? b) (multi_iter a (- b 1) (+ a n)))
	 	((even? b) (multi_iter (double a) (halve b) n))))

(define (multi a b) (multi_iter a b 0))
=======
(define (multi a b) 
 		(define (halve x) (/ x 2))
		(define (double x) (* x 2))
 		(define (multi-iter a b n)
		 		(cond ((or (= b 0) (= a 0)) n)
				 	  ((even? b) (multi-iter (double a) (halve b) n))
					  (else (multi-iter a (- b 1) (+ n a)))))
		(multi-iter a b 0))
>>>>>>> ea9e3345b93ea8dd71ed7da1d4f03b7f9087d3b9
