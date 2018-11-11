(define (search-for-primes count st)
 	(cond	((= count 3) true)
	 		((prime? st) (timed-prime-test st) (search-for-primes (+ count 1) (next-odd (+ st 1))))
			(else (search-for-primes count (next-odd (+ st 1))))))
	
(define (timed-prime-test n)
 	(newline)
	(display n)
	(start-prime-test n (runtime)))

(define (start-prime-test n start-time)
 	(if (prime? n)
	 	(report-prime (- (runtime) start-time))))

(define (report-prime elaspsed-time)
	(display " *** ")
	(display elaspsed-time))

(define (prime? n)
 	(define (prime?-iter count n)
 		(cond ((> (square count) n) true)
	 	 	  ((= (remainder n count) 0) false)
		  	  (else (prime?-iter (+ count 1) n))))
	(prime?-iter 2 n))

(define (next-odd n)
 		(if (= (remainder n 2) 0)
			(+ n 1)
			(+ n 2)))

(define (f0 n) (search-for-primes 0 n))
