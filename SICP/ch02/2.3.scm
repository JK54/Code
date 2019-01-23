(load "2.2.scm")

(define (area rec)
 	(* (get-length rec) (get-width rec)))
(define (perimeter rec)
 	(* 2 (+ (get-length rec) (get-width rec))))

(define rectangle
 	(lambda(a b c d)
	 	(make-segment a b c d)))

(define (get-length rec)
	(abs (- (x-point (start-segment rec)) (x-point (end-segment rec)))))
(define (get-width rec)
	(abs (- (y-point (start-segment rec)) (y-point (end-segment rec)))))

(define rec1 (rectangle 1 2 3 4))

(display (area rec1))
(newline)
(display (perimeter rec1))
