/* Copyright 2018 Boris Vinogradov <no111u3@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Lepestrum C++ Library implementation
 * Universal data input
 * @file in.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_IN_HH
#define LP_CC_LIB_IN_HH

#include <types.hh>

namespace lp {
    template <typename Inner, bool echo = true, typename Type = u32_t>
    class in {
    public:
        using inner = Inner;
        static constexpr auto t_bit_size = sizeof(Type) * 8;

        static constexpr void recv(i8_t &symbol) {
            symbol = inner::recv();
            if (echo) {
                inner::send(symbol);
            }
        }

        template <Type N>
        static constexpr void recv(i8_t (&string)[N]) {
            auto beg = string;
            const auto end = beg + N - 1;

            while (beg < end) {
                s8_t ch = inner::recv();
                if (echo) {
                    inner::send(ch);
                }
                if (ch == '\n' || ch == '\r') {
                    break;
                }
                *beg++ = ch;
            }
            *beg = '\0';
        }

        template <typename T>
        static constexpr void recv(T &number) {
            number = 0;
            i8_t buffer[t_bit_size + 1];

            auto beg = buffer;
            auto end = beg + t_bit_size;
            i8_t ch;
            auto sig = false;

            while ((ch = inner::recv()) <= ' ');

            while (beg < end) {
                if (echo) {
                    inner::send(ch);
                }
                if (ch == '\n' || ch == '\r' || ch <= ' ') {
                    break;
                }
                *beg++ = ch;
                ch = inner::recv();
            }

            beg = buffer;
            if (*beg == '-') {
                sig = true;
                beg++;
            }

            convert(beg, end, number);

            if (sig)
                number = 0 - number;
        }

        template <typename In, typename ...Ins>
        static constexpr void recv(In &in, Ins &...ins) {
            recv(in);
            recv(ins...);
        }
    private:
        static constexpr bool default_checker (i8_t ch) {
            return (ch == '\n' || ch == '\r') ?
                true : false;
        }

        template <typename T>
        static constexpr void convert(i8_t *beg, i8_t *end, T &number) {
            auto base = 10;

            if (*beg == '0') {
                beg++;
                if (*beg == 'a') {
                    base = 36;
                } else if (*beg == 'x') {
                    base = 16;
                } else if (*beg == 'b') {
                    base = 2;
                } else if (*beg <= ' ') {
                    return;
                } else {
                    base = 8;
                    beg--;
                }
                beg++;
            }

            while (beg < end) {
                i8_t ch = *beg;
                if (ch <= ' ') {
                    break;
                }
                if (ch >= 'a')
                    ch -= 0x20;
                ch -= '0';
                if (ch >= 17) {
                    ch -= 7;

                    if (ch <= 9) {
                        return;
                    }
                }
                if (ch >= base) {
                    return;
                }

                number = number * base + ch;
                beg++;
            }
        }
    };
}

#endif // LP_CC_LIB_IN_HH
