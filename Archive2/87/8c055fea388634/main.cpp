/**
 * orlp's intrinsics helper from libop
 * (https://github.com/orlp/libop/blob/master/bits/intrin.h)
 * 
 * Dependency on boost/cstdint.hpp added for C++03 support.
 * 
 * 
 * Copyright (c) 2015 Orson Peters <orsonpeters@gmail.com>
 * 
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 
 * 3. This notice may not be removed or altered from any source distribution.
 */


#ifndef OP_INTRIN_H
#define OP_INTRIN_H

#include <limits>
#include <utility>
#include <boost/cstdint.hpp>

#ifdef _MSC_VER
    #include <intrin.h>
#endif

#ifdef __has_builtin
    #define OP_HAS_BUILTIN(x) (__has_builtin(x))
#else
    #define OP_HAS_BUILTIN(x) (0)
#endif


namespace op {
    // Counts number of leading zeros of n. Undefined behaviour if n is zero.
    int clz(uint64_t n);
    int clz(uint32_t n);

    // Multiplies two unsigned 64 bit numbers. Returns a pair of 64 bit numbers containing the
    // result (high, low).
    std::pair<uint64_t, uint64_t> mulu64(uint64_t a, uint64_t b);
    
    // Returns the quotient and remainder after dividing the unsigned 128 bit number (hi, lo) by d.
    std::pair<uint64_t, uint64_t> divu128_64(uint64_t hi, uint64_t lo, uint64_t d);
    uint64_t modu128_64(uint64_t hi, uint64_t lo, uint64_t d);

    // Returns (a*b) % m without risk of overflow.
    uint64_t mulmodu64(uint64_t a, uint64_t b, uint64_t m);
}



// Implementation.
namespace op {
    inline int clz(uint64_t n) {
        #if defined(__GNUC__) || OP_HAS_BUILTIN(__builtin_clzll)
            return __builtin_clzll(n);
        #elif defined(_MSC_VER) && defined(_M_X64)
            unsigned long result;
            if (_BitScanReverse64(&result, val)) return 63 - result;
            return 64;
        #else
            uint32_t t;
            int r = 64;

            t = n >> 32; if (t != 0) { r = r - 32; n = t; }
            t = n >> 16; if (t != 0) { r = r - 16; n = t; }
            t = n >>  8; if (t != 0) { r = r -  8; n = t; }
            t = n >>  4; if (t != 0) { r = r -  4; n = t; }
            t = n >>  2; if (t != 0) { r = r -  2; n = t; }
            t = n >>  1; if (t != 0) return r - 2;

            return r - n;
        #endif
    }

    inline int clz(uint32_t n) {
        #if defined(__GNUC__) || OP_HAS_BUILTIN(__builtin_clzl)
            return __builtin_clzl(n);
        #elif defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
            unsigned long result;
            _BitScanReverse(&result, val);
            return 31 - result;
        #else
            uint32_t t;
            int r = 32;

            t = n >> 16; if (t != 0) { r = r - 16; n = t; }
            t = n >>  8; if (t != 0) { r = r -  8; n = t; }
            t = n >>  4; if (t != 0) { r = r -  4; n = t; }
            t = n >>  2; if (t != 0) { r = r -  2; n = t; }
            t = n >>  1; if (t != 0) return r - 2;

            return r - n;
        #endif
    }


    inline std::pair<uint64_t, uint64_t> mulu64(uint64_t a, uint64_t b) {
        uint64_t h, l;

        #if defined(__GNUC__) && defined(__x86_64__)
            asm("mulq %3"
                : "=a"(l),"=d"(h)
                : "a"(a), "rm"(b)
                : "cc");
        #elif defined(_MSC_VER) && defined(_M_X64)
            l = _umul128(a, b, &h);
        #else
            // Courtesy of Mysticial.
            uint32_t al = a;
            uint32_t bl = b;
            uint32_t ah = a >> 32;
            uint32_t bh = b >> 32;

            uint64_t r0, r1;
            l  = al * bl;
            r0 = ah * bl;
            r1 = al * bh;
            h  = ah * bh;

            r0 += l >> 32;
            r1 += r0 & 0xffffffff;
            l  &= 0xffffffff;
            l  |= r1 << 32;
            h  += r0 >> 32;
            h  += r1 >> 32;
        #endif

        return std::make_pair(h, l);
    }


    inline uint64_t mulmodu64(uint64_t a, uint64_t b, uint64_t m) {
        #if defined(__GNUC__) && defined(__x86_64__)
            uint64_t q, r;
            asm("mulq %3;"
                "divq %4;"
                : "=a"(q), "=d"(r)
                : "a"(a), "d"(b), "rm"(m)
                : "cc");
            return r;
        #else
            a %= m;
            b %= m;

            // No overflow possible.
            if (a == 0) return b;
            if (b <= std::numeric_limits<uint64_t>::max() / a) return (a*b) % m;

            uint64_t res = 0;
            while (a != 0) {
                if (a & 1) {
                    if (b >= m - res) res -= m;
                    res += b;
                }

                a >>= 1;
                if (b >= m - b) b += b - m;
                else            b += b;
            }

            return res;
        #endif
    }
    

