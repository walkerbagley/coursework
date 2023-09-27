(define-module (ice-9 paradigms_d7))

(define-public pick
  (lambda (n lat)
    (cond
      ((zero? (- n 1)) (car lat))
      (else (pick (- n 1) (cdr lat))))))

(define-public firsts
  (lambda (l)
    (cond
      ((null? l) (list))
      (else (cons (car (car l)) (firsts (cdr l)))))))

;; returns the other player (e.g., given 'x', return 'o')
(define-public other
  (lambda (p)
    (cond
      ((eq? p 'o) 'x)
      (else 'o))))

;; does player 'p' win this game state?
;; p = x or o
;; e.g., (x x x o o e e e e) is a win for x
(define-public win?
  (lambda (p gs)
    (cond
      ((or (eq? (pick 1 gs) (pick 4 gs) (pick 7 gs) p)
           (eq? (pick 2 gs) (pick 5 gs) (pick 8 gs) p)
           (eq? (pick 3 gs) (pick 6 gs) (pick 9 gs) p)
           (eq? (pick 1 gs) (pick 2 gs) (pick 3 gs) p)
           (eq? (pick 4 gs) (pick 5 gs) (pick 6 gs) p)
           (eq? (pick 7 gs) (pick 8 gs) (pick 9 gs) p)
           (eq? (pick 1 gs) (pick 5 gs) (pick 9 gs) p)
           (eq? (pick 3 gs) (pick 5 gs) (pick 7 gs) p) ) #t)
       (else #f) )))

