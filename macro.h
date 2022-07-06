
#ifndef _macro_
#define _macro_

//dampened loop, we may need it during maps generation
#define STANDARD_DAMPEN (1000)
#define DAMPENED_LOOP(CONDITION,MAX) \
 for(int dampen=0;dampen<MAX && (CONDITION);dampen++)

//just some easy debugging
#define print(...); {fprintf(stdout,__VA_ARGS__);fflush(stdout);}
#define error(...); {fprintf(stderr,__VA_ARGS__);fflush(stderr);}
#define fatal(...); {fprintf(stderr,__VA_ARGS__);fflush(stderr);exit(-1);}

//just some easy distance functions
#define distanceX(X0,Y0,X1,Y1) (abs((X0)-(X1)))
#define distanceY(X0,Y0,X1,Y1) (abs((Y0)-(Y1)))
#define distanceXY(X0,Y0,X1,Y1) (abs((X0)-(X1))+abs((Y0)-(Y1)))
#define distance(X0,Y0,X1,Y1) sqrt(pow((X0)-(X1),2)+pow((Y0)-(Y1),2))

#endif

