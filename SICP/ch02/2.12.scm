(load "2.7.scm")

(define (make-center-percent c p)
 	(make-interval (* c (- 1 p)) (* c (+ 1 p))))
(define (center i)
 	(/ (+ (lower-bound i) (upper-bound i)) 2))
(define (percent i)
 	(/ (- (upper-bound i) (center i)) (center i)))

(percent (make-center-percent 10 0.145))
