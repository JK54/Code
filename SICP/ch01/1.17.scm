(define (halve a) (/ a 2))
(define (double a) (+ a a))

(define (multiply a b)
 	(cond ((or (= b 0) (= a 0)) 0)
	 	  ((even? b) (double (multiply a (halve b))))
		  (else (+ a (multiply a (+ b -1))))))
