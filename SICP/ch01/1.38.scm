(define (cont-frac n d k)
 	(define (cont-frac-iter k result)
	 	(if (= k 0)
		 	result
			(cont-frac-iter (- k 1) (/ (n k) (+ (d k)  result)))))
	(cont-frac-iter k 0))

(define (n k) 1)

(define (d k)
 	(if (= (remainder (+ 1 k) 3) 0)
	 	(* 2 (/ (+ 1 k) 3))
		1))

(define (f0 k) (+ 2.0 (cont-frac n d k)))
		 	
		 	
