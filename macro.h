
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

#endif

