(define (product a b interval)
 	(if (> a b)
	 	1
		(* a (product (+ a interval) b interval))))

(define (product-i a b interval)
	(define (iter a b interval result)
		(if (> a b)
		 	result
			(iter (+ a interval) b interval (* result a))))
	(iter a b interval 1))

(define (factorial a b)
 	(product-i a b 1))

(define (quarter-of-pi n)
 	(define eh (if (even? n)
					n
					(- n 1)))
 	(* 2.0 eh (/ (square (product-i 4 (- eh 2) 2)) (square (product-i 3 n 2)))))

(define (pi n) (* 4 (quarter-of-pi n)))
