;; scheme daily homework 5
;; name: Walker Bagley
;; date: 9/1/23

;; utility functions
(define firsts
  (lambda (lat)
    (cond
      ((null? lat) '())
      (else (cons (car (car lat))
                  (firsts (cdr lat)))))))

(define member?
  (lambda (a lat)
    (cond
      ((null? lat) #f)
      ((eq? (car lat) a) #t)
      ((member? a (cdr lat)) #t)
      (else #f))))

(define subset?
  (lambda (set1 set2)
    (cond
      ((null? set1) #t)
      ((member? (car set1) set2) (subset? (cdr set1) set2))
      (else #f))))

;; data variables
(define dict  '((t o m a t o) (f i r e) (s a u c e) (c h i c k e n) (f r i e d) (f l a m e s)))
(define words '((o i l p r e s s u r e) (o i l t e m p) (m a g n e t i c c o m p a s s) (s e a t b e l t s) (e l t) (a i r s p e e d) (a l t i m e t e r) (t a c h o m e t e r) (m a n i f o l d) (f u e l g a u g e) (t e m p g a u g e) (l a n d i n g g e a r l i g h t)))

;; acronym finder
(define acronyms
  (lambda (lat1 lat2)
    (cond
      ((null? lat1) '())
      ((subset? (car lat1) (firsts lat2)) (cons (car lat1) (acronyms (cdr lat1) lat2)))
      (else (acronyms (cdr lat1) lat2)))))
;; your code here ;-)

(display (acronyms dict words))
(display "\n")

;; output should be:
;; ((t o m a t o) (f l a m e s))


