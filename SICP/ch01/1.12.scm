(define (pascal-triangle-recursive row col)
 		(cond ((= row 0) 1)
		 	  ((= col 0) 1)
			  ((= row col) 1)
			  ((< row col) -1)
			  (else (+ (pascal-triangle-recursive (- row 1) (- col 1)) (pascal-triangle-recursive (- row 1) col)))))

(define (factorial_sub count n result)
 	(if (<= count  n) 
	 	(factorial_sub (+ count 1) n (* result count))
	 	result))

(define (factorial n) (factorial_sub 1 n 1))

(define (pascal-triangle-iterative row col)
		(/ (factorial row) (* (factorial col) (factorial (- row col)))))
		      
(define (f0 row col) (pascal-triangle-recursive row col))
(define (f1 row col) (pascal-triangle-iterative row col))
