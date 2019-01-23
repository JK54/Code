(define tolerance 0.00001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
	(< (abs (- v1 v2)) tolerance))
  (define (try guess step)
	(let ((next (f guess)))
	  (if (close-enough? guess next)
		(begin
		  (display step)
		  next)
		(try next (+ step 1)))))
  (try first-guess 0))

(define (repeated f n)
  (if (= n 1)
	f
	(lambda (x)
	  (let ((fs (repeated f (- n 1))))
		(f (fs x))))))

(define (lg n)
	(cond ((> (/ n 2) 1)
		 (+ 1 (lg (/ n 2))))
		((< (/ n 2) 1)
		 0)
		(else
		  1)))
; (define (expt base n)
  ; (if (= n 0)
	; 1
	; ((repeated (lambda (x) (* base x)) n) 1)))

(define (average-damp-n-times f n)
	((repeated average-damp n) f))

(define (average-damp f)
	(define (average x y)
  		(/ (+ x y) 2))
  	(lambda (x)
		(average x (f x))))

(define (damped-nth-root n damp-times)
  (lambda (x)
	(fixed-point
	  (average-damp-n-times
		(lambda (y)
		  (/ x (expt y (- n 1))))
		damp-times)
	  1.0)))

(define (nth-root n)
  (damped-nth-root n (lg n)))

(define 10th-root (nth-root 10))
