(define (double x) (+ x x))
(define (halve x) (/ x 2))

(define (multi_iter a b n)
	(cond ((= b 0) n)
	 	((odd? b) (multi_iter a (- b 1) (+ a n)))
	 	((even? b) (multi_iter (double a) (halve b) n))))

(define (multi a b) (multi_iter a b 0))
