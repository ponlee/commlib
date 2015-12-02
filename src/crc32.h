/**********************************
 * File: crc32.hpp
 * Author:ponlee
 * Version:1.0
 * Date: 2014-04
 * Desc: ͨ�õ�crc32�㷨ʵ��
***********************************/

#ifndef _CRC_32_HPP__
#define _CRC_32_HPP__

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "c" {
#endif

	uint32_t generate_crc32c(char *string, size_t length);

#ifdef __cplusplus
};
#endif


#endif