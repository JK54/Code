(define (cube_iter guess x)
 		(if (good-enough? guess x)
			guess
			(cube_iter (improve guess x) x)
		)
)

(define (improve guess x)
	(/ (+ (/ x (* guess guess)) (* 2 guess)) 3)
)

(define (good-enough? guess x)
 		(< (abs (- guess (improve guess x))) 0.0000001)
)

(define (cube x)
 		(cube_iter 1.0 x)
)

(cube 987654321)
