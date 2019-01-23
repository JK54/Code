(define (subsets s)
 	(if (null? s)
	 	(list s)
		(let ((rest (subsets (cdr s))))
	 	(append rest
			 		(map (lambda (x)
						  	(cons (car s) x))
						 rest)))))

(trace-entry subsets)
(define s (list 1 2 3))
(subsets s)
