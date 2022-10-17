#if defined _sort_array_included_ 
    #endinput
#endif
#define _sort_array_included_

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define INVALID_ARRAY_INDEX -1

// ------------------------------------- //
//             Macro guards              //
// ------------------------------------- //

#define SortArr@%0\32; SortArr@
#define SortArr@count_%0\32; SortArr@count_

// ------------------------------------- //
//              Definition               //
// ------------------------------------- //

#define SortedArray:%0<%1> \
        SortArr@%0[%1], SortArr@count_%0

// ------------------------------------- //
//              Functions                //  
// ------------------------------------- //

#define SortArray_Count(%0) \
        SortArr@count_%0

/* ---------------------------------------------------------------- */
/*  SortArray_Count(array)                                          */
/*                                                                  */
/*  Returns the count of elements from the sorted array.            */
/* ---------------------------------------------------------------- */

#define SortArray_Clear(%0) \
        SortArr@count_%0 = 0

/* ---------------------------------------------------------------- */
/*  SortArray_Clear(array)                                          */
/*                                                                  */
/*  Clear an sorted array.                                          */
/* ---------------------------------------------------------------- */

#define SortArray_Copy(%0,%1) \
        SortArr@%1 = SortArr@%0, SortArr@count_%1 = SortArr@count_%0 

/* ---------------------------------------------------------------- */
/*  SortArray_Copy(dest[], source[])                                */
/*                                                                  */
/*  Copy an sorted array in another.                                */
/* ---------------------------------------------------------------- */

#define SortArray_Contains(%0,%1) \
        (_SortArray_FindIndex(SortArr@%0, SortArr@count_%0, %1) != INVALID_ARRAY_INDEX)

/* ---------------------------------------------------------------- */
/*  SortArray_Contains(array[], value)                              */
/*                                                                  */
/*  Check if an value is in the sorted array.                       */
/*                                                                  */
/*                                                                  */
/*  Returns true if value exists, otherwise false.                  */
/* ---------------------------------------------------------------- */

#define SortArray_Insert(%0,%1) \
        _SortArray_Insert(SortArr@%0, SortArr@count_%0, %1) 

stock bool:_SortArray_Insert(array[], &count, value, const size = sizeof array) {
    if(count == size)
        return false;

    if(!count) 
        array[0] = value;

    else if(value >= array[count - 1])
        array[count] = value;

    else if(value <= array[0]) {
        memcpy(array[1], array[0], 0, count << 3, size - 1);
        array[0] = value;
    }

    else {
        new i = count - 1;

        while(value <= array[i] && i >= 0) 
            array[i + 1] = array[i--];
     
        array[i + 1] = value;
    }

    count ++;
    return true;
}

/* ---------------------------------------------------------------- */
/*  SortArray_Insert(array[], value)                                */
/*                                                                  */
/*  Insert an value in the sorted array.                            */
/*                                                                  */
/*                                                                  */
/*  Returns true for success, otherwise false.                      */
/* ---------------------------------------------------------------- */

#define SortArray_Remove(%0,%1) \
        _SortArray_Remove(SortArr@%0, SortArr@count_%0, %1) 

stock bool:_SortArray_Remove(array[], &count, value, const size = sizeof array) {
    new const value_index = _SortArray_FindIndex(array, count, value);

    if(value_index == INVALID_ARRAY_INDEX)
        return false;

    if(value == array[--count]) 
        return true;

    memcpy(array[value_index], array[value_index + 1], 0, count + 1 << 3, size - 1);
    return true;
}

/* ---------------------------------------------------------------- */
/*  SortArray_Remove(array[], value)                                */
/*                                                                  */
/*  Remove an value from the sorted array.                          */
/*                                                                  */
/*                                                                  */
/*  Returns true if value is removed, otherwise false if value      */
/*  don't exists.                                                   */
/* ---------------------------------------------------------------- */

// ------------------------------------- //
//          Internal Functions           //
// ------------------------------------- //

static stock _SortArray_FindIndex(const array[], count, value) {
    if(!count)
        return INVALID_ARRAY_INDEX;

    if(array[0] == value)
        return 0;

    if(array[count - 1] == value)
        return count - 1;

    new half = count / 2;

    if(array[half] == value)
        return half;

    if(value >= array[half]) {
        while(++half < count) {
            if(array[half] == value)
                return half;
        }
    }
    else if(value <= array[half]) {
        while(--half >= 0) {
            if(array[half] == value)
                return half;
        }
    }

    return INVALID_ARRAY_INDEX;
}   

/* ---------------------------------------------------------------- */
/*  _SortArray_FindIndex(array[], value)                            */
/*                                                                  */
/*  Get the index for a specific value from the sorted array.       */
/*                                                                  */
/*                                                                  */
/*  Returns the value's index, otherwise INVALID_ARRAY_INDEX.       */
/* ---------------------------------------------------------------- */