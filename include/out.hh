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
 * Universal data output
 * @file out.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_OUT_HH
#define LP_CC_LIB_OUT_HH

#include <types.hh>

namespace lp {
    template <typename Outer, typename Type = u32_t>
    class out {
    public:
        using outer = Outer;
        static constexpr auto t_bit_size = sizeof(Type) * 8;

        enum struct base : u8_t {
            bin = 2,
            oct = 8,
            dec = 10,
            hex = 16,
            alpha = 36
        };

        template <typename T>
        struct to_base {
            const base bs;
            const T t;
        };

        template <typename T>
        static constexpr to_base<T> make_base(const base bs, const T t) {
            return to_base<T>{bs, t};
        }

        static constexpr void send(const i8_t symbol) {
            outer::send(symbol);
        }

        static constexpr void send(const i8_t *string) {
            while (*string != '\0') {
                outer::send(*string++);
            }
        }

        static constexpr void send(const i16_t number,
            const base out_base = base::dec) {
            send(static_cast<i32_t>(number), out_base);
        }

        static constexpr void send(const i32_t number,
            const base out_base = base::dec) {
            if (number < 0) {
                send('-');
                send(static_cast<u32_t>(number * -1), out_base);
            } else {
                send(static_cast<u32_t>(number), out_base);
            }
        }

        static constexpr void send(const u8_t number,
            const base out_base = base::dec) {
            send(static_cast<u32_t>(number), out_base);
        }

        static constexpr void send(const u16_t number,
            const base out_base = base::dec) {
            send(static_cast<u32_t>(number), out_base);
        }

        template <typename T>
        static constexpr void send(const to_base<T> t) {
            send(t.t, t.bs);
        }

        static constexpr void send(const u32_t number,
            const base out_base = base::dec) {
            i8_t output_buff[t_bit_size + 1]; // number of bits + '\0'

            const i8_t *pout =
                convert(output_buff + t_bit_size, number, out_base);

            send(pout);
        }

        template <typename Out, typename ...Outs>
        static constexpr void send(Out out, Outs ...outs) {
            send(out);
            send(outs...);
        }
    private:
        static constexpr i8_t * convert(
            i8_t *output_buff,
            u32_t number,
            const base out_base) {
            *output_buff-- = '\0';
            do {
                i8_t dig = number % static_cast<u8_t>(out_base);
                if (dig > 9)
                    dig += 0x27;
                *output_buff-- = dig + '0';
                number /=
                    static_cast<u8_t>(out_base);
            } while (number > 0);

            return output_buff + 1;
        }
    };
}

#endif // LP_CC_LIB_OUT_HH
