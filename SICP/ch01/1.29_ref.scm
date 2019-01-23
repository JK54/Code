(define (sum term a next b)
	(if (> a b)
	 	0
		(+ (term a)
		   (sum term (next a) next b))))

(define (cube x) (* x x x))

(define (simpson f a b n)
 	(define h (/ (- b a) n))
	(define (factor k)
	 	(cond ((or (= k 0) (= k n)) 1)
		 	  ((even? k) 2)
			  (else 4)))
	(define (y k) (f (+ a (* k h))))
	(define (term k) (* (factor k) (y k)))
	(define (next k) (+ 1 k))
	(* (/ h 3) (sum term 0 next n)))


