#include <stdio.h>
#include <stdlib.h>

#include "autoexpandvector.h"

int main () {
    autoexpandvec *aev = aev_init();
    object *obj = aev_newobj(0, (void *)123);
    aev_add(aev, obj);
    object *test = aev_get_byidx(aev, aev_get(aev, obj));
    printf("%d\n", test->pos);
    printf("%d\n", (int)test->data);
    printf("%d\n", aev_size(aev));
    printf("%d\n", aev->current_capacity);
    if (aev_remove(aev, obj)) {
        printf("%d\n", aev_size(aev));
        printf("%d\n", aev->current_capacity);
    }
    aev_free(aev);
    free(obj);
    return 0;
}
