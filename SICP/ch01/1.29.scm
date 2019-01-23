(define (cube x) (* x x x))

(define (simpson-sub f a b k n)
     ; use (> a b) here will cause much bigger deviation,because that the last round variable a will be a bit bigger than b,hence the loop break out earlier. 
 	(if (> k n)
	 	0
		(+ (* (cond ((or (= k 0) (= k n)) 1)
			   		((even? k) 2)
					(else 4))
			  (f a))
		   (simpson-sub f (+ a (/ 1.0 n)) b (+ k 1) n))))

(define (f0 a b n) (* (/ (- b a) 3 n) (simpson-sub cube a b 0 n)))