    inline std::pair<uint64_t, uint64_t> divu128_64(uint64_t hi, uint64_t lo, uint64_t d) {
        #if defined(__GNUC__) && defined(__x86_64__)
            uint64_t q, r;
            asm("divq %4"
                : "=a"(q),"=d"(r)
                : "a"(lo), "d" (hi), "rm"(d)
                : "cc");
            return std::make_pair(q, r);
        #else
            // Code from Hacker's Delight (http://www.hackersdelight.org/hdcodetxt/divlu.c.txt).
            const uint64_t b = (1ULL << 32); // Number base (32 bits).
            uint64_t un1, un0,               // Norm. dividend LSD's.
                     vn1, vn0,               // Norm. divisor digits.
                     q1, q0,                 // Quotient digits.
                     un64, un21, un10,       // Dividend digit pairs.
                     rhat;                   // A remainder.
            int s;                           // Shift amount for norm.
    
            // Overflow.
            if (hi >= d) return std::make_pair(uint64_t(-1), uint64_t(-1));
    
            // Count leading zeros.
            s = op::clz(d); // 0 <= s <= 63.
            if (s > 0) {
                d = d << s;           // Normalize divisor.
                un64 = (hi << s) | ((lo >> (64 - s)) & (-s >> 31));
                un10 = lo << s;       // Shift dividend left.
            } else {
                // Avoid undefined behavior.
                un64 = hi | lo;
                un10 = lo;
            }
                
            // Break divisor up into two 32-bit digits.
            vn1 = d >> 32;            
            vn0 = d & 0xFFFFFFFF; 

            // Break right half of dividend into two digits.
            un1 = un10 >> 32;         
            un0 = un10 & 0xFFFFFFFF;  

            // Compute the first quotient digit, q1.
            q1 = un64/vn1;
            rhat = un64 - q1*vn1;     

        again1:
            if (q1 >= b || q1*vn0 > b*rhat + un1) {
                q1 = q1 - 1;
                rhat = rhat + vn1;
                if (rhat < b) goto again1;
            }
            
            // Multiply and subtract.
            un21 = un64*b + un1 - q1*d;  

            // Compute the second quotient digit, q0.
            q0 = un21/vn1;            
            rhat = un21 - q0*vn1;     

        again2:
            if (q0 >= b || q0*vn0 > b*rhat + un0) {
                q0 = q0 - 1;
                rhat = rhat + vn1;
                if (rhat < b) goto again2;
            }

            return std::make_pair(q1*b + q0, (un21*b + un0 - q0*d) >> s);
        #endif
    }
}

#undef OP_HAS_BUILTIN

#endif






#include <boost/cstdint.hpp>
#include <iostream>

int main()
{
    const uint64_t sourceMask[] = {
		0x0000000080000000ULL,
		0
	};
	
    // Checking bit 32 is set
    std::clog << (sourceMask[0] & (1ull << 31)) << '\n';
    
	const uint64_t client_lists[2][32] = {
		// TOPSYNC_ENS
		{
			0,
			0,
			0,
			0,
            0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0x000000000000002eULL
		},
		
		// SYNCBOX_ENS
		{
			0,
			0,
			0
		}
	};
	
	for (int subsystem = 0; subsystem < 2; subsystem++) {
		const int lastSource = (sourceMask[subsystem] ? 64-op::clz(sourceMask[subsystem]) : 0);
        std::clog << "Last alarming source on subsystem " << subsystem << ": " << lastSource << '\n';
		for (int source_id = 0; source_id < lastSource; source_id++) {
			
			if (!(sourceMask[subsystem] & (uint64_t(1) << source_id))) {
				// If this source wasn't masked into this particular interrogation,
				// we can't say anything about alarms that may or may not be active
				// under it. In order to avoid falsely claiming that such alarms have
				// ended, we need to skip all the below logic in such a case.
                std::clog << "No alarm on subsystem " << subsystem << ", source ID " << +source_id << '\n';
				continue;
			}
			
			const uint64_t client_list_as_mask = client_lists[subsystem][source_id];
			
			//if (client_list_as_mask)
				std::clog << "Alarm bits on subsystem " << subsystem
					<< ", source ID " << +source_id << ": 0x" << std::hex << client_list_as_mask << std::dec << std::endl;
			
			for (int client_id = 1; client_id <= 64; client_id++) {
                const bool isAlarmActive = client_list_as_mask & (uint64_t(1) << (client_id-1));
                std::clog << "isAlarmActive? " << isAlarmActive << std::endl;
			}
		}
	}
}
