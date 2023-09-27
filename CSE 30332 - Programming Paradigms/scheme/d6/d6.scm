;; scheme daily homework 6
;; name: Walker Bagley
;; date: 9/4/23

(define sum*
  (lambda (ttup)
    (cond
	  ((null? ttup) 0)
      ((null? (cdr ttup)) (car (car ttup)))
      (else (+ (sum* (car (cdr ttup))) (sum* (cons (car ttup) (cdr (cdr ttup)))))))))

;; tests!
(display (sum* '((5)) ))
(display "\n")

(display (sum* '((0) ((0) ((5))) ((0) ((10)))) ))
(display "\n")

(display (sum* '((0) ((0) ((5) ((7)))) ((0) ((10) ))) ))
(display "\n")

(display (sum* '((0) ((0) ((5) ((7) ) ((8) ))) ((0) ((10) ))) ))
(display "\n")

;; correct output:
;;   $ guile d6.scm
;;   5
;;   15
;;   22
;;   30

