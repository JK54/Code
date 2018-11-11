(define (smallest-divisor n) 	
 	(define (divides? a b) (= (remainder b a) 0))
	(define (find-divisor n test-divisor)
	 	(cond ((> (square test-divisor) n) n)
		 	  ((divides? test-divisor n) test-divisor)
			  (else (find-divisor n (+ test-divisor 1)))))
	(find-divisor n 2))

(define (report-time el)
	(display " *** ")
	(display el))

(define (f0 n start-time) 
 		(smallest-divisor n) 
		(newline)
		(report-time (- (runtime) start-time)))
	
(define (f1 n ) (f0 n (runtime)))
