// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
--------------------------------------------------------------------------------
Copyright (C) 2002-present Jason Evans <jasone@canonware.com>.
All rights reserved.
Copyright (C) 2007-2012 Mozilla Foundation.  All rights reserved.
Copyright (C) 2009-present Facebook, Inc.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice(s),
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice(s),
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------------'
**/

#include "util/gc_helper_smoothstep.h"

#include <cstdint>

namespace starrocks {

// the following code is generated by JeMalloc script, `smoothstep.sh smoother 180 24 3 15`

/*
 * This file was generated by the following command:
 *   sh smoothstep.sh smoother 180 24 3 15
 */
/******************************************************************************/

/*
 * This header defines a precomputed table based on the smoothstep family of
 * sigmoidal curves (https://en.wikipedia.org/wiki/Smoothstep) that grow from 0
 * to 1 in 0 <= x <= 1.  The table is stored as integer fixed point values so
 * that floating point math can be avoided.
 *
 *                      3     2
 *   smoothstep(x) = -2x  + 3x
 *
 *                       5      4      3
 *   smootherstep(x) = 6x  - 15x  + 10x
 *
 *                          7      6      5      4
 *   smootheststep(x) = -20x  + 70x  - 84x  + 35x
 */

#define SMOOTHSTEP_VARIANT "smoother"
// #define SMOOTHSTEP_NSTEPS 180
// #define SMOOTHSTEP_BFP 24
#define SMOOTHSTEP                                                    \
    /* STEP(step, h,                            x,     y) */          \
    STEP(1, UINT64_C(0x000000000000001c), 0.005, 0.000001700420422)   \
    STEP(2, UINT64_C(0x00000000000000e2), 0.011, 0.000013489813535)   \
    STEP(3, UINT64_C(0x00000000000002f5), 0.016, 0.000045146604943)   \
    STEP(4, UINT64_C(0x00000000000006f4), 0.022, 0.000106113905398)   \
    STEP(5, UINT64_C(0x0000000000000d77), 0.027, 0.000205503321396)   \
    STEP(6, UINT64_C(0x0000000000001713), 0.033, 0.000352098765433)   \
    STEP(7, UINT64_C(0x0000000000002454), 0.038, 0.000554360266476)   \
    STEP(8, UINT64_C(0x00000000000035c4), 0.044, 0.000820427780309)   \
    STEP(9, UINT64_C(0x0000000000004be6), 0.050, 0.001158125000000)   \
    STEP(10, UINT64_C(0x0000000000006737), 0.055, 0.001574963166184)  \
    STEP(11, UINT64_C(0x0000000000008831), 0.061, 0.002078144877568)  \
    STEP(12, UINT64_C(0x000000000000af47), 0.066, 0.002674567901237)  \
    STEP(13, UINT64_C(0x000000000000dce9), 0.072, 0.003370828983136)  \
    STEP(14, UINT64_C(0x000000000001117f), 0.077, 0.004173227658377)  \
    STEP(15, UINT64_C(0x0000000000014d6e), 0.083, 0.005087770061735)  \
    STEP(16, UINT64_C(0x0000000000019117), 0.088, 0.006120172737908)  \
    STEP(17, UINT64_C(0x000000000001dcd4), 0.094, 0.007275866452018)  \
    STEP(18, UINT64_C(0x00000000000230fc), 0.100, 0.008560000000000)  \
    STEP(19, UINT64_C(0x0000000000028de1), 0.105, 0.009977444018946)  \
    STEP(20, UINT64_C(0x000000000002f3d0), 0.111, 0.011532794797543)  \
    STEP(21, UINT64_C(0x0000000000036310), 0.116, 0.013230378086409)  \
    STEP(22, UINT64_C(0x000000000003dbe7), 0.122, 0.015074252908606)  \
    STEP(23, UINT64_C(0x0000000000045e95), 0.127, 0.017068215369859)  \
    STEP(24, UINT64_C(0x000000000004eb53), 0.133, 0.019215802469130)  \
    STEP(25, UINT64_C(0x000000000005825a), 0.138, 0.021520295908904)  \
    STEP(26, UINT64_C(0x00000000000623dc), 0.144, 0.023984725905606)  \
    STEP(27, UINT64_C(0x000000000006d009), 0.150, 0.026611875000000)  \
    STEP(28, UINT64_C(0x0000000000078709), 0.155, 0.029404281867599)  \
    STEP(29, UINT64_C(0x0000000000084905), 0.161, 0.032364245129047)  \
    STEP(30, UINT64_C(0x000000000009161f), 0.166, 0.035493827160495)  \
    STEP(31, UINT64_C(0x000000000009ee75), 0.172, 0.038794857904025)  \
    STEP(32, UINT64_C(0x00000000000ad223), 0.177, 0.042268938678053)  \
    STEP(33, UINT64_C(0x00000000000bc13e), 0.183, 0.045917445987657)  \
    STEP(34, UINT64_C(0x00000000000cbbdc), 0.188, 0.049741535335059)  \
    STEP(35, UINT64_C(0x00000000000dc20b), 0.194, 0.053742145029963)  \
    STEP(36, UINT64_C(0x00000000000ed3d8), 0.200, 0.057920000000000)  \
    STEP(37, UINT64_C(0x00000000000ff14b), 0.205, 0.062275615601023)  \
    STEP(38, UINT64_C(0x0000000000111a6a), 0.211, 0.066809301427618)  \
    STEP(39, UINT64_C(0x0000000000124f36), 0.216, 0.071521165123459)  \
    STEP(40, UINT64_C(0x0000000000138fad), 0.222, 0.076411116191639)  \
    STEP(41, UINT64_C(0x000000000014dbcc), 0.227, 0.081478869805164)  \
    STEP(42, UINT64_C(0x000000000016338a), 0.233, 0.086723950617274)  \
    STEP(43, UINT64_C(0x00000000001796dc), 0.238, 0.092145696571910)  \
    STEP(44, UINT64_C(0x00000000001905b3), 0.244, 0.097743262714018)  \
    STEP(45, UINT64_C(0x00000000001a8000), 0.250, 0.103515625000000)  \
    STEP(46, UINT64_C(0x00000000001c05ac), 0.255, 0.109461584108101)  \
    STEP(47, UINT64_C(0x00000000001d96a2), 0.261, 0.115579769248840)  \
    STEP(48, UINT64_C(0x00000000001f32c8), 0.266, 0.121868641975310)  \
    STEP(49, UINT64_C(0x000000000020da01), 0.272, 0.128326499993640)  \
    STEP(50, UINT64_C(0x0000000000228c2e), 0.277, 0.134951480973421)  \
    STEP(51, UINT64_C(0x000000000024492c), 0.283, 0.141741566358020)  \
    STEP(52, UINT64_C(0x00000000002610d9), 0.288, 0.148694585175024)  \
    STEP(53, UINT64_C(0x000000000027e30c), 0.294, 0.155808217846616)  \
    STEP(54, UINT64_C(0x000000000029bf9c), 0.300, 0.163080000000000)  \
    STEP(55, UINT64_C(0x00000000002ba65e), 0.305, 0.170507326277746)  \
    STEP(56, UINT64_C(0x00000000002d9723), 0.311, 0.178087454148248)  \
    STEP(57, UINT64_C(0x00000000002f91bc), 0.316, 0.185817507716045)  \
    STEP(58, UINT64_C(0x00000000003195f6), 0.322, 0.193694481532292)  \
    STEP(59, UINT64_C(0x000000000033a39c), 0.327, 0.201715244405062)  \
    STEP(60, UINT64_C(0x000000000035ba78), 0.333, 0.209876543209873)  \
    STEP(61, UINT64_C(0x000000000037da51), 0.338, 0.218175006699944)  \
    STEP(62, UINT64_C(0x00000000003a02ed), 0.344, 0.226607149316668)  \
    STEP(63, UINT64_C(0x00000000003c340f), 0.350, 0.235169375000000)  \
    STEP(64, UINT64_C(0x00000000003e6d7a), 0.355, 0.243857980998819)  \
    STEP(65, UINT64_C(0x000000000040aeed), 0.361, 0.252669161681402)  \
    STEP(66, UINT64_C(0x000000000042f827), 0.366, 0.261599012345679)  \
    STEP(67, UINT64_C(0x00000000004548e5), 0.372, 0.270643533029766)  \
    STEP(68, UINT64_C(0x000000000047a0e2), 0.377, 0.279798632322307)  \
    STEP(69, UINT64_C(0x000000000049ffd8), 0.383, 0.289060131172836)  \
    STEP(70, UINT64_C(0x00000000004c657f), 0.388, 0.298423766702228)  \
    STEP(71, UINT64_C(0x00000000004ed190), 0.394, 0.307885196013061)  \
    STEP(72, UINT64_C(0x00000000005143bf), 0.400, 0.317440000000000)  \
    STEP(73, UINT64_C(0x000000000053bbc1), 0.405, 0.327083687160242)  \
    STEP(74, UINT64_C(0x000000000056394a), 0.411, 0.336811697403855)  \
    STEP(75, UINT64_C(0x000000000058bc0c), 0.416, 0.346619405864194)  \
    STEP(76, UINT64_C(0x00000000005b43b9), 0.422, 0.356502126708327)  \
    STEP(77, UINT64_C(0x00000000005dd000), 0.427, 0.366455116947364)  \
    STEP(78, UINT64_C(0x0000000000606092), 0.433, 0.376473580246912)  \
    STEP(79, UINT64_C(0x000000000062f51d), 0.438, 0.386552670737428)  \
    STEP(80, UINT64_C(0x0000000000658d4f), 0.444, 0.396687496824667)  \
    STEP(81, UINT64_C(0x00000000006828d6), 0.450, 0.406873125000000)  \
    STEP(82, UINT64_C(0x00000000006ac75d), 0.455, 0.417104583650871)  \
    STEP(83, UINT64_C(0x00000000006d6892), 0.461, 0.427376866871161)  \
    STEP(84, UINT64_C(0x0000000000700c1e), 0.466, 0.437684938271614)  \
    STEP(85, UINT64_C(0x000000000072b1ae), 0.472, 0.448023734790170)  \
    STEP(86, UINT64_C(0x00000000007558ed), 0.477, 0.458388170502450)  \
    STEP(87, UINT64_C(0x0000000000780184), 0.483, 0.468773140432101)  \
    STEP(88, UINT64_C(0x00000000007aab1d), 0.488, 0.479173524361117)  \
    STEP(89, UINT64_C(0x00000000007d5563), 0.494, 0.489584190640406)  \
    STEP(90, UINT64_C(0x0000000000800000), 0.500, 0.500000000000000)  \
    STEP(91, UINT64_C(0x000000000082aa9c), 0.505, 0.510415809359598)  \
    STEP(92, UINT64_C(0x00000000008554e2), 0.511, 0.520826475638876)  \
    STEP(93, UINT64_C(0x000000000087fe7b), 0.516, 0.531226859567902)  \
    STEP(94, UINT64_C(0x00000000008aa712), 0.522, 0.541611829497545)  \
    STEP(95, UINT64_C(0x00000000008d4e51), 0.527, 0.551976265209827)  \
    STEP(96, UINT64_C(0x00000000008ff3e1), 0.533, 0.562315061728394)  \
    STEP(97, UINT64_C(0x000000000092976d), 0.538, 0.572623133128848)  \
    STEP(98, UINT64_C(0x00000000009538a2), 0.544, 0.582895416349131)  \
    STEP(99, UINT64_C(0x000000000097d729), 0.550, 0.593126875000000)  \
    STEP(100, UINT64_C(0x00000000009a72b0), 0.555, 0.603312503175339) \
    STEP(101, UINT64_C(0x00000000009d0ae2), 0.561, 0.613447329262566) \
    STEP(102, UINT64_C(0x00000000009f9f6d), 0.566, 0.623526419753091) \
    STEP(103, UINT64_C(0x0000000000a22fff), 0.572, 0.633544883052629) \
    STEP(104, UINT64_C(0x0000000000a4bc46), 0.577, 0.643497873291676) \
    STEP(105, UINT64_C(0x0000000000a743f3), 0.583, 0.653380594135806) \
    STEP(106, UINT64_C(0x0000000000a9c6b5), 0.588, 0.663188302596137) \
    STEP(107, UINT64_C(0x0000000000ac443e), 0.594, 0.672916312839759) \
    STEP(108, UINT64_C(0x0000000000aebc40), 0.600, 0.682560000000000) \
    STEP(109, UINT64_C(0x0000000000b12e6f), 0.605, 0.692114803986950) \
    STEP(110, UINT64_C(0x0000000000b39a80), 0.611, 0.701576233297769) \
    STEP(111, UINT64_C(0x0000000000b60027), 0.616, 0.710939868827150) \
    STEP(112, UINT64_C(0x0000000000b85f1d), 0.622, 0.720201367677692) \
    STEP(113, UINT64_C(0x0000000000bab71a), 0.627, 0.729356466970232) \
    STEP(114, UINT64_C(0x0000000000bd07d8), 0.633, 0.738400987654325) \
    STEP(115, UINT64_C(0x0000000000bf5112), 0.638, 0.747330838318587) \
    STEP(116, UINT64_C(0x0000000000c19285), 0.644, 0.756142019001164) \
    STEP(117, UINT64_C(0x0000000000c3cbf0), 0.650, 0.764830625000000) \
    STEP(118, UINT64_C(0x0000000000c5fd12), 0.655, 0.773392850683329) \
    STEP(119, UINT64_C(0x0000000000c825ae), 0.661, 0.781824993300063) \
    STEP(120, UINT64_C(0x0000000000ca4587), 0.666, 0.790123456790118) \
    STEP(121, UINT64_C(0x0000000000cc5c63), 0.672, 0.798284755594938) \
    STEP(122, UINT64_C(0x0000000000ce6a09), 0.677, 0.806305518467718) \
    STEP(123, UINT64_C(0x0000000000d06e43), 0.683, 0.814182492283954) \
    STEP(124, UINT64_C(0x0000000000d268dc), 0.688, 0.821912545851753) \
    STEP(125, UINT64_C(0x0000000000d459a1), 0.694, 0.829492673722245) \
    STEP(126, UINT64_C(0x0000000000d64063), 0.700, 0.836920000000000) \
    STEP(127, UINT64_C(0x0000000000d81cf3), 0.705, 0.844191782153376) \
    STEP(128, UINT64_C(0x0000000000d9ef26), 0.711, 0.851305414824965) \
    STEP(129, UINT64_C(0x0000000000dbb6d3), 0.716, 0.858258433641967) \
    STEP(130, UINT64_C(0x0000000000dd73d1), 0.722, 0.865048519026574) \
    STEP(131, UINT64_C(0x0000000000df25fe), 0.727, 0.871673500006354) \
    STEP(132, UINT64_C(0x0000000000e0cd37), 0.733, 0.878131358024686) \
    STEP(133, UINT64_C(0x0000000000e2695d), 0.738, 0.884420230751154) \
    STEP(134, UINT64_C(0x0000000000e3fa53), 0.744, 0.890538415891882) \
    STEP(135, UINT64_C(0x0000000000e58000), 0.750, 0.896484375000000) \
    STEP(136, UINT64_C(0x0000000000e6fa4c), 0.755, 0.902256737285982) \
    STEP(137, UINT64_C(0x0000000000e86923), 0.761, 0.907854303428098) \
    STEP(138, UINT64_C(0x0000000000e9cc75), 0.766, 0.913276049382715) \
    STEP(139, UINT64_C(0x0000000000eb2433), 0.772, 0.918521130194834) \
    STEP(140, UINT64_C(0x0000000000ec7052), 0.777, 0.923588883808366) \
    STEP(141, UINT64_C(0x0000000000edb0c9), 0.783, 0.928478834876545) \
    STEP(142, UINT64_C(0x0000000000eee595), 0.788, 0.933190698572375) \
    STEP(143, UINT64_C(0x0000000000f00eb4), 0.794, 0.937724384398971) \
    STEP(144, UINT64_C(0x0000000000f12c27), 0.800, 0.942080000000000) \
    STEP(145, UINT64_C(0x0000000000f23df4), 0.805, 0.946257854970026) \
    STEP(146, UINT64_C(0x0000000000f34423), 0.811, 0.950258464664934) \
    STEP(147, UINT64_C(0x0000000000f43ec1), 0.816, 0.954082554012337) \
    STEP(148, UINT64_C(0x0000000000f52ddc), 0.822, 0.957731061321958) \
    STEP(149, UINT64_C(0x0000000000f6118a), 0.827, 0.961205142095980) \
    STEP(150, UINT64_C(0x0000000000f6e9e0), 0.833, 0.964506172839510) \
    STEP(151, UINT64_C(0x0000000000f7b6fa), 0.838, 0.967635754870953) \
    STEP(152, UINT64_C(0x0000000000f878f6), 0.844, 0.970595718132411) \
    STEP(153, UINT64_C(0x0000000000f92ff6), 0.850, 0.973388125000000) \
    STEP(154, UINT64_C(0x0000000000f9dc23), 0.855, 0.976015274094403) \
    STEP(155, UINT64_C(0x0000000000fa7da5), 0.861, 0.978479704091102) \
    STEP(156, UINT64_C(0x0000000000fb14ac), 0.866, 0.980784197530860) \
    STEP(157, UINT64_C(0x0000000000fba16a), 0.872, 0.982931784630135) \
    STEP(158, UINT64_C(0x0000000000fc2418), 0.877, 0.984925747091400) \
    STEP(159, UINT64_C(0x0000000000fc9cef), 0.883, 0.986769621913572) \
    STEP(160, UINT64_C(0x0000000000fd0c2f), 0.888, 0.988467205202455) \
    STEP(161, UINT64_C(0x0000000000fd721e), 0.894, 0.990022555981056) \
    STEP(162, UINT64_C(0x0000000000fdcf03), 0.900, 0.991440000000000) \
    STEP(163, UINT64_C(0x0000000000fe232b), 0.905, 0.992724133547993) \
    STEP(164, UINT64_C(0x0000000000fe6ee8), 0.911, 0.993879827262107) \
    STEP(165, UINT64_C(0x0000000000feb291), 0.916, 0.994912229938268) \
    STEP(166, UINT64_C(0x0000000000feee80), 0.922, 0.995826772341611) \
    STEP(167, UINT64_C(0x0000000000ff2316), 0.927, 0.996629171016863) \
    STEP(168, UINT64_C(0x0000000000ff50b8), 0.933, 0.997325432098767) \
    STEP(169, UINT64_C(0x0000000000ff77ce), 0.938, 0.997921855122439) \
    STEP(170, UINT64_C(0x0000000000ff98c8), 0.944, 0.998425036833823) \
    STEP(171, UINT64_C(0x0000000000ffb419), 0.950, 0.998841875000000) \
    STEP(172, UINT64_C(0x0000000000ffca3b), 0.955, 0.999179572219685) \
    STEP(173, UINT64_C(0x0000000000ffdbab), 0.961, 0.999445639733524) \
    STEP(174, UINT64_C(0x0000000000ffe8ec), 0.966, 0.999647901234558) \
    STEP(175, UINT64_C(0x0000000000fff288), 0.972, 0.999794496678602) \
    STEP(176, UINT64_C(0x0000000000fff90b), 0.977, 0.999893886094594) \
    STEP(177, UINT64_C(0x0000000000fffd0a), 0.983, 0.999954853395052) \
    STEP(178, UINT64_C(0x0000000000ffff1d), 0.988, 0.999986510186459) \
    STEP(179, UINT64_C(0x0000000000ffffe3), 0.994, 0.999998299579589) \
    STEP(180, UINT64_C(0x0000000001000000), 1.000, 1.000000000000000)

static const uint64_t h_steps[SMOOTHSTEP_NSTEPS] = {
#define STEP(step, h, x, y) h,
        SMOOTHSTEP
#undef STEP
};

size_t get_smoothstep_at(size_t index) {
    return h_steps[index];
}

} // namespace starrocks
