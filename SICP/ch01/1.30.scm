(define (sum term a next b)
 	(define (iter a result)
	 	(if (> a b)
		 	result
			(iter (next a) (+ result (term a)))))
	(iter a 0))

(define (idt x) x)
(define (next x) (+ 1 x))

(define (f0 a b) (sum idt a next b))

