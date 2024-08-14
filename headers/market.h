#ifndef __CppOptions__Market__
#define __CppOptions__Market__

#include "calendar.h"
#include "date.h"
#include "options.h"

/*
       I haven't really figured out what this class should do, 
       think of it as the place where everything happens, where trades 
       take place. It's like the common groud where rules are imposed. 
*/

#include <vector>

class Market{
private:
       const Calendar cal;
       Market();
public:
       Market setUp();
};

#endif