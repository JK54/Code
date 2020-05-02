#include "../include/myapue.h"

//FIXME : _r version of function(getenv, for example) is defined in bsd, not in linux.
//To add variable in process environ table, require for memory allocation.
//If require for signal-safe, the only way is to use sigprocmask to suspend signal,
//but can we call it singal-safe when block signal?
//Yes, it is.
