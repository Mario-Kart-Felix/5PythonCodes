/*! \file global_defines.h
 * Include file for global defines
 */
/*
 * Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef GLOBAL_DEFINES_H_
#define GLOBAL_DEFINES_H_

//#include <stdint.h>
//#include <stdio.h>
#include <inttypes.h>

#ifdef __arm__
#pragma import(__use_no_semihosting)

// stdio.h output override file handles
//struct __FILE { int handle;   /* Add whatever you need here */};
//extern FILE *stdnoecho;
//extern FILE *stdoutraw;
//extern FILE *stdoutnb;


// Log buffer settings
#if !defined(ECOSIM_KIT) && !defined(FULL_CHIP_SIM) && !defined(BOOTBLOCK)
#define LOG_BUFFER_EXISTS
#define LOG_BUFFER_MODE         1
#define LOG_BUFFER_ENABLED
#define LOG_STDOUT_ENABLED
#define LOG_FILE_NAME
#define LOG_FUNC_NAME
#define LOG_LINE_NUM
#define PSIF_LOG_ENABLED
#endif
#endif

typedef unsigned long long	U64;
typedef unsigned int		U32;
typedef unsigned short		U16;
typedef unsigned char		U8;

typedef long long		    S64;
typedef int			        S32;
typedef short			    S16;
typedef char			    S8;

typedef unsigned long long  UINT64;
typedef unsigned int        UINT32;
typedef unsigned short      UINT16;
typedef unsigned char       UINT8;

typedef signed long long  INT64;
typedef signed int        INT32;
typedef signed short      INT16;
typedef signed char       INT8;

//typedef unsigned long long	u64;
//typedef unsigned int		u32;
//typedef unsigned short		u16;
//typedef unsigned char		u8;

#ifdef PACKAGE_VERSION
#define REV_STRING PACKAGE_VERSION
#else
#define REV_STRING _REVMAJ_"."_REVMIN_
#endif

// Location in memory where the reboot code is located at for applications
#define REBOOT_VECTOR       0x001FFF00

// EPS core identifiers
enum eps_id {
    EPSA_0_ID  = 0x1,
    EPSA_1_ID  = 0x2,
    EPSA_2_ID  = 0x3,
    EPSA_3_ID  = 0x4,
    EPSC_ID    = 0x5,
    EPS_ID_END = 0x6
};


#define FULL_ASIC_RESET         0x013012AALL
#define FULL_ASIC_RESET_VALUE   0x0000A11CLL

#define HW_SHRD_MEM_BASE        0x001C0000
#define HW_SHRD_MEM_END		0x00200000

// TODO: This should be in a psif_stdlib.h file...
extern int str2uint(char *str, uint64_t *data);

#define _4K     0x00001000
#define _8K     0x00002000
#define _16K    0x00004000
#define _32K    0x00008000
#define	_64K    0x00010000
#define	_128K   0x00020000
#define	_256K   0x00040000
#define	_512K   0x00080000
#define	_1M     0x00100000
#define	_2M     0x00200000
#define	_4M     0x00400000
#define	_8M     0x00800000
#define	_16M    0x01000000
#define	_32M    0x02000000
#define	_64M    0x04000000
#define	_128M   0x08000000


#define	GET_BIT(val, n) \
	((val >> n) & 0x1ULL)

/* get n bits from position p */
#define	GET_BITS(val, n, p) \
	((val >> p) & ((1ULL << n) - 1ULL))

#define	SET_BIT(res, n, val) \
	((unsigned long long) ((0 != val) ? \
		(res | (0x01ULL << n)) : (res & ~(0x01ULL << n))))

/* set bit in res to value from val where mask is 1 */
#define	SET_MASK_BITS(res, val, mask) \
	((res & ~mask) | (val & mask))

/* set n bits from position p in res to val */
#define	SET_BITS(res, val, n, p) \
	(SET_MASK_BITS(res, (val << p), (((1ULL << n) - 1ULL) << p)))


