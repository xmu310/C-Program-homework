typedef struct _sMixedNumber{int64_t a;int64_t b;int64_t c;}sMixedNumber;
void mixed_add(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2);
void mixed_sub(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2);
void mixed_mul(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2);
void mixed_div(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2);
void simp(sMixedNumber *p);
void f();
void check(sMixedNumber *p);
