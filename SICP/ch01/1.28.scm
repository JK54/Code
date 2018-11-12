(define (f0 n) (fast-prime? n 12))

(define (fast-prime? n times)
 	(cond ((= times 0) true)
	 	  ((miller-rabin-test n) (fast-prime? n (- times 1)))
		  (else false)))
	
(define (miller-rabin-test n)
	(cond ((or (= n 2) (= n 1)) true)
		  ((= (remainder n 2) 0) false)
		  (else (try-it (random0 n) n))))

(define (try-it a n)
	 (if (= (expmod a (- n 1) n) 1)
		true
		false))

(define (expmod base expo m)
	(cond ((= expo 0) 1)
		  ((nontrivial-square-root? base m) 0)
		  ((even? expo) (remainder (square (expmod base (/ expo 2) m)) m))
	  	  (else (remainder (* base (expmod base (- expo 1) m)) m))))
	
(define (nontrivial-square-root? a n)
 	(if (and (not (= a 1)) (not (= a (- n 1))) (= 1 (remainder (square a) n)))
	  true
	  false))

(define (random0 n)
 	(let ((r (random n)))
	 	(if (or (= r (- n 1)) (= r 0))
		 	(random0 n)
			r)))