int get_bits(U32 addr, U8 n, U8 p);
int set_bits(U32 addr, U8 n, U8 p, U64 val, int verbose);



#define	SET_ON_PORTS(portmask, addr, n, p, val, verbose) {		\
	int port, status;						\
	for (port = 0; port < 2; port++) {				\
		if (0 == GET_BIT(portmask, port))			\
			continue;					\
		status = set_bits(addr + port*IBU_PORT_1_OFFSET,	\
					n, p, val, verbose);		\
		if (0 != status) {					\
			if (verbose)					\
				printf("%s: Failed!\n", __FUNCTION__);	\
			return (1);					\
		}							\
	}								\
}

#define BOTH_PORTS	3	/* ((1 << 1) | (1 << 0)) */

#define	SET_ON_BOTH_PORTS(addr, n, p, val, verbose)	\
	SET_ON_PORTS(BOTH_PORTS, addr, n, p, val, verbose)


#define	_TS(s, stat) \
	(s == TX_##stat) ? #stat :

#define	THREAD_STATE2STR(s) (  \
	_TS(s, READY		)\
	_TS(s, COMPLETED	)\
	_TS(s, TERMINATED	)\
	_TS(s, SUSPENDED	)\
	_TS(s, SLEEP		)\
	_TS(s, QUEUE_SUSP	)\
	_TS(s, SEMAPHORE_SUSP	)\
	_TS(s, EVENT_FLAG	)\
	_TS(s, BLOCK_MEMORY	)\
	_TS(s, BYTE_MEMORY	)\
	_TS(s, IO_DRIVER	)\
	_TS(s, FILE		)\
	_TS(s, TCP_IP		)\
	_TS(s, MUTEX_SUSP	)\
	       "UNKNOWN"	)

#define	THREAD_ERR2STR(s) (  \
	_TS(s, SUCCESS             )\
	_TS(s, DELETED             )\
	_TS(s, NO_MEMORY           )\
	_TS(s, POOL_ERROR          )\
	_TS(s, PTR_ERROR           )\
	_TS(s, WAIT_ERROR          )\
	_TS(s, SIZE_ERROR          )\
	_TS(s, GROUP_ERROR         )\
	_TS(s, NO_EVENTS           )\
	_TS(s, OPTION_ERROR        )\
	_TS(s, QUEUE_ERROR         )\
	_TS(s, QUEUE_EMPTY         )\
	_TS(s, QUEUE_FULL          )\
	_TS(s, SEMAPHORE_ERROR     )\
	_TS(s, NO_INSTANCE         )\
	_TS(s, THREAD_ERROR        )\
	_TS(s, PRIORITY_ERROR      )\
	_TS(s, START_ERROR         )\
	_TS(s, DELETE_ERROR        )\
	_TS(s, RESUME_ERROR        )\
	_TS(s, CALLER_ERROR        )\
	_TS(s, SUSPEND_ERROR       )\
	_TS(s, TIMER_ERROR         )\
	_TS(s, TICK_ERROR          )\
	_TS(s, ACTIVATE_ERROR      )\
	_TS(s, THRESH_ERROR        )\
	_TS(s, SUSPEND_LIFTED      )\
	_TS(s, WAIT_ABORTED        )\
	_TS(s, WAIT_ABORT_ERROR    )\
	_TS(s, MUTEX_ERROR         )\
	_TS(s, NOT_AVAILABLE       )\
	_TS(s, NOT_OWNED           )\
	_TS(s, INHERIT_ERROR       )\
	_TS(s, NOT_DONE            )\
	_TS(s, CEILING_EXCEEDED    )\
	_TS(s, INVALID_CEILING     )\
	_TS(s, FEATURE_NOT_ENABLED )\
	       "UNKNOWN"	)

#endif				/* GLOBAL_DEFINES_H_ */
