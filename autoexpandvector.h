#ifndef AUTOEXPANDVECTOR_H
#define AUTOEXPANDVECTOR_H

#include <stdbool.h>

typedef struct object_ {
    void *data;
    int pos;
} object;

typedef struct autoexpandvec_ {
    int size;
    object *obj;
    int current_capacity;
} autoexpandvec;

autoexpandvec *aev_init ();
void aev_free(autoexpandvec *aev);
bool aev_add (autoexpandvec *aev, object *obj);
int aev_get (const autoexpandvec *aev, const object *obj);
object *aev_get_byidx (const autoexpandvec *aev, int idx);
void aev_set (const autoexpandvec *aev, const object *obj, int i);
bool aev_remove (autoexpandvec *aev, const object *obj);
int aev_size (const autoexpandvec *aev);
bool aev_contains (const autoexpandvec *aev, const object *obj);
void aev_trimtosize (autoexpandvec *aev, int size);

object *aev_newobj (int pos, void *data);
bool aev_obj_equals (const object *obj1, const object *obj2);

#endif
