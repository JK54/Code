(load "Fermat_Test.scm")
(define (search-for-primes count st)
 	(cond	((= count 3) true)
	 		((fast-prime? st 5) (timed-prime-test st) (search-for-primes (+ count 1) (next-odd st)))
			(else (search-for-primes count (next-odd st)))))
	
(define (timed-prime-test n)
 	(newline)
	(display n)
	(start-prime-test n (runtime)))

(define (start-prime-test n start-time)
 	(if (fast-prime? n 5)
	 	(report-prime (- (runtime) start-time))))

(define (report-prime elaspsed-time)
	(display " *** ")
	(display elaspsed-time))

(define (next-odd n)
 		(if (= (remainder n 2) 0)
			(+ n 1)
			(+ n 2)))

(define (f0 n) (search-for-primes 0 n))
