/**
 * @file Stamp_t.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-16
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_LIB_TIME_STAMPT_T_HPP_
#define _LIMINAL_LIB_TIME_STAMPT_T_HPP_

#include "Unit.hpp"

namespace time_ {
    
    using Stamp_t = long long int; // FIXME : should this be a class ?

    /**
     * @brief Convert in UNIX stamp
     * 
     * @param stamp 
     * @param inputUnit 
     * @param outputUnit 
     * @return long double 
    */
    Stamp_t convert(const Stamp_t &stamp, const Unit &inputUnit, const Unit &outputUnit);

} // namespace time_


#endif // _LIMINAL_LIB_TIME_STAMPT_T_HPP_