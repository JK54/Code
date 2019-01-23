(load "1.38.scm")


(define (tan-cf x k) 
	(define (n k)
	 	(if (= k 1)
		 	x
			(- (square x))))
	
	(define (d k) 
	 	(- (* k 2) 1))
	(exact->inexact (cont-frac n d k)));the result will be error if without the "exact->inexact"
