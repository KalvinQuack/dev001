#ifndef __PLATFORMS_H__
#define __PLATFORMS_H__

#pragma once

#define XSTR(V...) #V

#ifdef __TMC129__
    #define HAL_PATH(PATH, NAME) XSTR(PATH/HAL/TMC129/NAME)
#elif defined(__TMC123__)
    #define HAL_PATH(PATH, NAME) XSTR(PATH/HAL/TMC123/NAME)
#endif/* __PLATFORMS_H__ */
#endif/* __PLATFORMS_H__ */
