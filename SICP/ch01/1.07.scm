(define (sqrt_iter guess x)
 		(if (good-enough? guess x)
			guess
			(sqrt_iter (improve guess x) x)
		)
)

(define (improve guess x)
	(/ (+ (/ x guess) guess) 2)
)

(define (good-enough? guess x)
 		(< (abs (- guess (improve guess x))) 0.0000001)
)

(define (sqrt1 x)
 		(sqrt_iter 1.0 x)
)

(sqrt1 250000000000)
