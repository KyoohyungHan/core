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
use crate::c1665::big::NLEN;

// Base Bits= 60
pub const MODULUS:[Chunk;NLEN]=[0xFFFFFFFFFFFFFFB,0xFFFFFFFFFFFFFFF,0x3FFFFFFFFFFF];
pub const R2MODP:[Chunk;NLEN]=[0x190000000,0x0,0x0];
pub const ROI:[Chunk;NLEN]=[0xFFFFFFFFFFFFFFA,0xFFFFFFFFFFFFFFF,0x3FFFFFFFFFFF];
pub const MCONST:Chunk=0x5;

//*** rom curve parameters *****
// Base Bits= 60

pub const CURVE_A:isize = 1;
pub const CURVE_COF_I:isize = 4;
pub const CURVE_COF:[Chunk;NLEN]=[0x4,0x0,0x0];
pub const CURVE_B_I:isize = 5766;
pub const CURVE_B:[Chunk;NLEN]=[0x1686,0x0,0x0];
pub const CURVE_ORDER:[Chunk;NLEN]=[0x80FF0A99DBA8B27,0xFFFFFFFFFD5EF01,0xFFFFFFFFFFF];
pub const CURVE_GX:[Chunk;NLEN]=[0x671B9DBF9D52398,0x9A0618EE0F666C,0x14C94DA505B8];
pub const CURVE_GY:[Chunk;NLEN]=[0xC7087B244920345,0x13BFC7739D62DC2,0x29414549BC0A];