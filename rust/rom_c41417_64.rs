/*
   Copyright (C) 2019 MIRACL UK Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.


    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

     https://www.gnu.org/licenses/agpl-3.0.en.html

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   You can be released from the requirements of the license by purchasing     
   a commercial license. Buying such a license is mandatory as soon as you
   develop commercial activities involving the MIRACL Core Crypto SDK
   without disclosing the source code of your own applications, or shipping
   the MIRACL Core Crypto SDK with a closed source product.     
*/

use crate::arch::Chunk;
use crate::c41417::big::NLEN;

// Base Bits= 60
// c41417 Modulus
pub const MODULUS: [Chunk; NLEN] = [
    0xFFFFFFFFFFFFFEF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0x3FFFFFFFFFFFFF,
];
pub const ROI: [Chunk; NLEN] = [
    0xFFFFFFFFFFFFFEE,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0x3FFFFFFFFFFFFF,
];
pub const R2MODP: [Chunk; NLEN] = [0x121000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0];
pub const MCONST: Chunk = 0x11;

// c41417 Curve
pub const CURVE_COF_I: isize = 8;
pub const CURVE_A: isize = 1;
pub const CURVE_B_I: isize = 3617;
pub const CURVE_COF: [Chunk; NLEN] = [0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0];
pub const CURVE_B: [Chunk; NLEN] = [0xE21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0];
pub const CURVE_ORDER: [Chunk; NLEN] = [
    0xB0E71A5E106AF79,
    0x1C0338AD63CF181,
    0x414CF706022B36F,
    0xFFFFFFFFEB3CC92,
    0xFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFF,
    0x7FFFFFFFFFFFF,
];
pub const CURVE_GX: [Chunk; NLEN] = [
    0x4FD3812F3CBC595,
    0x1A73FAA8537C64C,
    0x4AB4D6D6BA11130,
    0x3EC7F57FF35498A,
    0xE5FCD46369F44C0,
    0x300218C0631C326,
    0x1A334905141443,
];
pub const CURVE_GY: [Chunk; NLEN] = [0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0];
