#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "autoexpandvector.h"

/*
    AEV Constants
*/
const int AEV_INIT_CAPACITY = 5;
const int AEV_CAPA_DELTA = 5;
/*
    Initialize the autoexpandvector
*/
autoexpandvec *
aev_init () {
    autoexpandvec *aev;
    aev = (autoexpandvec *) malloc(sizeof(struct autoexpandvec_));
    aev->current_capacity = AEV_INIT_CAPACITY;
    aev->obj = (object *) malloc (sizeof(struct object_) * aev->current_capacity);
    aev->size = 0;
    return aev;
}

/*
    free the autoexpand vector
*/
void
aev_free(autoexpandvec *aev) {
    free(aev->obj);
    free(aev);
}

/*
    Add the object to the vector and increase the vector's size
    @param autoexpandvec *
    @param object *
    @return boolean value
*/
bool
aev_add (autoexpandvec *aev, object *obj) {
    int old_size = aev_size(aev);
    int new_capacity;
    (aev->size)++;
    if (old_size == aev->current_capacity) {
        //Expand the vector
        new_capacity = aev->current_capacity + AEV_CAPA_DELTA;
        aev->obj = realloc(aev->obj, new_capacity);
    }
    (aev->obj)[old_size] = *obj;
    return true;
}

/*
    Get the index of an object
    @param const autoexpandvec *aev
    @param const object *obj
    @return int index value
*/
int
aev_get (const autoexpandvec *aev, const object *obj) {
    int idx = -1;
    for (int i = 0; i < aev_size (aev); i++) {
        if (aev->obj[i].pos == obj->pos) {
            idx = i;
            break;
        }
    }
    return idx;
}

/*
    get the object by the index
    @param const autoexpandvec *aev
    @param int index
    return the object
*/
object *
aev_get_byidx (const autoexpandvec *aev, int idx) {
    return &(aev->obj[idx]);
}

/*
    set the object into a given vector
    @param const object
    @param int index
*/
void
aev_set (const autoexpandvec *aev, const object *obj, int i) {
    aev->obj[i].pos = obj->pos;
    aev->obj[i].data = obj->data;
}

/*
    remove an object from the vector and rescale the vector
    @param autoexpandvec vector
    @param const object
    @return bool is successful
*/
bool
aev_remove (autoexpandvec *aev, const object *obj) {
    bool ret = false;
    int length = aev_size (aev);
    int last_index = length - 1;
    int new_size, new_capacity;
    for (int i = 0; i < length; i++) {
        if (aev_obj_equals(aev_get_byidx(aev, i), obj)) {
            aev->size--;
            if (last_index > i) {
                memmove(aev->obj + i, aev->obj + i + 1, sizeof(struct autoexpandvec_) * (last_index - i));
                new_size = aev->size;
                new_capacity = aev->current_capacity - AEV_CAPA_DELTA;
                if (new_capacity > new_size) {
                    aev->obj = realloc(aev->obj, sizeof(struct autoexpandvec_));
                    aev->current_capacity = new_capacity;
                }
            }
            ret = true;
        }
    }
    return ret;
}

/*
Get the size of the vector
@param autoexpandvec
@return int size
*/
int
aev_size (const autoexpandvec *aev) {
    return aev->size;
}

/*
    Does the vector contains given object?
    @param const autoexpandvec vector
    @param const object *obj
    @return bool result
*/
bool
aev_contains (const autoexpandvec *aev, const object *obj) {
    return (aev_get(aev, obj) > -1);
}

/*
    Change the size of autoexpandvector
    @param autoexpandvec *aev
    @param int size
*/
void
aev_trimtosize (autoexpandvec *aev, int size) {
    aev->obj = realloc (aev->obj, sizeof(struct object_) * aev_size(aev) );
}

/*
    Create a new object given the parameters
    @param int position of the object
    @param void * data to be stored
    @return object * result
*/
object *
aev_newobj (int pos, void *data) {
    object *obj = malloc(sizeof(struct object_));
    obj->pos = pos;
    obj->data = data;
    return obj;
}

/*
    Check if the given two objects are equal
    @param const object *
    @param const object *
    @return bool result
*/
bool
aev_obj_equals (const object *obj1, const object *obj2) {
    bool res = false;
    if (obj1->data == obj2->data && obj1->pos == obj2->pos) {
        res = true;
    }
    return res;
}

