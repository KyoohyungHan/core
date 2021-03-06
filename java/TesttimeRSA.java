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

/* test driver and function exerciser for ECDH/ECIES/ECDSA API Functions */

package org.miracl.core.XXX;

import java.util.Scanner;
import junit.framework.TestCase;
import org.miracl.core.RAND;

public class TesttimeRSA extends TestCase {
    public static final int MIN_TIME = 10; /* seconds */
    public static final int MIN_ITERS = 10;

    public static void testtimeRSA() {
        byte[] RAW = new byte[100];
        RAND rng = new RAND();
        int i, iterations;
        long start, elapsed;
        double dur;
        public_key pub = new public_key(CONFIG_FF.FFLEN);
        private_key priv = new private_key(FF.HFLEN);

        rng.clean();
        for (i = 0; i < 100; i++) RAW[i] = (byte)(i);
        rng.seed(100, RAW);

        byte[] P = new byte[RSA.RFS];
        byte[] M = new byte[RSA.RFS];
        byte[] C = new byte[RSA.RFS];

        System.out.println("\nTesting/Timing  RSA");
        System.out.println("Generating RSA public/private key pair");

        iterations = 0;
        start = System.currentTimeMillis();
        do {
            RSA.KEY_PAIR(rng, 65537, priv, pub);
            iterations++;
            elapsed = (System.currentTimeMillis() - start);
        } while (elapsed < MIN_TIME * 1000 || iterations < MIN_ITERS);
        dur = (double)elapsed / iterations;
        System.out.format("RSA gen - %8d iterations  ", iterations);
        System.out.format(" %8.2f ms per iteration\n", dur);

        for (i = 0; i < RSA.RFS; i++) M[i] = (byte)(i % 128);

        iterations = 0;
        start = System.currentTimeMillis();
        do {
            RSA.ENCRYPT(pub, M, C);
            iterations++;
            elapsed = (System.currentTimeMillis() - start);
        } while (elapsed < MIN_TIME * 1000 || iterations < MIN_ITERS);
        dur = (double)elapsed / iterations;
        System.out.format("RSA enc - %8d iterations  ", iterations);
        System.out.format(" %8.2f ms per iteration\n", dur);

        iterations = 0;
        start = System.currentTimeMillis();
        do {
            RSA.DECRYPT(priv, C, P);
            iterations++;
            elapsed = (System.currentTimeMillis() - start);
        } while (elapsed < MIN_TIME * 1000 || iterations < MIN_ITERS);
        dur = (double)elapsed / iterations;
        System.out.format("RSA dec - %8d iterations  ", iterations);
        System.out.format(" %8.2f ms per iteration\n", dur);

        for (i = 0; i < RSA.RFS; i++) {
            if (P[i] != M[i]) {
                fail("FAILURE - RSA decryption");
            }
        }

        System.out.print("All tests pass\n");
    }
}
