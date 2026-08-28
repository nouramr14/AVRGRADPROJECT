/*
 * BIT_MATH.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_
#define REGISTER_SIZE 8
#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)    reg^=(1<<bit)
#define GET_BIT(reg,bit)    (reg&(1<<bit))>>bit
#define IS_BIT_SET(reg,bit)  (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)


#endif /* LIB_BIT_MATH_H_ */
