(define (cont-frac n d k)
 	(define (cont-frac-iter n d k result)
	 	(if (= k 0)
		 	result
			(cont-frac-iter n d (- k 1) (/ (n k) (+ (d k)  result)))))
	(cont-frac-iter n d k 0))

(define (f0 k) (/ 1.0 (cont-frac (lambda (i) 1.0) (lambda (i) 1.0) k)))
		 	
		 	
